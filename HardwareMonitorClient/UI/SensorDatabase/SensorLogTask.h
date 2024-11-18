#pragma once

#include <QObject>

#include "HardwareService.qpb.h"

class Database;

class SensorLogTask : public QObject
{
    Q_OBJECT
public:
    explicit SensorLogTask(Database* database, GrpcHardwareMonitor::HardwareListInfo* hardwareListInfo);

public Q_SLOTS:
    void onSensorTablesChanged(const GrpcHardwareMonitor::HardwareList&);

private:
    Database* m_database;

    QList<QString> m_hardwaredNames;
    QList<QList<QString>> m_sensorTableNames;
};
