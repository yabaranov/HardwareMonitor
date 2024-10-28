#pragma once

#include <QAbstractListModel>

namespace GrpcHardwareMonitor {
class Hardware;
using HardwareRepeated = QList<Hardware>;
}

class HardwareModel : public QAbstractListModel
{
public:
    explicit HardwareModel(const GrpcHardwareMonitor::HardwareRepeated& hardwareList = {}, QObject *parent = nullptr);
    ~HardwareModel();
    HardwareModel(HardwareModel& rhs);
    HardwareModel& operator=(HardwareModel& rhs);

    const GrpcHardwareMonitor::HardwareRepeated& getHardwareList() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void swap(HardwareModel& rhs) noexcept;

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

void swap(HardwareModel& lhs, HardwareModel& rhs) noexcept;
