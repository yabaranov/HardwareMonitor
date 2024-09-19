#include <QThread.h>
#include <QAbstractItemModel>

#include "HardwareTreeController.h"
#include "HardwareTask.h"

HardwareTreeController::HardwareTreeController(QObject* parent) : QObject(parent)
{
   HardwareDataExtractor hardwareMonitorExtractor;
   m_hardwareTreeModel = std::make_unique<HardwareTreeModel>(hardwareMonitorExtractor.getHardwareData());
}

void HardwareTreeController::makeHardwareThread()
{
   HardwareTask* hardwareTask = new HardwareTask();
   QThread* thread = new QThread();

   hardwareTask->moveToThread(thread);

   connect(thread, &QThread::finished, hardwareTask, &QObject::deleteLater);

   connect(thread, &QThread::started, hardwareTask, &HardwareTask::updateSensorData);

   connect(hardwareTask, &HardwareTask::sensorDataUpdated, m_hardwareTreeModel.get(), &HardwareTreeModel::updateModel);

   connect(&m_timer, &QTimer::timeout, hardwareTask, &HardwareTask::updateSensorData);
   m_timer.start(1000);

   thread->start();
}

Q_INVOKABLE QAbstractItemModel* HardwareTreeController::getHardwareTreeModel()
{
   return m_hardwareTreeModel.get();
}
