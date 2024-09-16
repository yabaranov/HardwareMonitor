import QtQuick
import QtQuick.Controls.Basic

ScrollBar {
    id: control
    size: 0.3
    position: 0.2
    active: true

    contentItem: Rectangle {
        implicitWidth: 6
        implicitHeight: 6
        radius: width / 2
        color: control.pressed ? "black" : "grey"
        opacity: control.policy === ScrollBar.AlwaysOn || control.size < 1.0 ? 0.75 : 0

        Behavior on opacity {
            NumberAnimation {}
        }
    }   
}