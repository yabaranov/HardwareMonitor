#pragma once

#include "HardwareService.qpb.h"
#include <QString>

class SensorPrecisionProvider
{
public:
    static quint32 getPrecision(GrpcHardwareMonitor::SensorInfo::SensorType sensorType);

private:
    static const std::unordered_map<GrpcHardwareMonitor::SensorInfo::SensorType, quint32> m_precisions;
};
