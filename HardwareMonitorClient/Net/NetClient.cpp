#include "NetClient.h"
#include "SensorTask.h"

#include "HardwareService_client.grpc.qpb.h"

#include <QGrpcHttp2Channel>
#include <QGrpcChannelOptions>
#include <qprotobufregistration.h>

#include "Logger/Logger.h"

NetClient& NetClient::instance()
{
    static NetClient netEngine;
    return netEngine;
}

NetClient::~NetClient()
{
    logout();
}

void NetClient::login(const QUrl& hostUri, const QString &name, const QString &password)
{
    m_client = std::make_unique<GrpcHardwareMonitor::HardwareService::Client>();

    QHash<QByteArray, QByteArray> metadata =
        {
            { "Login", { name.toUtf8() } },
            { "Password", { password.toUtf8() } },
        };
    QGrpcChannelOptions channelOptions;
    channelOptions.setMetadata(metadata);

    std::shared_ptr<QAbstractGrpcChannel> channel = std::make_shared<QGrpcHttp2Channel>(hostUri, channelOptions);
    m_client->attachChannel(channel);

    std::shared_ptr<QGrpcCallReply> replyHardwareListInfo = m_client->getHardwareListInfo(GrpcHardwareMonitor::None());
    connect(replyHardwareListInfo.get(), &QGrpcCallReply::finished, this, [replyHardwareListInfo, this] (const QGrpcStatus &status)
        {
            if (status.code() == QtGrpc::StatusCode::Ok)
            {
                auto hardwareListInfo = std::make_unique<GrpcHardwareMonitor::HardwareListInfo>();
                if(const auto hardwareListInfoResponse = replyHardwareListInfo->read<GrpcHardwareMonitor::HardwareListInfo>())
                    *hardwareListInfo = *hardwareListInfoResponse;

                Logger::instance().info("Successful authentication");
                startSensorThread();
                emit auth(hardwareListInfo.get());
            }
            else if (status.code() == QtGrpc::StatusCode::Unauthenticated)
                emit networkError("This username with this password doesn't exists.");
            else
                emit networkError(status.message());
        },
        Qt::SingleShotConnection
    );

    //GrpcHardwareMonitor::HardwareInfoRepeated hardwares;

    //GrpcHardwareMonitor::SensorInfoRepeated sensors1;
    //GrpcHardwareMonitor::SensorInfo sensor1;
    //sensor1.setName("Clock1");
    //sensor1.setType(GrpcHardwareMonitor::SensorInfo::SensorType::Clock);
    //sensors1.append(sensor1);

    //GrpcHardwareMonitor::HardwareInfo hardware1;
    //hardware1.setName("Cpu1");
    //hardware1.setSensorInfos(sensors1);
    //hardwares.append(hardware1);

    //GrpcHardwareMonitor::SensorInfoRepeated sensors2;
    //GrpcHardwareMonitor::SensorInfo sensor2;
    //sensor2.setName("Clock2");
    //sensor2.setType(GrpcHardwareMonitor::SensorInfo::SensorType::Clock);
    //sensors2.append(sensor2);

    //GrpcHardwareMonitor::HardwareInfo hardware2;
    //hardware2.setName("Cpu2");
    //hardware2.setSensorInfos(sensors2);
    //hardwares.append(hardware2);

    //auto hardwareListInfo = std::make_unique<GrpcHardwareMonitor::HardwareListInfo>();
    //hardwareListInfo->setHardwareInfos(hardwares);

    //Logger::instance().info("Successful authentication");
    //startSensorThread();
    //emit auth(hardwareListInfo.get());

    ////emit networkError("This username with this password doesn't exists.");
}

Q_INVOKABLE void NetClient::logout()
{
    stopSensorThread(); 
    if(m_client) m_client.reset();
}

void NetClient::startSensorThread()
{
    m_sensorTask = std::make_unique<SensorTask>(m_client.get());
    m_sensorThread = std::make_unique<QThread>();
    m_sensorTask->moveToThread(m_sensorThread.get());

    connect(m_sensorTask.get(), &SensorTask::networkError, this,
            &NetClient::networkError);
    connect(m_sensorTask.get(), &SensorTask::sensorTablesChanged, this,
            &NetClient::sensorTablesChanged);

    m_sensorThread->start();
    m_sensorTask->changeSensorTables();
    Logger::instance().info("Start sensor thread");
}

void NetClient::stopSensorThread()
{
    if (m_sensorThread && m_sensorThread->isRunning())
    {
        m_sensorThread->quit();
        m_sensorThread->wait();

        disconnect(m_sensorTask.get(), &SensorTask::networkError, this,
                &NetClient::networkError);
        disconnect(m_sensorTask.get(), &SensorTask::sensorTablesChanged, this,
                &NetClient::sensorTablesChanged);

        m_sensorThread.reset();
        m_sensorTask.reset();
    }

    Logger::instance().info("Stop sensor thread");
}
