import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import hardwareTreeModel



Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello Qt6 TreeView")

TreeView {
    id: control
    anchors.fill: parent
    anchors.margins: 10

    model: HardwareTreeModel {
         id: tree_model
         Component.onCompleted: {
         control.expandRecursively()
         }
    }

    delegate: TreeViewDelegate{}

    Timer {
        id: updateTimer
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            tree_model.resetItems()
            control.expandRecursively()
        }
    }
}
}