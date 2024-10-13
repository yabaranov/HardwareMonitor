#pragma once

#include <QAbstractListModel>

#include "HardwareService.qpb.h"

class HardwareModel : public QAbstractListModel
{
public:
    explicit HardwareModel(QObject *parent = nullptr);
    void setHardwareStructure(const GrpcHardwareMonitor::HardwareStructure& hardwareStructure);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:

    GrpcHardwareMonitor::HardwareStructure m_hardwareStructure;

    enum HardwareRoles
    {
        Name = Qt::UserRole + 1,
        IconSrc
    };

};

