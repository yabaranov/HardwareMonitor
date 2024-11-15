#include "SensorThread.h"

#include "HardwareService_client.grpc.qpb.h"

SensorThread::SensorThread(GrpcHardwareMonitor::HardwareService::Client* client, QObject* parent)
    : QThread(parent),
      m_client(client)
{
    m_timer.start(1000);
}

void SensorThread::run()
{
    //std::shared_ptr<QGrpcServerStream> sensorStream = m_client->getSensorStream(GrpcHardwareMonitor::None());
    //auto finishedConnection = std::make_shared<QMetaObject::Connection>();
    //*finishedConnection = connect(sensorStream.get(), &QGrpcServerStream::finished, this,
    //    [this, finishedConnection, sensorStream ](const QGrpcStatus &status)
    //    {
    //        if (status.code() != QtGrpc::StatusCode::Ok)
    //            emit networkError(status.message());

    //        disconnect(*finishedConnection);
    //    }
    //);

    //connect(sensorStream.get(), &QGrpcServerStream::messageReceived, this,
    //    [sensorStream, this]
    //    {
    //        if (const auto sensorInfoResponse = sensorStream->read<GrpcHardwareMonitor::SensorInfo>())
    //            emit sensorChanged(*sensorInfoResponse);
    //    }
    //);

    connect(&m_timer, &QTimer::timeout, this,
        [this]()
        {
            QList<int> values {12,10,11,15,1000};
            if(i>=values.size())
                i = 0;
            GrpcHardwareMonitor::HardwareRepeated hardwares;

            GrpcHardwareMonitor::SensorRepeated sensors1;
            GrpcHardwareMonitor::Sensor sensor1;
            sensor1.setValue(values[i]);
            sensors1.append(sensor1);

            GrpcHardwareMonitor::Hardware hardware1;
            hardware1.setSensors(sensors1);
            hardwares.append(hardware1);

            GrpcHardwareMonitor::SensorRepeated sensors2;
            GrpcHardwareMonitor::Sensor sensor2;
            sensor2.setValue(values[i++]);
            sensors2.append(sensor2);

            GrpcHardwareMonitor::Hardware hardware2;
            hardware2.setSensors(sensors2);
            hardwares.append(hardware2);

            GrpcHardwareMonitor::HardwareList hardwareList;
            hardwareList.setHardwares(hardwares);
            emit sensorTablesChanged(hardwareList);
        }
    );

    QThread::run();
}

