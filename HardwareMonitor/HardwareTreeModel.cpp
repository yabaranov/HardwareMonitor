#include "HardwareTreeModel.h"


HardwareTreeModel::HardwareTreeModel(QObject* parent) : QAbstractItemModel(parent)
{ 
   m_rootItem = std::make_shared<Hardware>(L"");  
}

QModelIndex HardwareTreeModel::index(int row, int column, const QModelIndex& parent) const
{
   if (!hasIndex(row, column, parent))
      return QModelIndex();

   auto parentItem = getItem(parent);
   auto childPtr = parentItem->children.at(row);
   return (childPtr) ? createIndex(row, column, childPtr.get()) : QModelIndex();
}

QModelIndex HardwareTreeModel::parent(const QModelIndex& index) const
{
   if (!index.isValid()) 
   {
      return QModelIndex();
   }
   auto childItem = getItem(index);
   auto parentPtr = childItem->parent.lock();

   if (!parentPtr || parentPtr == m_rootItem)
   {
      return QModelIndex();
   }

   return createIndex(parentPtr.get()->position(), 0, parentPtr.get());
}

int HardwareTreeModel::rowCount(const QModelIndex& parent) const
{
   auto parentItem = getItem(parent);
   return static_cast<int>(parentItem->children.size());
}

int HardwareTreeModel::columnCount(const QModelIndex& parent) const
{
   auto parentItem = getItem(parent);
   return 4;
}

QVariant HardwareTreeModel::data(const QModelIndex& index, int role) const {
   if (!index.isValid())
      return QVariant();

   auto item = getItem(index);

   if (role == Qt::DisplayRole)
   {
      role = Qt::UserRole + index.column();
   }
   switch (role) 
   {
   case NameRole: return QString::fromStdWString(item->name);
   case ValueRole: return QString::fromStdWString(item->sensor.value);
   case MinRole: return QString::fromStdWString(item->sensor.min);
   case MaxRole: return QString::fromStdWString(item->sensor.max);
   default: break;
   }
   return QVariant();
}

QHash<int, QByteArray> HardwareTreeModel::roleNames() const {
   QHash<int, QByteArray> names = QAbstractItemModel::roleNames();
   names[NameRole] = "name";
   names[ValueRole] = "valueRole";
   names[MinRole] = "minRole";
   names[MaxRole] = "maxRole";

   return names;
}

Hardware* HardwareTreeModel::getItem(const QModelIndex& index) const
{
   if (index.isValid()) 
   {
      return static_cast<Hardware*>(index.internalPointer());
   }
   return m_rootItem.get();
}

void HardwareTreeModel::resetItems(std::shared_ptr<Hardware> rootItem)
{
   beginResetModel();
   m_rootItem = rootItem;
   endResetModel();
   emit dataChanged();
}

