#pragma once

#include <QAbstractListModel>

namespace GrpcHardwareMonitor {
class HardwareInfo;
using HardwareInfoRepeated = QList<HardwareInfo>;
}

class HardwareModel : public QAbstractListModel
{
public:
    explicit HardwareModel(const GrpcHardwareMonitor::HardwareInfoRepeated& hardwareInfos, QObject *parent = nullptr);
    ~HardwareModel();
    HardwareModel(HardwareModel& rhs);
    HardwareModel& operator=(HardwareModel& rhs);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void swap(HardwareModel& rhs) noexcept;

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

void swap(HardwareModel& lhs, HardwareModel& rhs) noexcept;
