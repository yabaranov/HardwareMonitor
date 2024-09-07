#pragma once
#include <QObject>
#include "HardwareTreeModel.h"
#include <QTimer>
class TreeViewController : public QObject
{
	Q_OBJECT

public:
	TreeViewController(QObject* parent = nullptr);
	~TreeViewController();

public:
	void makeThread();
	Q_INVOKABLE QAbstractItemModel* getTreeModel();

private:
	HardwareTreeModel* m_hardwareTreeModel;
	QTimer timer;
};