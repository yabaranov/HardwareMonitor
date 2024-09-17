#pragma once
#include "SensorFormatter.h"

const std::unordered_map<HardwareType, std::pair<QString, int>> SensorFormatter::m_formats =
{
   { HardwareType::Voltage,      { "%1 V", 3} },
   { HardwareType::Current,      { "%1 A", 3} },
   { HardwareType::Power,        { "%1 W", 1 } },
   { HardwareType::Clock,        { "%1 MHz", 0 } },
   { HardwareType::Temperature,  { "%1 \u00B0C", 1 } },
   { HardwareType::Load,         { "%1 %", 1 } },
   { HardwareType::Frequency,    { "%1 Hz", 0 } },
   { HardwareType::Fan,          { "%1 RPM", 0 } },
   { HardwareType::Flow,         { "%1 L/h", 0 } },
   { HardwareType::Control,      { "%1 %", 1 } },
   { HardwareType::Level,        { "%1 %", 1 } },
   { HardwareType::Factor,       { "%1", 3 } },
   { HardwareType::Data,         { "%1 GB", 1 } },
   { HardwareType::SmallData,    { "%1 MB", 0 } },
   { HardwareType::Throughput,   { "%1 B/s", 0 } },
   { HardwareType::TimeSpan,     { "%1", 3 } },
   { HardwareType::Energy,       { "%1 mWh", 0 } },
   { HardwareType::Noise,        { "%1 dBA", 0 } },
   { HardwareType::Conductivity, { "%1 µS/cm", 1} },
   { HardwareType::Humidity,     { "%1 %", 0 } },
   { HardwareType::Unknown,      { "%1", 1 } }
};

const std::pair<QString, int>& SensorFormatter::getFormat(HardwareType hardwareType)
{
   auto it = m_formats.find(hardwareType);
   return it != m_formats.end() ? it->second : m_formats.at(HardwareType::Unknown);
}
