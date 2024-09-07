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

   TreeView 
   {
      id: control
      anchors.fill: parent
      anchors.margins: 10
      model: treeModel
      delegate: TreeViewDelegate{}

      Connections 
      {
         target: treeModel
         onDataChanged: 
         {
            control.expandRecursively(); 
         }
      }
   }
}