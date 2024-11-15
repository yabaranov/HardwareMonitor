#include "HardwareModel.h"
#include "HardwareService.qpb.h"
#include "Types/Hardware.h"

class HardwareModel::Impl
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

HardwareModel::Impl::Impl(const GrpcHardwareMonitor::HardwareInfoRepeated& hardwareList)
{
    for(auto& hardware: hardwareList)
        m_hardwares.append(Hardware{.name = hardware.name()});
}

int HardwareModel::Impl::rowCount(const QModelIndex &parent) const
{
    return static_cast<int>(m_hardwares.size());
}

QVariant HardwareModel::Impl::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= static_cast<int>(m_hardwares.size()))
        return QVariant();

    const auto& hardware = m_hardwares[index.row()];

    if (role == Name)
        return hardware.name;

    return QVariant();
}

HardwareModel::HardwareModel(const GrpcHardwareMonitor::HardwareInfoRepeated& hardwareInfos, QObject *parent)
    : QAbstractListModel(parent),
      pImpl(std::make_unique<Impl>(hardwareInfos))
{
}

int HardwareModel::rowCount(const QModelIndex &parent) const
{
    return pImpl->rowCount(parent);
}

QVariant HardwareModel::data(const QModelIndex &index, int role) const
{
    return pImpl->data(index, role);
}

QHash<int, QByteArray> HardwareModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[pImpl->Name] = "name";

    return roles;
}

HardwareModel::~HardwareModel() = default;

HardwareModel::HardwareModel(HardwareModel& rhs) : pImpl(nullptr)
{
    if(rhs.pImpl)
        pImpl = std::make_unique<Impl>(*rhs.pImpl);
}

HardwareModel& HardwareModel::operator=(HardwareModel& rhs)
{
    if(!rhs.pImpl)
        pImpl.reset();
    else if(!pImpl)
        pImpl = std::make_unique<Impl>(*rhs.pImpl);
    else
        *pImpl = *rhs.pImpl;

    return *this;
}

void HardwareModel::swap(HardwareModel& rhs) noexcept
{
    using std::swap;
    swap(pImpl, rhs.pImpl);
}

void swap(HardwareModel& lhs, HardwareModel& rhs) noexcept {lhs.swap(rhs);}
