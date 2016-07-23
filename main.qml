import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1


ApplicationWindow {
    visible: true
    width: 800
    height: 480
    // visibility: "FullScreen"
    title: qsTr("PowerTune")
    color: "black"

    Rectangle {
        id:dash
        color : "black"
        width: parent.width
        height: parent.height
        visible: true
        Dashboard{}
    }



 /*   Rectangle{
        id:rev
        color:"transparent"
        width: parent.width
        height: parent.height

        visible: true
        SpeedGauge{}

    }

 /*  Rectangle{
        id:speedo
        color:"transparent"
        width: parent.height / 1.5
        height: width
        y:parent.height / 5
        x: parent.width / 6.66
        visible: true
        SpeedGauge{}

    }*/

    Rectangle{
        id:lingmap
        width: Math.round(parent.width / 1.5)
        height: Math.round(parent.height / 1.5)
        anchors.left: parent.left;
        visible: false
        LeadingIgnitionMap{}
    }
    Rectangle{
        id: tingmap
        width: Math.round(parent.width / 1.5)
        height: Math.round(parent.height / 1.5)
        anchors.left: parent.left;
        visible: false
        LeadingIgnitionMap{}
    }


    Rectangle{
        id:gauge
        width: 200
        height: 250
        anchors.right: parent.right;
        anchors.top: parent.top;
        visible: false
        TempGauge{}
    }


    TreeView{
        id:tree
        width:200
        height: 200
        visible: false

    }

    toolBar:ToolBar {
        id: maintoolbar
        // anchors.fill: parent
        // transformOrigin: Body.left;
        //rotation :90;

        // x: - maintoolbar.width
        // y: -300


        RowLayout {
            ToolButton {
                text: "ECU"
                onClicked:{
                    if (tree.visible==true)
                        tree.visible=false
                    else
                        tree.visible=true
                }

            }
            ToolButton {
                text: "Basemap"
                onClicked:{
                    if (bmap.visible==true)
                        bmap.visible=false
                    else
                        bmap.visible=true
                        tingmap.visible=false
                        lingmap.visible=false
                }

            }


            ToolButton {
                text: "LeadingMap"

            onClicked:{
                if (lingmap.visible==true)
                    lingmap.visible=false
                else
                    lingmap.visible=true
                    tingmap.visible=false
                    bmap.visible=false
                }
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





