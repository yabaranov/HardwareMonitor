import QtQuick
import QtQuick.Controls

TreeView {
   id: treeView
   property var treeModel: hardwareTreeController.getHardwareTreeModel()
   model: treeModel

   columnWidthProvider: 
      function(index) {
         const totalWidth = treeView.width;
         const columnCount = model.columnCount()  
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

   delegate: HardwareTreeDelegate{
   }
  
   Component.onCompleted: {
      treeView.expandRecursively()
   }

   ScrollBar.vertical: CustomScrollBar {
      policy: ScrollBar.AlwaysOn
      smooth: true
   }

   ScrollBar.horizontal: CustomScrollBar {
      policy: ScrollBar.AsNeeded
      smooth: true
   }
}