import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1


ApplicationWindow {
    visible: true
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableWidth
    title: qsTr("PowerTune")
    color: "black"


    Rectangle{
        id:bmap
        movable: true
        width: Math.round(parent.width / 1.5)
        height: Math.round(parent.height / 1.5)
        anchors.left: parent.left;
        BaseMap{}
    }
    Rectangle{
        id:gauge
        width: 200
        height: 250
        anchors.left: bmap.right;
        TempGauge{}
    }

    toolBar:ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: "Show Basemap"
                onClicked :{}
               // signal showBase(string Base)
            }
            ToolButton {
                text: "Enabled"
            }
            ToolButton {
                text: "Enabled"
            }
            Item { Layout.fillWidth: true }
            CheckBox {
                text: "Enabled"
                checked: true
                Layout.alignment: Qt.AlignRight
            }
        }

    }
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
        Menu {
            title: qsTr("Options")
            MenuItem {
                text: qsTr("COM Port")
                onTriggered: console.log("Select COM Port");
            }
            MenuItem {
                text: qsTr("Connect")
                onTriggered: console.log("Connecting to Power FC");

            }
            MenuItem {
                text: qsTr("Disconnect")
                onTriggered: console.log("Disconnect Power FC");
            }
        }
        Menu {
            title: qsTr("ECU Controls")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("ECU Controls");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
        Menu {
            title: qsTr("Logging")
            MenuItem {
                text: qsTr("Logging Setup")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Logging Start")

            }
            MenuItem {
                text: qsTr("Logging Stop")

            }
        }
    }
}




