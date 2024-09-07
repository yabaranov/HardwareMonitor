import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import hardwareTreeModel

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello Qt6 TreeView")

property var treeModel: controller.getTreeModel()

TreeView {
    id: control
    anchors.fill: parent
    anchors.margins: 10

    model: treeModel

    delegate: TreeViewDelegate{}

 Connections {
            target: treeModel
            onDataChanged: {
                control.expandRecursively(); 
            }
        }
}
}