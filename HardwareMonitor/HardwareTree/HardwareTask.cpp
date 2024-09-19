#include "HardwareTask.h"
#include <QThread>

void HardwareTask::updateSensorData()
{
   auto rootItem = m_hardwareDataExtractor.getHardwareData();
   emit sensorDataUpdated(rootItem);
}

