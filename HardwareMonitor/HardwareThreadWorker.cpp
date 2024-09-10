#include "HardwareThreadWorker.h"
#include <QThread>

void HardwareThreadWorker::process()
{
   auto rootItem = m_hardwareMonitorLib.getHardwareData();
   emit sensorDataUpdated(rootItem);
}

