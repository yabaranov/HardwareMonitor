import QtQuick
import QtQuick.Controls.Universal

ListView {
    id: root

    property var hardwareList
    property int selectedHardwareIndex

    onVisibleChanged: selectedHardwareIndex = 0

    highlight: Rectangle { color: Universal.accent; radius: 5 }
    highlightResizeDuration: 0
    model: hardwareList

    delegate: Item {
        width: parent.width
        height: 50

        CustomLabel {
            text: model.name
            width: parent.width
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.currentIndex = model.index;
                root.selectedHardwareIndex = model.index
                logger.info("Current hardware is %1", [model.name])
            }
        }
    }
}
