#pragma once

#include <QObject>

#include "HardwareService.qpb.h"
#include "SensorModel.h"
#include "HardwareModel.h"

class ModelManager : public QObject
{
    Q_OBJECT
public:
    explicit ModelManager(QObject* parent = nullptr);
    Q_INVOKABLE void createModels(const GrpcHardwareMonitor::HardwareStructure& hardwareStructure);
    Q_INVOKABLE void destroyModels();
    Q_INVOKABLE HardwareModel* getHardwareModel();
    Q_INVOKABLE SensorModel* getSensorTable(int index);
    Q_INVOKABLE void resetMinAndMax();

public Q_SLOTS:
    void onSensorChanged(const GrpcHardwareMonitor::SensorInfo& sensorInfo);

private:
    std::unique_ptr<HardwareModel> m_hardwareModel;
    std::vector<std::unique_ptr<SensorModel>> m_sensorTables;
};
