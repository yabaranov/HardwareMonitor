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
            GrpcHardwareMonitor::SensorInfo sensorInfo;
            sensorInfo.setHardwareName("Cpu1");
            sensorInfo.setSensorName("Clock1");
            sensorInfo.setValue(values[i++]);
            emit sensorChanged(sensorInfo);
        }
    );

    QThread::run();
}

