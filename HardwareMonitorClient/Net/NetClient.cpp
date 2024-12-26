#include "NetClient.h"

#include "HardwareService_client.grpc.qpb.h"

#include <QGrpcChannelOptions>
#include <qprotobufregistration.h>
#include <QGrpcHttp2Channel>

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
    connect(replyHardwareListInfo.get(), &QGrpcCallReply::finished, this,
        [replyHardwareListInfo, this] (const QGrpcStatus &status)
        {
            if (status.code() == QtGrpc::StatusCode::Ok)
            {
                auto hardwareListInfo = std::make_unique<GrpcHardwareMonitor::HardwareListInfo>();
                if(const auto hardwareListInfoResponse = replyHardwareListInfo->read<GrpcHardwareMonitor::HardwareListInfo>())
                    *hardwareListInfo = *hardwareListInfoResponse;

                Logger::instance().info("Successful authentication");
                startReceivingSensorData();
                emit auth(hardwareListInfo.get());
            }
            else if (status.code() == QtGrpc::StatusCode::Unauthenticated)
                emit networkError("This username with this password doesn't exists.");
            else
                emit networkError(status.message());
        },
        Qt::SingleShotConnection
    );
}

Q_INVOKABLE void NetClient::logout()
{
    stopReceivingSensorData();
}

void NetClient::changeSensorTables()
{
    std::shared_ptr<QGrpcCallReply> replyHardwareList = m_client->getHardwareList(GrpcHardwareMonitor::None());
    connect(replyHardwareList.get(), &QGrpcCallReply::finished, this,
        [replyHardwareList, this] (const QGrpcStatus &status)
        {
            if (status.code() == QtGrpc::StatusCode::Ok)
            {
                if (const auto hardwareList = replyHardwareList->read<GrpcHardwareMonitor::HardwareList>())
                    emit sensorTablesChanged(*hardwareList);
            }
            else
                emit networkError(status.message());
        },
        Qt::SingleShotConnection
    );
}

void NetClient::startReceivingSensorData()
{
    m_timer.start(1000);
    connect(&m_timer, &QTimer::timeout, this, &NetClient::changeSensorTables);
    Logger::instance().info("Start receiving sensor data");
}

void NetClient::stopReceivingSensorData()
{
    m_timer.stop();
    disconnect(&m_timer, &QTimer::timeout, this, &NetClient::changeSensorTables);
    Logger::instance().info("Stop receiving sensor data");
}
