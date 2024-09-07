#include "Controller.h"
#include "Worker.h"
#include <qthread.h>

TreeViewController::TreeViewController(QObject* parent)
{
   m_hardwareTreeModel = new HardwareTreeModel();
}

TreeViewController::~TreeViewController()
{
   delete m_hardwareTreeModel;
}

void TreeViewController::makeThread()
{
   Worker* worker = new Worker();
   QThread* thread = new QThread();

   worker->moveToThread(thread);

   connect(thread, &QThread::finished, worker, &QObject::deleteLater);

   connect(thread, &QThread::started, worker, &Worker::process);

   connect(worker, &Worker::sensorDataUpdated, m_hardwareTreeModel, &HardwareTreeModel::resetItems);

   connect(&timer, &QTimer::timeout, worker, &Worker::process);
   timer.start(1000);

   thread->start();

}

Q_INVOKABLE QAbstractItemModel* TreeViewController::getTreeModel()
{
   return m_hardwareTreeModel;
}
