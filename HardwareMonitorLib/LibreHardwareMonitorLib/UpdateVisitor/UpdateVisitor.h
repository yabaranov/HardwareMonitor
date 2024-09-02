#pragma once

public ref class UpdateVisitor : LibreHardwareMonitor::Hardware::IVisitor
{
public:
   virtual void VisitComputer(LibreHardwareMonitor::Hardware::IComputer^ computer);
   virtual void VisitHardware(LibreHardwareMonitor::Hardware::IHardware^ hardware);
   virtual void VisitSensor(LibreHardwareMonitor::Hardware::ISensor^ sensor);
   virtual void VisitParameter(LibreHardwareMonitor::Hardware::IParameter^ parameter);
};
