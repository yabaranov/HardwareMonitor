#pragma once
#include <msclr/auto_gcroot.h>

struct ComputerWrapper
{
   msclr::auto_gcroot<LibreHardwareMonitor::Hardware::Computer^> API;
};
