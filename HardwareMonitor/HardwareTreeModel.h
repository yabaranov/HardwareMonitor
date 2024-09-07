#pragma once

#include <QAbstractItemModel>
#include <qqml.h>
#include "HardwareData.h"


class HardwareTreeModel : public QAbstractItemModel
{
   Q_OBJECT
   QML_ELEMENT

private:
   enum RoleType
   {
      NameRole = Qt::UserRole,
      ValueRole,
      MinRole, 
      MaxRole
   };

public:
   explicit HardwareTreeModel(QObject* parent = nullptr);

   QModelIndex index(int row, int column,
      const QModelIndex& parent = QModelIndex()) const override;
   QModelIndex parent(const QModelIndex& index) const override;
   int rowCount(const QModelIndex& parent = QModelIndex()) const override;
   int columnCount(const QModelIndex& parent = QModelIndex()) const override;
   QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
   QHash<int, QByteArray> roleNames() const override;

signals:
   void dataChanged();

public slots:
   void resetItems(std::shared_ptr<Hardware> rootItem);

private:
   Hardware* getItem(const QModelIndex& index) const;
   std::shared_ptr<Hardware> m_rootItem;

};