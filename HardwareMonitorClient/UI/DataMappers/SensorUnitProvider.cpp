#include "SensorUnitProvider.h"

const std::unordered_map<GrpcHardwareMonitor::Sensor::SensorType, QString> SensorUnitProvider::m_units =
    {
        {GrpcHardwareMonitor::Sensor::SensorType::Voltage,      "%1 V"},
        {GrpcHardwareMonitor::Sensor::SensorType::Current,      "%1 A"},
        {GrpcHardwareMonitor::Sensor::SensorType::Power,        "%1 W"},
        {GrpcHardwareMonitor::Sensor::SensorType::Clock,        "%1 MHz"},
        {GrpcHardwareMonitor::Sensor::SensorType::Temperature,  "%1 \u00B0C"},
        {GrpcHardwareMonitor::Sensor::SensorType::Load,         "%1 %"},
        {GrpcHardwareMonitor::Sensor::SensorType::Frequency,    "%1 Hz"},
        {GrpcHardwareMonitor::Sensor::SensorType::Fan,          "%1 RPM"},
        {GrpcHardwareMonitor::Sensor::SensorType::Flow,         "%1 L/h"},
        {GrpcHardwareMonitor::Sensor::SensorType::Control,      "%1 %"},
        {GrpcHardwareMonitor::Sensor::SensorType::Level,        "%1 %"},
        {GrpcHardwareMonitor::Sensor::SensorType::Factor,       "%1"},
        {GrpcHardwareMonitor::Sensor::SensorType::Data,         "%1 GB"},
        {GrpcHardwareMonitor::Sensor::SensorType::SmallData,    "%1 MB"},
        {GrpcHardwareMonitor::Sensor::SensorType::Throughput,   "%1 B/s"},
        {GrpcHardwareMonitor::Sensor::SensorType::TimeSpan,     "%1"},
        {GrpcHardwareMonitor::Sensor::SensorType::Energy,       "%1 mWh"},
        {GrpcHardwareMonitor::Sensor::SensorType::Noise,        "%1 dBA"},
        {GrpcHardwareMonitor::Sensor::SensorType::Conductivity, "%1 µS/cm"},
        {GrpcHardwareMonitor::Sensor::SensorType::Humidity,     "%1 %"},
        {GrpcHardwareMonitor::Sensor::SensorType::Unknown,      "%1"}
};

const QString& SensorUnitProvider::getUnit(GrpcHardwareMonitor::Sensor::SensorType sensorType)
{
    auto it = m_units.find(sensorType);
    return it != m_units.end() ? it->second : m_units.at(GrpcHardwareMonitor::Sensor::SensorType::Unknown);
}
