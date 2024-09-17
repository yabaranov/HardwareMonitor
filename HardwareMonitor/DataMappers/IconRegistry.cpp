#include "IconRegistry.h"

const std::unordered_map<HardwareType, QString> IconRegistry::m_iconPaths =
{
    {HardwareType::Motherboard,        "mainboard.png"},
    {HardwareType::SuperIO,            "chip.png"},
    {HardwareType::Cpu,                "cpu.png"},
    {HardwareType::Memory,             "ram.png"},
    {HardwareType::GpuNvidia,          "nvidia.png"},
    {HardwareType::GpuAmd,             "amd.png"},
    {HardwareType::GpuIntel,           "intel.png"},
    {HardwareType::Storage,            "hdd.png"},
    {HardwareType::Network,            "nic.png"},
    {HardwareType::Cooler,             "fan.png"},
    {HardwareType::EmbeddedController, "chip.png"},
    {HardwareType::Psu,                "power-supply.png"},
    {HardwareType::Battery,            "battery.png"},
    {HardwareType::Voltage,            "voltage.png"},
    {HardwareType::Current,            "voltage.png"},
    {HardwareType::Power,              "power.png"},
    {HardwareType::Clock,              "clock.png"},
    {HardwareType::Temperature,        "temperature.png"},
    {HardwareType::Load,               "load.png"},
    {HardwareType::Frequency,          "clock.png"},
    {HardwareType::Fan,                "fan.png"},
    {HardwareType::Flow,               "flow.png"},
    {HardwareType::Control,            "control.png"},
    {HardwareType::Level,              "level.png"},
    {HardwareType::Factor,             "factor.png"},
    {HardwareType::Data,               "data.png"},
    {HardwareType::SmallData,          "data.png"},
    {HardwareType::Throughput,         "throughput.png"},
    {HardwareType::TimeSpan,           "time.png"},
    {HardwareType::Energy,             "battery.png"},
    {HardwareType::Noise,              "loudspeaker.png"},
    {HardwareType::Conductivity,       "voltage.png"},
    {HardwareType::Humidity,           "humidity.png"},
    {HardwareType::Unknown,            "transparent.png"},
};

const QString& IconRegistry::getIconPath(HardwareType hardwareType)
{
   auto it = m_iconPaths.find(hardwareType);
   return it != m_iconPaths.end() ? it->second : m_iconPaths.at(HardwareType::Unknown);
}