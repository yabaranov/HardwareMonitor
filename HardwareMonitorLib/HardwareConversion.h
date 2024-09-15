#pragma once
#include "HardwareData.h"
#include <msclr/marshal_cppstd.h>

std::shared_ptr<Hardware> convertHardware(LibreHardwareMonitor::Hardware::IHardware^ hw, std::shared_ptr<Hardware> parent);
void populateSensors(LibreHardwareMonitor::Hardware::IHardware^ hw, std::shared_ptr<Hardware> parent);
Hardware convertSensor(LibreHardwareMonitor::Hardware::ISensor^ sr);