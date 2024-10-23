import QtQuick
import QtQuick.Controls

Label {
    id: errorText
    visible: false
    font.pointSize: 14

    onVisibleChanged: {
        if (errorText.visible) {
            fadeOutTimer.restart()
        } else {
            fadeOutTimer.stop()
        }
    }

    Timer {
        id: fadeOutTimer
        onTriggered: {
            errorText.visible = false
        }
    }
}
