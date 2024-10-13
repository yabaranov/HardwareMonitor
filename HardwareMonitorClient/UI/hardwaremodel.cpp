#include "HardwareModel.h"

HardwareModel::HardwareModel(QObject *parent)
{

};

void HardwareModel::setHardwareStructure(const GrpcHardwareMonitor::HardwareStructure& hardwareStructure)
{
    m_hardwareStructure = hardwareStructure;
}

int HardwareModel::rowCount(const QModelIndex &parent) const
{
    return static_cast<int>(m_hardwareStructure.hardwares().size());
}

QVariant HardwareModel::data(const QModelIndex &index, int role) const
{
    auto& hardwares = m_hardwareStructure.hardwares();
    if (!index.isValid() || index.row() >= static_cast<int>(hardwares.size()))
        return QVariant();

    const auto& hardware = hardwares[index.row()];

    if (role == Name)
        return hardware.name();

    if (role == IconSrc)
    {
        return "-";
    }

    return QVariant();
}

QHash<int, QByteArray> HardwareModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[Name] = "name";
    roles[IconSrc] = "iconSrc";

    return roles;
}
