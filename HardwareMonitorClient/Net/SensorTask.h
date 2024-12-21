#pragma once

#include <QObject>

#include "HardwareService.qpb.h"
#include "HardwareService_client.grpc.qpb.h"

#include "QTimer"

namespace GrpcHardwareMonitor
{
namespace HardwareService
{
class Client;
}
}

class SensorTask : public QObject
{
    Q_OBJECT
public:
    explicit SensorTask(GrpcHardwareMonitor::HardwareService::Client* client);

Q_SIGNALS:
    void networkError(const QString&);
    void sensorTablesChanged(const GrpcHardwareMonitor::HardwareList&);

public Q_SLOTS:
    void changeSensorTables();
    void getHardwareList(const QGrpcStatus &status);

private:
    GrpcHardwareMonitor::HardwareService::Client* m_client;
    std::shared_ptr<QGrpcCallReply> replyHardwareList;
    QTimer m_timer;
};
