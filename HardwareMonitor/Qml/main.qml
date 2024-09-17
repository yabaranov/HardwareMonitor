import QtQuick
import QtQuick.Controls

Window {
   width: 600
   height: 900
   visible: true
   title: "Hardware monitor"
   
   property var treeModel: hardwareTreeController.getHardwareTreeModel()

   Column {
      anchors.fill: parent
      anchors.leftMargin: 10

      HorizontalHeaderView {
         id: header
         width: parent.width
         syncView: treeView
         model: ["Sensor", "Value", "Min", "Max"]     
         resizableColumns: false
         delegate: Item {  

         implicitWidth: 80
         implicitHeight: 50
            Label {
               anchors.fill: parent
               text: modelData
               horizontalAlignment: Text.AlignLeft
               verticalAlignment: Text.AlignVCenter
            }
         }
      }

      HardwareTreeView {
         id: treeView        
         width: parent.width
         height: parent.height - header.implicitHeight         
      }  
   }
}