#include "IconRegistry.h"

const std::unordered_map<std::wstring, std::wstring> IconRegistry::m_iconPaths =
{
    {L"Motherboard",        L"mainboard.png"},
    {L"SuperIO",            L"chip.png"},
    {L"Cpu",                L"cpu.png"},
    {L"Memory",             L"ram.png"},
    {L"GpuNvidia",          L"nvidia.png"},
    {L"GpuAmd",             L"amd.png"},
    {L"GpuIntel",           L"intel.png"},
    {L"Storage",            L"hdd.png"},
    {L"Network",            L"nic.png"},
    {L"Cooler",             L"fan.png"},
    {L"EmbeddedController", L"chip.png"},
    {L"Psu",                L"power-supply.png"},
    {L"Battery",            L"battery.png"},
    {L"Voltage",            L"voltage.png"},
    {L"Current",            L"voltage.png"},
    {L"Power",              L"power.png"},
    {L"Clock",              L"clock.png"},
    {L"Temperature",        L"temperature.png"},
    {L"Load",               L"load.png"},
    {L"Frequency",          L"clock.png"},
    {L"Fan",                L"fan.png"},
    {L"Flow",               L"flow.png"},
    {L"Control",            L"control.png"},
    {L"Level",              L"level.png"},
    {L"Factor",             L"factor.png"},
    {L"Data",               L"data.png"},
    {L"SmallData",          L"data.png"},
    {L"Throughput",         L"throughput.png"},
    {L"TimeSpan",           L"time.png"},
    {L"Energy",             L"battery.png"},
    {L"Noise",              L"loudspeaker.png"},
    {L"Conductivity",       L"voltage.png"},
    {L"Humidity",           L"humidity.png"},
    {L"Unknown",            L"transparent.png"},
};


std::wstring_view IconRegistry::getIconPath(std::wstring_view sensorName)
{
   auto it = m_iconPaths.find(sensorName.data());
   return it != m_iconPaths.end() ? it->second : m_iconPaths.at(L"Unknown");
}