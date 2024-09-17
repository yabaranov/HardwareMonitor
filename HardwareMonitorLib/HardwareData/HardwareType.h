#pragma once

#include <cstdint>

enum class HardwareType : uint8_t
{
   Motherboard = 0,
   SuperIO,
   Cpu,
   Memory,
   GpuNvidia,
   GpuAmd,
   GpuIntel,
   Storage,
   Network,
   Cooler,
   EmbeddedController,
   Psu,
   Battery,
   Voltage,
   Current,
   Power,
   Clock,
   Temperature,
   Load,
   Frequency,
   Fan,
   Flow,
   Control,
   Level,
   Factor,
   Data,
   SmallData,
   Throughput,
   TimeSpan,
   Energy,
   Noise,
   Conductivity,
   Humidity,
   Unknown
};