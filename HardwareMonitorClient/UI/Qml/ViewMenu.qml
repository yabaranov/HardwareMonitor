import QtQuick
import QtQuick.Controls

Menu {
    id: root
    title: qsTr("View")

    MenuItem {
        text: qsTr("Reset Min/Max")
        onTriggered:
        {
            AppSettings.resetMinAndMax();
            logger.info("Reset min and max")
        }
    }

    Menu {
        title: qsTr("Columns")

        Repeater {
            model: [
                { index: 0, text: qsTr("Value") },
                { index: 1, text: qsTr("Min") },
                { index: 2, text: qsTr("Max") }
            ]

            CheckBox {
                checked: AppSettings.columnVisibility[modelData.index]
                text: modelData.text
                onCheckedChanged: {
                    AppSettings.setColumnVisibility(modelData.index, checked);
                }
            }
        }
    }

    MenuItem {
        CheckBox {
            checked: AppSettings.logSensors
            text: qsTr("Log sensors")
            onCheckedChanged: {
                AppSettings.setLogSensors(checked);
            }
        }
    }
}
