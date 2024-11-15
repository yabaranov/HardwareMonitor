#pragma once
#include "DataBase/Database.h"
#include "HardwareService.qpb.h"

#include <QObject>

class NetEngine;

class SensorLogDatabase : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE bool open(const QString& dbPath);
    Q_INVOKABLE void close();

    Q_INVOKABLE void createTables(const GrpcHardwareMonitor::HardwareListInfo& hardwareListInfo);

    Q_INVOKABLE void connectToQObject(QObject* qObject);
    Q_INVOKABLE void disconnectFromQObject(QObject* qObject);

public Q_SLOTS:
    void onSensorTablesChanged(const GrpcHardwareMonitor::HardwareList& hardwareList);

private:
    void createTables();

    Database m_database;
    QList<QString> m_hardwaredNames;
    QList<QList<QString>> m_sensorsNames;

};
