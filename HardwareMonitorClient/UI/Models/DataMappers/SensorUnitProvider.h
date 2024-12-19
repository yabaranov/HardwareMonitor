#pragma once

#include "HardwareService.qpb.h"
#include <QString>

class SensorUnitProvider
{
public:
    static const QString& getUnit(GrpcHardwareMonitor::SensorInfo::SensorType sensorType);

private:
    static const std::unordered_map<GrpcHardwareMonitor::SensorInfo::SensorType, QString> m_units;
};

