using Grpc.Core;
using GrpcHardwareMonitor;
using System.Text.Json;

 public class HardwareServiceImpl : HardwareService.HardwareServiceBase
{
    private readonly ILogger<HardwareServiceImpl> _logger;
    private readonly string _userCredentialsFile = "user_credentials.json";

    LibreHardwareMonitor.Hardware.Computer computer;
    UpdateVisitor updateVisitor;
    public HardwareServiceImpl(ILogger<HardwareServiceImpl> logger)
     {
         _logger = logger;
        computer = new LibreHardwareMonitor.Hardware.Computer
        {
            IsCpuEnabled = true,
            IsGpuEnabled = true,
            IsMemoryEnabled = true,
            IsStorageEnabled = true
        };
        computer.Open();

        updateVisitor = new UpdateVisitor();

    }

    public override Task<HardwareListInfo> getHardwareListInfo(None request, ServerCallContext context)
    {
        if (!ValidateCredentials(context))
        {
            throw new RpcException(new Status(StatusCode.Unauthenticated, "Invalid username or password."));
        }

        return Task.FromResult(GetHardwareListInfo());
    }

    public override Task<HardwareList> getHardwareList(None request, ServerCallContext context)
    {
        if (!ValidateCredentials(context))
        {
            throw new RpcException(new Status(StatusCode.Unauthenticated, "Invalid username or password."));
        }

        return Task.FromResult(GetHardwareList());
    }

    private HardwareListInfo GetHardwareListInfo()
    {
        var hardwareListInfo = new HardwareListInfo();

        computer.Accept(updateVisitor);

        foreach (LibreHardwareMonitor.Hardware.IHardware hardware in computer.Hardware)
        {
            var hardwareInfo = new HardwareInfo { Name = hardware.Name };
            foreach (LibreHardwareMonitor.Hardware.ISensor sensor in hardware.Sensors)
            {
                hardwareInfo.SensorInfos.Add(new SensorInfo
                {
                    Name = sensor.Name,
                    Type = (SensorInfo.Types.SensorType)Enum.Parse(typeof(SensorInfo.Types.SensorType), sensor.SensorType.ToString(), true)
                });
            }
            hardwareListInfo.HardwareInfos.Add(hardwareInfo);
        }

        return hardwareListInfo;
    }

    private HardwareList GetHardwareList()
    {
        var hardwareList = new HardwareList();

        computer.Accept(updateVisitor);

        foreach (LibreHardwareMonitor.Hardware.IHardware hardware in computer.Hardware)
        {
            var hardwareEntry = new Hardware();
            foreach (LibreHardwareMonitor.Hardware.ISensor sensor in hardware.Sensors)
            {
                hardwareEntry.Sensors.Add(new Sensor
                {
                    Value = sensor.Value ?? 0.0f
                });
            }
            hardwareList.Hardwares.Add(hardwareEntry);
        }

        return hardwareList;
    }

    private bool ValidateCredentials(ServerCallContext context)
    {
        var metadata = context.RequestHeaders;
        string username = metadata.GetValue("Login");
        string password = metadata.GetValue("Password");

        if (File.Exists(_userCredentialsFile))
        {
            var users = JsonSerializer.Deserialize<Dictionary<string, string>>(File.ReadAllText(_userCredentialsFile));
            return users != null && users.TryGetValue(username, out var storedPassword) && storedPassword == password;
        }

        return false;
    }
}

