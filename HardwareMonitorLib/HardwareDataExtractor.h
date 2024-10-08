#pragma once

#ifdef HARDWAREMONITORLIB_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

#include "HardwareData/Hardware.h"

#include <vector>
#include <memory>

struct ComputerWrapper;
struct UpdateVisitorWrapper;

class DLL_EXPORT HardwareDataExtractor
{
public:
   HardwareDataExtractor();
   ~HardwareDataExtractor();
   std::shared_ptr<Hardware> getHardwareData();

private:
   std::unique_ptr<ComputerWrapper> m_computer;
   std::unique_ptr<UpdateVisitorWrapper> m_updateVisitor;
};
