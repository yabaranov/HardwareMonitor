import QtQuick.Controls
import QtQuick.Controls.Universal

Menu {
    id: root
    title: qsTr("Options")

    Menu {
        title: qsTr("Theme")

        MenuItem {
            text: qsTr("Dark")
            onTriggered: AppSettings.theme = Universal.Dark
        }

        MenuItem {
            text: qsTr("Light")
            onTriggered: AppSettings.theme = Universal.Light
        }

        MenuItem {
            text: qsTr("System")
            onTriggered: AppSettings.theme = Universal.System
        }
    }

    Menu {
        title: qsTr("Language")

        MenuItem {
            text: qsTr("English")
            onTriggered: {
                AppSettings.languageCode = "en";
                languageChooser.setLanguage(AppSettings.languageCode);
                logger.info("New language is %1", [AppSettings.languageCode])
            }
        }

        MenuItem {
            text: qsTr("Russian")
            onTriggered: {
                AppSettings.languageCode = "ru";
                languageChooser.setLanguage(AppSettings.languageCode);
                logger.info("New language is %1", [AppSettings.languageCode])
            }
        }
    }
}
