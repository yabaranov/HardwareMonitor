#pragma once

#include <QThread>

#include "HardwareService.qpb.h"

#include "QTimer"

namespace GrpcHardwareMonitor
{
namespace HardwareService
{
class Client;
}
}

class SensorThread : public QThread
{
    Q_OBJECT
public:
    explicit SensorThread(std::shared_ptr<GrpcHardwareMonitor::HardwareService::Client> client, QObject* parent = nullptr);
    ~SensorThread() override = default;
    void run() override;

Q_SIGNALS:
    void networkError(const QString&);
    void sensorChanged(const GrpcHardwareMonitor::SensorInfo&);

private:
    std::shared_ptr<GrpcHardwareMonitor::HardwareService::Client> m_client;
    QTimer m_timer;
    int i{0};
};
