#pragma once
#include "SensorFormatter.h"

const std::unordered_map<std::wstring, std::wstring> SensorFormatter::m_formats =
{
    {L"Voltage",      L"{:.3f} V"},
    {L"Current",      L"{:.3f} A"},
    {L"Power",        L"{:.1f} W"},
    {L"Clock",        L"{:.0f} MHz"},
    {L"Temperature",  L"{:.1f} °C"},
    {L"Load",         L"{:.1f} %"},
    {L"Frequency",    L"{:.0f} Hz"},
    {L"Fan",          L"{:.0f} RPM"},
    {L"Flow",         L"{:.0f} L/h"},
    {L"Control",      L"{:.1f} %"},
    {L"Level",        L"{:.1f} %"},
    {L"Factor",       L"{:.3f}"},
    {L"Data",         L"{:.1f} GB"},
    {L"SmallData",    L"{:.0f} MB"},
    {L"Throughput",   L"{:.0f} B/s"},
    {L"TimeSpan",     L"{:.3g}"},
    {L"Energy",       L"{:.0f} mWh"},
    {L"Noise",        L"{:.0f} dBA"},
    {L"Conductivity", L"{:.1f} µS/cm"},
    {L"Humidity",     L"{:.0f} %"},
    {L"Unknown",      L"{:.1f}"},
};


std::wstring_view SensorFormatter::getFormat(std::wstring_view sensorName)
{
   auto it = m_formats.find(sensorName.data());
   return it != m_formats.end() ? it->second : m_formats.at(L"Unknown");
}
