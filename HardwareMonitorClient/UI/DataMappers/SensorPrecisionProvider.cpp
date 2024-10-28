#include "SensorPrecisionProvider.h"

const std::unordered_map<GrpcHardwareMonitor::Sensor::SensorType, quint32> SensorPrecisionProvider::m_precisions =
{
        {GrpcHardwareMonitor::Sensor::SensorType::Voltage,      3},
        {GrpcHardwareMonitor::Sensor::SensorType::Current,      3},
        {GrpcHardwareMonitor::Sensor::SensorType::Power,        1},
        {GrpcHardwareMonitor::Sensor::SensorType::Clock,        0},
        {GrpcHardwareMonitor::Sensor::SensorType::Temperature,  1},
        {GrpcHardwareMonitor::Sensor::SensorType::Load,         1},
        {GrpcHardwareMonitor::Sensor::SensorType::Frequency,    0},
        {GrpcHardwareMonitor::Sensor::SensorType::Fan,          0},
        {GrpcHardwareMonitor::Sensor::SensorType::Flow,         0},
        {GrpcHardwareMonitor::Sensor::SensorType::Control,      1},
        {GrpcHardwareMonitor::Sensor::SensorType::Level,        1},
        {GrpcHardwareMonitor::Sensor::SensorType::Factor,       3},
        {GrpcHardwareMonitor::Sensor::SensorType::Data,         1},
        {GrpcHardwareMonitor::Sensor::SensorType::SmallData,    0},
        {GrpcHardwareMonitor::Sensor::SensorType::Throughput,   0},
        {GrpcHardwareMonitor::Sensor::SensorType::TimeSpan,     3},
        {GrpcHardwareMonitor::Sensor::SensorType::Energy,       0},
        {GrpcHardwareMonitor::Sensor::SensorType::Noise,        0},
        {GrpcHardwareMonitor::Sensor::SensorType::Conductivity, 1},
        {GrpcHardwareMonitor::Sensor::SensorType::Humidity,     0},
        {GrpcHardwareMonitor::Sensor::SensorType::Unknown,      1}
};

quint32 SensorPrecisionProvider::getPrecision(GrpcHardwareMonitor::Sensor::SensorType sensorType)
{
    auto it = m_precisions.find(sensorType);
    return it != m_precisions.end() ? it->second : m_precisions.at(GrpcHardwareMonitor::Sensor::SensorType::Unknown);
}
