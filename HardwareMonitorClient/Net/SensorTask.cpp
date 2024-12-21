#include "SensorTask.h"

#include "HardwareService_client.grpc.qpb.h"

SensorTask::SensorTask(GrpcHardwareMonitor::HardwareService::Client* client)
    : m_client(client)
{
    m_timer.start(1000);
    connect(&m_timer, &QTimer::timeout, this, &SensorTask::changeSensorTables);
}

void SensorTask::changeSensorTables()
{
    replyHardwareList = m_client->getHardwareList(GrpcHardwareMonitor::None());
    connect(replyHardwareList.get(), &QGrpcCallReply::finished, this, &SensorTask::getHardwareList);
}

void SensorTask::getHardwareList(const QGrpcStatus &status)
{
    if (status.code() == QtGrpc::StatusCode::Ok)
    {
        if (const auto hardwareList = replyHardwareList->read<GrpcHardwareMonitor::HardwareList>())
            emit sensorTablesChanged(*hardwareList);
    }
    else
        emit networkError(status.message());
}
