#pragma once
#include "../../HardwareData.h"
#include <msclr/marshal_cppstd.h>

std::shared_ptr<Hardware> ConvertHardware(LibreHardwareMonitor::Hardware::IHardware^ hw, std::shared_ptr<Hardware> parent);