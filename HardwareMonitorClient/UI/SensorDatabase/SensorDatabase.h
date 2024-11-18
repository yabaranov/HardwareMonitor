#pragma once

#include "HardwareService.qpb.h"
#include "DataBase/Database.h"

#include <QObject>
#include <QThread>

class SensorDatabase : public QObject
{
    Q_OBJECT
public:
    SensorDatabase() = default;
    Q_INVOKABLE void open(const QString& dbPath, GrpcHardwareMonitor::HardwareListInfo* hardwareListInfo);
    ~SensorDatabase();

Q_SIGNALS:
    void sensorTablesChanged(const GrpcHardwareMonitor::HardwareList& hardwareList);

private:
    void createTables(GrpcHardwareMonitor::HardwareListInfo* hardwareListInfo);

    void startSensorLogThread(GrpcHardwareMonitor::HardwareListInfo* hardwareListInfo);
    void stopSensorLogThread();

    std::unique_ptr<Database> m_database;
    std::unique_ptr<QThread> m_sensorLogThread;
};
