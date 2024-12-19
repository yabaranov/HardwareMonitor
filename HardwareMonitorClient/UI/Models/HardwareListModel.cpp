#include "HardwareListModel.h"
#include "HardwareService.qpb.h"
#include "Types/Hardware.h"

class HardwareListModel::Impl
{
public:
    explicit Impl(const GrpcHardwareMonitor::HardwareInfoRepeated& hardwareInfos);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    enum HardwareRoles
    {
        Name = Qt::UserRole
    };

private:
    QList<Hardware> m_hardwares;
};

HardwareListModel::Impl::Impl(const GrpcHardwareMonitor::HardwareInfoRepeated& hardwareList)
{
    for(auto& hardware: hardwareList)
        m_hardwares.append(Hardware{.name = hardware.name()});
}

int HardwareListModel::Impl::rowCount(const QModelIndex &parent) const
{
    return static_cast<int>(m_hardwares.size());
}

QVariant HardwareListModel::Impl::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= static_cast<int>(m_hardwares.size()))
        return QVariant();

    const auto& hardware = m_hardwares[index.row()];

    if (role == Name)
        return hardware.name;

    return QVariant();
}

HardwareListModel::HardwareListModel(const GrpcHardwareMonitor::HardwareInfoRepeated& hardwareInfos)
    : pImpl(std::make_unique<Impl>(hardwareInfos))
{
}

int HardwareListModel::rowCount(const QModelIndex &parent) const
{
    return pImpl->rowCount(parent);
}

QVariant HardwareListModel::data(const QModelIndex &index, int role) const
{
    return pImpl->data(index, role);
}

QHash<int, QByteArray> HardwareListModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[pImpl->Name] = "name";

    return roles;
}

HardwareListModel::~HardwareListModel() = default;

HardwareListModel::HardwareListModel(HardwareListModel& rhs) : pImpl(nullptr)
{
    if(rhs.pImpl)
        pImpl = std::make_unique<Impl>(*rhs.pImpl);
}

HardwareListModel& HardwareListModel::operator=(HardwareListModel& rhs)
{
    if(!rhs.pImpl)
        pImpl.reset();
    else if(!pImpl)
        pImpl = std::make_unique<Impl>(*rhs.pImpl);
    else
        *pImpl = *rhs.pImpl;

    return *this;
}

void HardwareListModel::swap(HardwareListModel& rhs) noexcept
{
    using std::swap;
    swap(pImpl, rhs.pImpl);
}

void swap(HardwareListModel& lhs, HardwareListModel& rhs) noexcept {lhs.swap(rhs);}
