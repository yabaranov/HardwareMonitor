#pragma once

#include <QObject>

#include "HardwareService.qpb.h"
#include "SensorTableModel.h"
#include "HardwareListModel.h"

class HardwarePageModel : public QObject
{
    Q_OBJECT
public:
    HardwarePageModel() = default;
    Q_INVOKABLE void initialize(GrpcHardwareMonitor::HardwareListInfo* hardwareListInfo);
    Q_INVOKABLE HardwareListModel* getHardwareList();
    Q_INVOKABLE SensorTableModel* getSensorTable(int index);
    Q_INVOKABLE void resetMinAndMax();
    ~HardwarePageModel() override;

public Q_SLOTS:
    void onSensorTablesChanged(const GrpcHardwareMonitor::HardwareList& hardwareList);

private:
    std::unique_ptr<HardwareListModel> m_hardwareModel;
    std::vector<std::unique_ptr<SensorTableModel>> m_sensorTables;
};
