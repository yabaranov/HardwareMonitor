#include "HardwareTask.h"
#include <QThread>

void HardwareTask::process()
{
   auto rootItem = m_hardwareDataExtractor.getHardwareData();
   emit sensorDataUpdated(rootItem);
}

