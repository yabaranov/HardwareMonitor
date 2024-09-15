import QtQuick
import QtQuick.Controls

Window {
   width: 600
   height: 900
   visible: true
   title: qsTr("Hardware monitor")
   
   property var treeModel: hardwareTreeController.getHardwareTreeModel()

   HorizontalHeaderView {
      id: header
      anchors.left: treeView.left
      anchors.right: parent.right
      anchors.top: parent.top
      syncView: treeView
      model: ["Sensor", "Value", "Min", "Max"]     
      delegate: Item {  
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
      anchors.left: parent.left
      anchors.top: header.bottom
      anchors.right: parent.right
      anchors.bottom: parent.bottom
      anchors.margins: 10
   }  
}