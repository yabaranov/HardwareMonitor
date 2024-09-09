#pragma once

#ifdef HARDWAREMONITORLIB_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

#include "HardwareData.h"

#include <vector>
#include <memory>

class ComputerWrapper;
class UpdateVisitorWrapper;

class DLL_EXPORT HardwareMonitorLib
{
public:
   HardwareMonitorLib();
   ~HardwareMonitorLib();
   std::shared_ptr<Hardware> getHardwareData();

private:
   std::unique_ptr<ComputerWrapper> m_computer;
   std::unique_ptr<UpdateVisitorWrapper> m_updateVisitor;
};
