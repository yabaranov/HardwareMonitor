#pragma once

#include <QAbstractListModel>

namespace GrpcHardwareMonitor {
class HardwareInfo;
using HardwareInfoRepeated = QList<HardwareInfo>;
}

class HardwareListModel : public QAbstractListModel
{
public:
    explicit HardwareListModel(const GrpcHardwareMonitor::HardwareInfoRepeated& hardwareInfos);
    ~HardwareListModel() = default;
    HardwareListModel(HardwareListModel& rhs);
    HardwareListModel& operator=(HardwareListModel& rhs);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    enum HardwareRoles
    {
        Name = Qt::UserRole
    };

private:
    QList<QString> m_hardwareNames;
};
