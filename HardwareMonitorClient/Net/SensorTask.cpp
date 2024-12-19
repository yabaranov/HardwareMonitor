#include "SensorTask.h"

#include "HardwareService_client.grpc.qpb.h"

SensorTask::SensorTask(GrpcHardwareMonitor::HardwareService::Client* client)
    : m_client(client)
{
}

void SensorTask::changeSensorTables()
{
    std::shared_ptr<QGrpcServerStream> hardwareListStream = m_client->getHardwareList(GrpcHardwareMonitor::None());
    auto finishedConnection = std::make_shared<QMetaObject::Connection>();
    *finishedConnection = connect(hardwareListStream.get(), &QGrpcServerStream::finished, this,
        [this, finishedConnection, hardwareListStream ](const QGrpcStatus &status)
        {
            if (status.code() != QtGrpc::StatusCode::Ok)
                emit networkError(status.message());

            disconnect(*finishedConnection);
        }
    );

    connect(hardwareListStream.get(), &QGrpcServerStream::messageReceived, this,
        [hardwareListStream, this]
        {
            if (const auto hardwareList = hardwareListStream->read<GrpcHardwareMonitor::HardwareList>())
                emit sensorTablesChanged(*hardwareList);
        }
    );


    //QList<int> values {12,10,11,15,1000};
    //if(i>=values.size())
    //    i = 0;
    //GrpcHardwareMonitor::HardwareRepeated hardwares;

    //GrpcHardwareMonitor::SensorRepeated sensors1;
    //GrpcHardwareMonitor::Sensor sensor1;
    //sensor1.setValue(values[i]);
    //sensors1.append(sensor1);

    //GrpcHardwareMonitor::Hardware hardware1;
    //hardware1.setSensors(sensors1);
    //hardwares.append(hardware1);

    //GrpcHardwareMonitor::SensorRepeated sensors2;
    //GrpcHardwareMonitor::Sensor sensor2;
    //sensor2.setValue(values[i++]);
    //sensors2.append(sensor2);

    //GrpcHardwareMonitor::Hardware hardware2;
    //hardware2.setSensors(sensors2);
    //hardwares.append(hardware2);

    //GrpcHardwareMonitor::HardwareList hardwareList;
    //hardwareList.setHardwares(hardwares);
    //emit sensorTablesChanged(hardwareList);
    ////emit networkError("This username with this password doesn't exists.");
}
