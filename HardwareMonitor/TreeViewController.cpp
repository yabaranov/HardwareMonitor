#include <QThread.h>
#include <QAbstractItemModel>
#include "TreeViewController.h"
#include "HardwareThreadWorker.h"
TreeViewController::TreeViewController(QObject* parent) : QObject(parent)
{
   HardwareMonitorLib hardwareMonitorLib;
   m_hardwareTreeModel = std::make_unique<HardwareTreeModel>(hardwareMonitorLib.getHardwareData());
}

void TreeViewController::makeHardwareThread()
{
   HardwareThreadWorker* worker = new HardwareThreadWorker();
   QThread* thread = new QThread();

   worker->moveToThread(thread);

   connect(thread, &QThread::finished, worker, &QObject::deleteLater);

   connect(thread, &QThread::started, worker, &HardwareThreadWorker::process);

   connect(worker, &HardwareThreadWorker::sensorDataUpdated, m_hardwareTreeModel.get(), &HardwareTreeModel::updateModel);

   connect(&m_timer, &QTimer::timeout, worker, &HardwareThreadWorker::process);
   m_timer.start(1000);

   thread->start();
}

Q_INVOKABLE QAbstractItemModel* TreeViewController::getHardwareTreeModel()
{
   return m_hardwareTreeModel.get();
}
