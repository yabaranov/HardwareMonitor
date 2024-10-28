import QtQuick.Controls

Menu {
    id: root
    title: "View"

    MenuItem {
        text: "Reset Min/Max"
        onTriggered:
        {
            modelManager.resetMinAndMax();
        }
    }

    Menu {
        title: "Columns"

        CheckBox {
            checked: AppSettings.columnVisibility[0]
            text: qsTr("Value")
            onCheckedChanged: AppSettings.setColumnVisibility(0, checked)
        }

        CheckBox {
            checked: AppSettings.columnVisibility[1]
            text: qsTr("Min")
            onCheckedChanged: AppSettings.setColumnVisibility(1, checked)
        }

        CheckBox {
            checked: AppSettings.columnVisibility[2]
            text: qsTr("Max")
            onCheckedChanged: AppSettings.setColumnVisibility(2, checked)
        }
    }
}
