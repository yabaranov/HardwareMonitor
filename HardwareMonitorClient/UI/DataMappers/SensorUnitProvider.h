#pragma once

#include "HardwareService.qpb.h"
#include <QString>

class SensorUnitProvider
{
public:
    static const QString& getUnit(GrpcHardwareMonitor::Sensor::SensorType sensorType);

private:
    static const std::unordered_map<GrpcHardwareMonitor::Sensor::SensorType, QString> m_units;
};

