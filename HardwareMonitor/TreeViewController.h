#pragma once
#include <QObject>
#include <QTimer>
#include <memory>
#include "HardwareTreeModel.h"

class TreeViewController : public QObject
{
	Q_OBJECT

public:
	TreeViewController(QObject* parent = nullptr);
public:
	void makeHardwareThread();
	Q_INVOKABLE QAbstractItemModel* getHardwareTreeModel();

private:
	std::unique_ptr<HardwareTreeModel> m_hardwareTreeModel;
	QTimer m_timer;
};