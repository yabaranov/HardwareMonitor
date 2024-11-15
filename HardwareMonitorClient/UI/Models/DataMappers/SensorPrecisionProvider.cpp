#include "SensorPrecisionProvider.h"

const std::unordered_map<GrpcHardwareMonitor::SensorInfo::SensorType, quint32> SensorPrecisionProvider::m_precisions =
{
    {GrpcHardwareMonitor::SensorInfo::SensorType::Voltage,      3},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Current,      3},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Power,        1},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Clock,        0},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Temperature,  1},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Load,         1},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Frequency,    0},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Fan,          0},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Flow,         0},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Control,      1},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Level,        1},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Factor,       3},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Data,         1},
    {GrpcHardwareMonitor::SensorInfo::SensorType::SmallData,    0},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Throughput,   0},
    {GrpcHardwareMonitor::SensorInfo::SensorType::TimeSpan,     3},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Energy,       0},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Noise,        0},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Conductivity, 1},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Humidity,     0},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Unknown,      1}
};

quint32 SensorPrecisionProvider::getPrecision(GrpcHardwareMonitor::SensorInfo::SensorType sensorType)
{
    auto it = m_precisions.find(sensorType);
    return it != m_precisions.end() ? it->second : m_precisions.at(GrpcHardwareMonitor::SensorInfo::SensorType::Unknown);
}
