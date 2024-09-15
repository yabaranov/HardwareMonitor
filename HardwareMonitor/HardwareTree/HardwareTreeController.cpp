#include <QThread.h>
#include <QAbstractItemModel>

#include "HardwareTreeController.h"
#include "HardwareTask.h"

HardwareTreeController::HardwareTreeController(QObject* parent) : QObject(parent)
{
   HardwareDataExtractor hardwareMonitorLib;
   m_hardwareTreeModel = std::make_unique<HardwareTreeModel>(hardwareMonitorLib.getHardwareData());
}

void HardwareTreeController::makeHardwareThread()
{
   HardwareTask* worker = new HardwareTask();
   QThread* thread = new QThread();

   worker->moveToThread(thread);

   connect(thread, &QThread::finished, worker, &QObject::deleteLater);

   connect(thread, &QThread::started, worker, &HardwareTask::process);

   connect(worker, &HardwareTask::sensorDataUpdated, m_hardwareTreeModel.get(), &HardwareTreeModel::updateModel);

   connect(&m_timer, &QTimer::timeout, worker, &HardwareTask::process);
   m_timer.start(1000);

   thread->start();
}

Q_INVOKABLE QAbstractItemModel* HardwareTreeController::getHardwareTreeModel()
{
   return m_hardwareTreeModel.get();
}
