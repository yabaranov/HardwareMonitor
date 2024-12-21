using Grpc.Core;
using GrpcHardwareMonitor;
using HardwareMonitorServer;
using System.Text.Json;

 public class HardwareServiceImpl : HardwareService.HardwareServiceBase
{
    private readonly ILogger<HardwareServiceImpl> _logger;
    private readonly string _userCredentialsFile = "user_credentials.json";
    public HardwareServiceImpl(ILogger<HardwareServiceImpl> logger)
     {
         _logger = logger;
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
        LibreHardwareMonitor.Hardware.Computer computer = new LibreHardwareMonitor.Hardware.Computer
        {
            IsCpuEnabled = true,
            IsGpuEnabled = true,
            IsMemoryEnabled = true,
            IsStorageEnabled = true
        };

        computer.Open();
        computer.Accept(new UpdateVisitor());

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

        computer.Close();
        return hardwareListInfo;
    }

    private HardwareList GetHardwareList()
    {
        var hardwareList = new HardwareList();
        LibreHardwareMonitor.Hardware.Computer computer = new LibreHardwareMonitor.Hardware.Computer
        {
            IsCpuEnabled = true,
            IsGpuEnabled = true,
            IsMemoryEnabled = true,
            IsStorageEnabled = true
        };

        computer.Open();
        computer.Accept(new UpdateVisitor());

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

        computer.Close();
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

