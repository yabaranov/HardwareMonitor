using Grpc.Core;
using GrpcHardwareMonitor;
using LibreHardwareMonitor.Hardware;
using System.Data.SQLite;

namespace HardwareMonitorServer
{
    public class HardwareServiceImpl : HardwareService.HardwareServiceBase
    {
        private readonly Dictionary<string, string> _users;
        private readonly List<IServerStreamWriter<GrpcHardwareMonitor.HardwareList>> _clients;
        private readonly object _clientsLock = new object();

        public HardwareServiceImpl(string connectionString)
        {
            _users = LoadUsersFromDatabase(connectionString);
            _clients = new List<IServerStreamWriter<GrpcHardwareMonitor.HardwareList>>();
        }

        private Dictionary<string, string> LoadUsersFromDatabase(string connectionString)
        {
            var users = new Dictionary<string, string>();
            using var connection = new SQLiteConnection(connectionString);
            connection.Open();

            using var command = new SQLiteCommand("SELECT Login, Password FROM Users", connection);
            using var reader = command.ExecuteReader();

            while (reader.Read())
            {
                users[reader.GetString(0)] = reader.GetString(1);
            }

            return users;
        }

        public override Task<GrpcHardwareMonitor.HardwareListInfo> getHardwareListInfo(None request, ServerCallContext context)
        {
            if (!Authenticate(context))
            {
                throw new RpcException(new Status(StatusCode.Unauthenticated, "Invalid login or password"));
            }

            var hardwareListInfo = new GrpcHardwareMonitor.HardwareListInfo();
            var computer = new Computer
            {
                IsCpuEnabled = true,
                IsGpuEnabled = true,
                IsMemoryEnabled = true
            };

            computer.Open();
            computer.Accept(new UpdateVisitor());

            foreach (var hardware in computer.Hardware)
            {
                var hardwareInfo = new GrpcHardwareMonitor.HardwareInfo { Name = hardware.Name };
                foreach (var sensor in hardware.Sensors)
                {
                    hardwareInfo.SensorInfos.Add(new GrpcHardwareMonitor.SensorInfo { Name = sensor.Name, Type = (GrpcHardwareMonitor.SensorInfo.Types.SensorType)sensor.SensorType });
                }
                hardwareListInfo.HardwareInfos.Add(hardwareInfo);
            }

            computer.Close();

            return Task.FromResult(hardwareListInfo);
        }

        public override async Task getHardwareList(None request, IServerStreamWriter<GrpcHardwareMonitor.HardwareList> responseStream, ServerCallContext context)
        {
            lock (_clientsLock)
            {
                _clients.Add(responseStream);
            }

            try
            {
                // Keep the stream open
                await Task.Delay(Timeout.Infinite, context.CancellationToken);
            }
            catch (TaskCanceledException)
            {
                // Client disconnected
            }
            finally
            {
                lock (_clientsLock)
                {
                    _clients.Remove(responseStream);
                }
            }
        }

        public void StartSendingHardwareUpdates()
        {
            Task.Run(async () =>
            {
                while (true)
                {
                    List<IServerStreamWriter<GrpcHardwareMonitor.HardwareList>> clientsCopy;
                    lock (_clientsLock)
                    {
                        clientsCopy = new List<IServerStreamWriter<GrpcHardwareMonitor.HardwareList>>(_clients);
                    }

                    var hardwareList = new GrpcHardwareMonitor.HardwareList();
                    var computer = new Computer
                    {
                        IsCpuEnabled = true,
                        IsGpuEnabled = true,
                        IsMemoryEnabled = true
                    };

                    computer.Open();
                    computer.Accept(new UpdateVisitor());

                    foreach (var hardware in computer.Hardware)
                    {
                        var hardwareData = new GrpcHardwareMonitor.Hardware();
                        foreach (var sensor in hardware.Sensors)
                        {
                            if (sensor.Value.HasValue)
                            {
                                hardwareData.Sensors.Add(new GrpcHardwareMonitor.Sensor { Value = sensor.Value.Value });
                            }
                        }
                        hardwareList.Hardwares.Add(hardwareData);
                    }

                    computer.Close();

                    foreach (var client in clientsCopy)
                    {
                        try
                        {
                            await client.WriteAsync(hardwareList);
                        }
                        catch
                        {
                            lock (_clientsLock)
                            {
                                _clients.Remove(client);
                            }
                        }
                    }

                    await Task.Delay(1000);
                }
            });
        }

        private bool Authenticate(ServerCallContext context)
        {
            var metadata = context.RequestHeaders;
            var login = metadata.FirstOrDefault(m => m.Key == "login")?.Value;
            var password = metadata.FirstOrDefault(m => m.Key == "password")?.Value;

            return login != null && password != null && _users.TryGetValue(login, out var storedPassword) && storedPassword == password;
        }
    }
}