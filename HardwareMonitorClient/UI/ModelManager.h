#pragma once

#include <QObject>

#include "HardwareService.qpb.h"
#include "HardwareModel.h"
#include "SensorModel.h"

class ModelManager : public QObject
{
    Q_OBJECT
public:
    explicit ModelManager(QObject* parent = nullptr);
    Q_INVOKABLE void setHardwareStructure(const GrpcHardwareMonitor::HardwareStructure& hardwareStructure);
    Q_INVOKABLE HardwareModel* getHardwareModel();
    Q_INVOKABLE SensorModel* getSensorTable(int i);

public Q_SLOTS:
    void onSensorChanged(const GrpcHardwareMonitor::SensorInfo& sensorInfo);

private:
    GrpcHardwareMonitor::HardwareStructure m_hardwareStructure;
    HardwareModel m_hardwareModel;
    QList<std::shared_ptr<SensorModel>> m_sensorTables;
};
