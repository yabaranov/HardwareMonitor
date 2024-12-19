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
    ~HardwareListModel();
    HardwareListModel(HardwareListModel& rhs);
    HardwareListModel& operator=(HardwareListModel& rhs);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void swap(HardwareListModel& rhs) noexcept;

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

void swap(HardwareListModel& lhs, HardwareListModel& rhs) noexcept;
