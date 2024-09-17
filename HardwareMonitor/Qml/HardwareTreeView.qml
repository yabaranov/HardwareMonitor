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

   readonly property string src: "qrc:/Resources/Images/"
   readonly property string on: "on.png"
   readonly property string off: "off.png"
   readonly property real indent: 20
   readonly property real padding: 5 

   delegate: HardwareTreeDelegate{
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