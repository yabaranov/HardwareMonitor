#pragma once

#include <QObject>

#include "HardwareService.qpb.h"

namespace GrpcHardwareMonitor
{
namespace HardwareService
{
class Client;
}
}

class SensorThread;

class NetEngine : public QObject
{
    Q_OBJECT

public :
    Q_INVOKABLE void startSensorThread();
    Q_INVOKABLE void stopSensorThread();
    Q_INVOKABLE void login(const QUrl& hostUri, const QString &name, const QString &password);
    Q_INVOKABLE GrpcHardwareMonitor::HardwareListInfo getHardwareListInfo();

    static NetEngine& instance();

Q_SIGNALS:
    void networkError(const QString&);
    void auth();
    void sensorTablesChanged(const GrpcHardwareMonitor::HardwareList&);

private:
    explicit NetEngine(QObject *parent = nullptr);
    ~NetEngine() override;
    NetEngine(const NetEngine&);
    NetEngine& operator=(const NetEngine&);

    std::unique_ptr<GrpcHardwareMonitor::HardwareService::Client> m_client;
    std::unique_ptr<SensorThread> m_sensorThread;
};
