#pragma once

#include "HardwareService.qpb.h"
#include <QString>

class SensorPrecisionProvider
{
public:
    static quint32 getPrecision(GrpcHardwareMonitor::Sensor::SensorType sensorType);

private:
    static const std::unordered_map<GrpcHardwareMonitor::Sensor::SensorType, quint32> m_precisions;
};
