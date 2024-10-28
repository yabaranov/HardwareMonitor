#include "NetEngine.h"
#include "SensorThread.h"

#include "HardwareService_client.grpc.qpb.h"

#include <QGrpcHttp2Channel>
#include <QGrpcChannelOptions>
#include <qprotobufregistration.h>

NetEngine::NetEngine(QObject *parent)
    : QObject(parent),
      m_client(std::make_unique<GrpcHardwareMonitor::HardwareService::Client>())
{

}

NetEngine::~NetEngine()
{
    if (m_sensorThread && m_sensorThread->isRunning())
    {
        m_sensorThread->quit();
        m_sensorThread->wait();
    }
}

void NetEngine::startSensorThread()
{
    m_sensorThread = std::make_unique<SensorThread>(m_client.get());

    connect(m_sensorThread.get(), &SensorThread::networkError, this,
            &NetEngine::networkError, Qt::QueuedConnection);
    connect(m_sensorThread.get(), &SensorThread::sensorChanged, this,
            &NetEngine::sensorChanged, Qt::QueuedConnection);

    m_sensorThread->start();
}

void NetEngine::stopSensorThread()
{
    if (m_sensorThread && m_sensorThread->isRunning())
    {
        m_sensorThread->quit();
        m_sensorThread->wait();
    }

    disconnect(m_sensorThread.get(), &SensorThread::networkError, this,
            &NetEngine::networkError);
    disconnect(m_sensorThread.get(), &SensorThread::sensorChanged, this,
            &NetEngine::sensorChanged);

    m_sensorThread.reset();
}

void NetEngine::login(const QUrl& hostUri, const QString &name, const QString &password)
{
    //QHash<QByteArray, QByteArray> metadata =
    //    {
    //        { "user-name", { name.toUtf8() } },
    //        { "user-password", { password.toUtf8() } },
    //    };

    //QGrpcChannelOptions channelOptions;
    //channelOptions.setMetadata(metadata);

    //std::shared_ptr<QAbstractGrpcChannel> channel = std::make_shared<QGrpcHttp2Channel>(hostUri, channelOptions);

    //m_client->attachChannel(channel);
    //std::shared_ptr<QGrpcCallReply> replyCheckAuthentication = m_client->checkAuthentication(GrpcHardwareMonitor::None());

    //connect(replyCheckAuthentication.get(), &QGrpcCallReply::finished, this,
    //    [replyCheckAuthentication, this] (const QGrpcStatus &status)
    //    {
    //        if (status.code() == QtGrpc::StatusCode::Ok)
    //            emit auth();
    //        else if (status.code() == QtGrpc::StatusCode::Unauthenticated)
    //            emit networkError("This username with this password doesn't exists.");
    //        else
    //            emit networkError(status.message());
    //    },
    //    Qt::SingleShotConnection
    //);

    emit auth();
    //emit networkError("This username with this password doesn't exists.");
}

GrpcHardwareMonitor::HardwareStructure NetEngine::getHardwareStructure()
{
    //std::shared_ptr<QGrpcCallReply> replyHardwareStructure = m_client->getHardwareStructure(GrpcHardwareMonitor::None());

    //GrpcHardwareMonitor::HardwareStructure hardwareStructure;

    //connect(replyHardwareStructure.get(), &QGrpcCallReply::finished, this, [replyHardwareStructure, &hardwareStructure, this] (const QGrpcStatus &status)
    //    {
    //        if (status.code() == QtGrpc::StatusCode::Ok)
    //        {
    //            if(const auto hardwareStructureResponse = replyHardwareStructure->read<GrpcHardwareMonitor::HardwareStructure>())
    //                hardwareStructure = *hardwareStructureResponse;
    //        }
    //        else if(status.code() != QtGrpc::StatusCode::Ok)
    //            emit networkError(status.message());
    //    },
    //    Qt::SingleShotConnection
    //);

    //return hardwareStructure;

    GrpcHardwareMonitor::HardwareRepeated hardwares;

    GrpcHardwareMonitor::SensorRepeated sensors1;
    GrpcHardwareMonitor::Sensor sensor1;
    sensor1.setName("Clock1");
    sensor1.setType(GrpcHardwareMonitor::Sensor::SensorType::Clock);
    sensors1.append(sensor1);

    GrpcHardwareMonitor::Hardware hardware1;
    hardware1.setName("Cpu1");
    hardware1.setSensors(sensors1);
    hardware1.setType(GrpcHardwareMonitor::Hardware::HardwareType::Cpu);
    hardwares.append(hardware1);

    GrpcHardwareMonitor::SensorRepeated sensors2;
    GrpcHardwareMonitor::Sensor sensor2;
    sensor2.setName("Clock2");
    sensor2.setValue(2000);
    sensor2.setType(GrpcHardwareMonitor::Sensor::SensorType::Clock);
    sensors2.append(sensor2);

    GrpcHardwareMonitor::Hardware hardware2;
    hardware2.setName("Cpu2");
    hardware2.setSensors(sensors2);
    hardware2.setType(GrpcHardwareMonitor::Hardware::HardwareType::Cpu);
    hardwares.append(hardware2);

    GrpcHardwareMonitor::HardwareStructure hardwareStructure;
    hardwareStructure.setHardwares(hardwares);

    return hardwareStructure;
}
