#include "SensorUnitProvider.h"

const std::unordered_map<GrpcHardwareMonitor::SensorInfo::SensorType, QString> SensorUnitProvider::m_units =
{
    {GrpcHardwareMonitor::SensorInfo::SensorType::Voltage,      "%1 V"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Current,      "%1 A"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Power,        "%1 W"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Clock,        "%1 MHz"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Temperature,  "%1 \u00B0C"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Load,         "%1 %"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Frequency,    "%1 Hz"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Fan,          "%1 RPM"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Flow,         "%1 L/h"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Control,      "%1 %"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Level,        "%1 %"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Factor,       "%1"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Data,         "%1 GB"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::SmallData,    "%1 MB"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Throughput,   "%1 B/s"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::TimeSpan,     "%1"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Energy,       "%1 mWh"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Noise,        "%1 dBA"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Conductivity, "%1 µS/cm"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Humidity,     "%1 %"},
    {GrpcHardwareMonitor::SensorInfo::SensorType::Unknown,      "%1"}
};

const QString& SensorUnitProvider::getUnit(GrpcHardwareMonitor::SensorInfo::SensorType sensorType)
{
    auto it = m_units.find(sensorType);
    return it != m_units.end() ? it->second : m_units.at(GrpcHardwareMonitor::SensorInfo::SensorType::Unknown);
}
