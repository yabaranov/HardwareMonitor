#include "HardwareModel.h"

HardwareModel::HardwareModel(const GrpcHardwareMonitor::HardwareRepeated& hardwareList, QObject *parent) : QAbstractListModel(parent), m_hardwareList(hardwareList)
{
}

int HardwareModel::rowCount(const QModelIndex &parent) const
{
    return static_cast<int>(m_hardwareList.size());
}

QVariant HardwareModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= static_cast<int>(m_hardwareList.size()))
        return QVariant();

    const auto& hardware = m_hardwareList[index.row()];

    if (role == Name)
        return hardware.name();

    return QVariant();
}

QHash<int, QByteArray> HardwareModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[Name] = "name";

    return roles;
}

const GrpcHardwareMonitor::HardwareRepeated& HardwareModel::getHardwareList() const
{
    return m_hardwareList;
}
