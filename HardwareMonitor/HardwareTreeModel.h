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
   explicit HardwareTreeModel(std::shared_ptr<Hardware> rootItem, QObject* parent = nullptr);

   QModelIndex index(int row, int column,
      const QModelIndex& parent = QModelIndex()) const override;
   QModelIndex parent(const QModelIndex& index) const override;
   int rowCount(const QModelIndex& parent = QModelIndex()) const override;
   int columnCount(const QModelIndex& parent = QModelIndex()) const override;
   QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
   QHash<int, QByteArray> roleNames() const override;
public slots:
   void updateModel(std::shared_ptr<Hardware> rootItem);

private:
   Hardware* getItem(const QModelIndex& index) const;
   void updateItems(std::shared_ptr<Hardware> currentNode, std::shared_ptr<Hardware> newNode);
   std::shared_ptr<Hardware> m_rootItem;

};