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
    explicit NetEngine(QObject *parent = nullptr);
    ~NetEngine() override;
    Q_INVOKABLE void startSensorThread();
    Q_INVOKABLE void login(const QUrl& hostUri, const QString &name, const QString &password);
    Q_INVOKABLE GrpcHardwareMonitor::HardwareStructure getHardwareStructure();

Q_SIGNALS:
    void networkError(const QString&);
    void auth(bool state);
    void sensorChanged(const GrpcHardwareMonitor::SensorInfo&);

private:
    std::shared_ptr<GrpcHardwareMonitor::HardwareService::Client> m_client;
    std::unique_ptr<SensorThread> m_sensorThread;
};
