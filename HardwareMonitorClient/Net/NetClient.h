#pragma once

#include <QObject>
#include <QTimer>
#include "HardwareService.qpb.h"

namespace GrpcHardwareMonitor
{
namespace HardwareService
{
class Client;
}
}

class NetClient : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE void login(const QUrl& hostUri, const QString &name, const QString &password);
    Q_INVOKABLE void logout();

    static NetClient& instance();

Q_SIGNALS:
    void networkError(const QString&);
    void auth(GrpcHardwareMonitor::HardwareListInfo*);
    void sensorTablesChanged(const GrpcHardwareMonitor::HardwareList&);

public Q_SLOTS:
    void changeSensorTables();

private:
    explicit NetClient() = default;
    ~NetClient() override;
    NetClient(const NetClient&);
    NetClient& operator=(const NetClient&);

    void startReceivingSensorData();
    void stopReceivingSensorData();

    std::unique_ptr<GrpcHardwareMonitor::HardwareService::Client> m_client;
    QTimer m_timer;
};
