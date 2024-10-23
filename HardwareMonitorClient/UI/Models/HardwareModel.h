#pragma once

#include <QAbstractListModel>

#include "HardwareService.qpb.h"

class HardwareModel : public QAbstractListModel
{
public:
    explicit HardwareModel(const GrpcHardwareMonitor::HardwareRepeated& hardwareList, QObject *parent = nullptr);
    const GrpcHardwareMonitor::HardwareRepeated& getHardwareList() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    GrpcHardwareMonitor::HardwareRepeated m_hardwareList;

    enum HardwareRoles
    {
        Name = Qt::UserRole
    };

};

