#include "NetEngine.h"
#include "SensorThread.h"

#include "HardwareService_client.grpc.qpb.h"

#include <QGrpcHttp2Channel>
#include <QGrpcChannelOptions>
#include <qprotobufregistration.h>

#include "Logger/Logger.h"

NetEngine::NetEngine(QObject *parent)
    : QObject(parent),
      m_client(std::make_unique<GrpcHardwareMonitor::HardwareService::Client>())
{
}

NetEngine& NetEngine::instance()
{
    static NetEngine netEngine;
    return netEngine;
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
    connect(m_sensorThread.get(), &SensorThread::sensorTablesChanged, this,
            &NetEngine::sensorTablesChanged, Qt::QueuedConnection);

    m_sensorThread->start();
    Logger::instance().info("Start sensor thread");
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
    disconnect(m_sensorThread.get(), &SensorThread::sensorTablesChanged, this,
            &NetEngine::sensorTablesChanged);

    m_sensorThread.reset();

    Logger::instance().info("Stop sensor thread");
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

GrpcHardwareMonitor::HardwareListInfo NetEngine::getHardwareListInfo()
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

    GrpcHardwareMonitor::HardwareInfoRepeated hardwares;

    GrpcHardwareMonitor::SensorInfoRepeated sensors1;
    GrpcHardwareMonitor::SensorInfo sensor1;
    sensor1.setName("Clock1");
    sensor1.setType(GrpcHardwareMonitor::SensorInfo::SensorType::Clock);
    sensors1.append(sensor1);

    GrpcHardwareMonitor::HardwareInfo hardware1;
    hardware1.setName("Cpu1");
    hardware1.setSensorInfos(sensors1);
    hardwares.append(hardware1);

    GrpcHardwareMonitor::SensorInfoRepeated sensors2;
    GrpcHardwareMonitor::SensorInfo sensor2;
    sensor2.setName("Clock2");
    sensor2.setType(GrpcHardwareMonitor::SensorInfo::SensorType::Clock);
    sensors2.append(sensor2);

    GrpcHardwareMonitor::HardwareInfo hardware2;
    hardware2.setName("Cpu2");
    hardware2.setSensorInfos(sensors2);
    hardwares.append(hardware2);

    GrpcHardwareMonitor::HardwareListInfo hardwareListInfo;
    hardwareListInfo.setHardwareInfos(hardwares);

    return hardwareListInfo;
}
