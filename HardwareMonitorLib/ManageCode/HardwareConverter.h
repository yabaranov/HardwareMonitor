#pragma once
#include "../HardwareData/Hardware.h"
#include <msclr/marshal_cppstd.h>

class HardwareConverter
{
public:
   static std::shared_ptr<Hardware> convertHardware(LibreHardwareMonitor::Hardware::IHardware^ hw, std::shared_ptr<Hardware> parent);

private:
   static void mapSensorsToHardware(LibreHardwareMonitor::Hardware::IHardware^ hw, std::shared_ptr<Hardware> parent);
   static Hardware convertSensor(LibreHardwareMonitor::Hardware::ISensor^ sr);
};
