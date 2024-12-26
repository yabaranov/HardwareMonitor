#include "HardwareListModel.h"
#include "HardwareService.qpb.h"

HardwareListModel::HardwareListModel(const GrpcHardwareMonitor::HardwareInfoRepeated& hardwareInfos)
{
    for(auto& hardwareInfo: hardwareInfos)
        m_hardwareNames.append(hardwareInfo.name());
}

int HardwareListModel::rowCount(const QModelIndex &parent) const
{
    return static_cast<int>(m_hardwareNames.size());
}

QVariant HardwareListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= static_cast<int>(m_hardwareNames.size()))
        return QVariant();

    const auto& hardwareName = m_hardwareNames[index.row()];

    if (role == Name)
        return hardwareName;

    return QVariant();
}

QHash<int, QByteArray> HardwareListModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[Name] = "name";

    return roles;
}
