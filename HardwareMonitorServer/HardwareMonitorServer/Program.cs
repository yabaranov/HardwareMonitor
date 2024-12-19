using System;
using System.Collections.Generic;
using System.Data.SQLite;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Grpc.Core;
using GrpcHardwareMonitor;
using LibreHardwareMonitor.Hardware;
using System.Globalization;

namespace HardwareMonitorServer
{
    class Program
    {
        const string ConnectionString = "Data Source=users.db;Version=3;";

        static void Main(string[] args)
        {
            Console.Write("Enter the port number: ");
            if (!int.TryParse(Console.ReadLine(), out int port) || port <= 0 || port > 65535)
            {
                Console.WriteLine("Invalid port number. Exiting.");
                return;
            }

            var hardwareService = new HardwareServiceImpl(ConnectionString);

            var server = new Grpc.Core.Server
            {
                Services = { HardwareService.BindService(hardwareService) },
                Ports = { new ServerPort("localhost", port, ServerCredentials.Insecure) }
            };

            server.Start();
            hardwareService.StartSendingHardwareUpdates();

            Console.WriteLine($"Server started on port {port}");

            Console.ReadKey();
            server.ShutdownAsync().Wait();
        }
    }
}
