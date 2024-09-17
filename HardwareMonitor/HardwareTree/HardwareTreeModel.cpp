#include "HardwareTreeModel.h"
#include "../DataMappers/SensorFormatter.h"
#include "../DataMappers/IconRegistry.h"

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

   return createIndex(parentPtr.get()->indexInParent(), 0, parentPtr.get());
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

QVariant HardwareTreeModel::data(const QModelIndex& index, int role) const 
{
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
      case ValueRole: case MinRole: case MaxRole: 
         if (item->children.empty())
         {
            auto parentType = item->parent.lock()->type;
            auto value = item->values[index.column() - 1];
            auto format = SensorFormatter::getFormat(parentType);
            return value.has_value() ? format.first.arg(*value, 0, 'f', format.second) : "-";
         }   
         else
            return "";
      case IconRole: return IconRegistry::getIconPath(item->type);
      default: break;
   }
   return QVariant();
}

QHash<int, QByteArray> HardwareTreeModel::roleNames() const 
{
   QHash<int, QByteArray> names = QAbstractItemModel::roleNames();
   names[NameRole] =  "name";
   names[ValueRole] = "value";
   names[MinRole] =   "min";
   names[MaxRole] =   "max";
   names[IconRole] =  "icon";

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

void HardwareTreeModel::updateItems(std::shared_ptr<Hardware> currentNode, std::shared_ptr<Hardware> newNode)
{
   if (!currentNode->values.empty())
   {
      for (size_t i = 0; i < currentNode->values.size(); i++)
      {
         if (currentNode->values[i] != newNode->values[i])
         {
            QModelIndex index = createIndex(currentNode->indexInParent(), i + 1, currentNode.get());
            currentNode->values[i] = newNode->values[i];
            emit dataChanged(index, index);
         }
      }
   }
      
   for (size_t i = 0; i < currentNode->children.size(); ++i) 
   {
      updateItems(currentNode->children[i], newNode->children[i]);
   }
}

void HardwareTreeModel::updateModel(std::shared_ptr<Hardware> rootItem)
{
   updateItems(m_rootItem, rootItem);
}

