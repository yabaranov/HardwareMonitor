import QtQuick
import QtQuick.Controls

TreeView {
   id: treeView
   model: treeModel

   columnWidthProvider: 
      function(index) {
         const totalWidth = treeView.width;
         const columnCount = treeModel.columnCount()  
         const minSensorColumnWidth = 200
         const fixedColumnWidth = 80
   
         if (index === 0) {
             const availableWidth = totalWidth - (fixedColumnWidth * (columnCount - 1));
             return Math.max(minSensorColumnWidth, availableWidth);
         } else {
             return fixedColumnWidth;
         }  
      }

   delegate: Item {
      id: treeItemDelegate
                                   
      required property TreeView treeView              
      required property bool isTreeNode               
      required property bool expanded              
      required property int hasChildren                
      required property int depth

      readonly property real indent: 20
      readonly property real padding: 5  

      implicitWidth: padding + label.x + label.implicitWidth + padding
      implicitHeight: label.implicitHeight

      TreeConnector {
         id: treeConnector
         depth: treeItemDelegate.depth
         indent: treeItemDelegate.indent
         padding: treeItemDelegate.padding
         indicatorX: indicator.x
         indicatorWidth: indicator.width
         iconX: icon.x
      }

      onYChanged: {
         treeConnector.requestPaint();
      }
             
      TapHandler {
         onTapped: treeView.toggleExpanded(row)
      }

      readonly property string src: "qrc:/Resources/Images/"  
         
      Image {
         id: indicator
         visible: treeItemDelegate.isTreeNode && treeItemDelegate.hasChildren
         x: padding + (treeItemDelegate.depth * treeItemDelegate.indent)
         anchors.verticalCenter: parent.verticalCenter         
         readonly property string on: "on.png"
         readonly property string off: "off.png"
         source: treeItemDelegate.expanded ? src + off : src + on
      }  

      Image {
         id: icon
         visible: treeItemDelegate.isTreeNode && treeItemDelegate.hasChildren
         x: indicator.x + treeItemDelegate.indent
         anchors.verticalCenter: parent.verticalCenter
         source: src + model.icon
      }  
            
      Text {
         id: label
         x: treeItemDelegate.isTreeNode ? icon.x + treeItemDelegate.indent : padding
         anchors.verticalCenter: parent.verticalCenter
         width: treeItemDelegate.width - treeItemDelegate.padding - x
         elide: Text.ElideRight
         text: model.display
      }         
   }
  
   Component.onCompleted: {
      treeView.expandRecursively()
   }

   ScrollBar.vertical: CustomScrollBar {
      policy: ScrollBar.AlwaysOn
   }

   ScrollBar.horizontal: CustomScrollBar {
      policy: ScrollBar.AsNeeded
   }
}