import QtQuick.Controls
import QtQuick.Controls.Universal

Menu {
    id: root
    title: "Theme"

    MenuItem {
        text: "Dark"
        onTriggered: AppSettings.theme = Universal.Dark
    }

    MenuItem {
        text: "Light"
        onTriggered: AppSettings.theme = Universal.Light
    }

    MenuItem {
        text: "System"
        onTriggered: AppSettings.theme = Universal.System
    }
}
