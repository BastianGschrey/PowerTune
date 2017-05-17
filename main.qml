import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import com.powertune 1.0

ApplicationWindow {


    visible: true
    width: 800
    height: 480
    // visibility: "FullScreen"
    title: qsTr("PowerTune")
    color: "black"

    TabView {
        id: tabView
        anchors.fill: parent
        Tab {
            title: "Dashboard"
            Dashboard{}
        }
        Tab {
            title: "Advanced Info"
            Advanced{}
        }
        Tab {
            title: "test"
            BaseMap{}
        }
        Tab {
            title: "Leading Map"
            LeadingIgnitionMap{}
        }
        Tab {
            title: "Serial settings"
            SerialSettings{}
        }




    }


/*    menuBar: MenuBar {
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
    }*/
}
