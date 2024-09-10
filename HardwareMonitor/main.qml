import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window 
{
   width: 640
   height: 480
   visible: true
   title: qsTr("Hardware monitor")

   property var treeModel: treeViewController.getHardwareTreeModel()

   HorizontalHeaderView 
   {
        id: horizontalHeader
        anchors.left: treeView.left
        anchors.top: parent.top
        syncView: treeView
        model: ["Sensor", "Value", "Min", "Max"]
   }

   TreeView 
   {
      id: treeView
      anchors.left: parent.left
      anchors.top: horizontalHeader.bottom
      anchors.right: parent.right
      anchors.bottom: parent.bottom
      anchors.margins: 10
      model: treeModel
      delegate: TreeViewDelegate{}      
      Component.onCompleted: 
      {
        treeView.expandRecursively()
      }
   }
}