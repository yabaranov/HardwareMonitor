#include "HardwareTreeModel.h"


HardwareTreeModel::HardwareTreeModel(std::shared_ptr<Hardware> rootItem, QObject* parent) : QAbstractItemModel(parent), m_rootItem(rootItem)
{ 
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

void HardwareTreeModel::updateNode(std::shared_ptr<Hardware> currentNode, std::shared_ptr<Hardware> newNode)
{
   if (currentNode->sensor.value != newNode->sensor.value)
   {
      QModelIndex index = createIndex(currentNode->position(), 1, currentNode.get());
      currentNode->sensor.value = newNode->sensor.value;
      emit dataChanged(index, index);
   }

   if (currentNode->sensor.min != newNode->sensor.min)
   {
      QModelIndex index = createIndex(currentNode->position(), 2, currentNode.get());
      currentNode->sensor.min = newNode->sensor.min;
      emit dataChanged(index, index);
   }

   if (currentNode->sensor.max != newNode->sensor.max)
   {
      QModelIndex index = createIndex(currentNode->position(), 3, currentNode.get());
      currentNode->sensor.max = newNode->sensor.max;
      emit dataChanged(index, index);
   }

   // Рекурсивно обходим дочерние узлы
   for (size_t i = 0; i < currentNode->children.size(); ++i) {
      updateNode(currentNode->children[i], newNode->children[i]);
   }
}

void HardwareTreeModel::updateItems(std::shared_ptr<Hardware> rootItem)
{
   /*beginResetModel();
   m_rootItem = rootItem;
   endResetModel();*/

   updateNode(m_rootItem, rootItem);
}

