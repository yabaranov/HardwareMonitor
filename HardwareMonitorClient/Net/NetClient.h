#pragma once

#include <QObject>

#include "HardwareService.qpb.h"

#include <QThread>

namespace GrpcHardwareMonitor
{
namespace HardwareService
{
class Client;
}
}

class SensorTask;

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

private:
    explicit NetClient() = default;
    ~NetClient() override;
    NetClient(const NetClient&);
    NetClient& operator=(const NetClient&);

    void startSensorThread();
    void stopSensorThread();

    std::unique_ptr<GrpcHardwareMonitor::HardwareService::Client> m_client;
    std::unique_ptr<SensorTask> m_sensorTask;
};
