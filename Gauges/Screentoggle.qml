import QtQuick 2.8
import QtQuick.Controls 2.1

Item {
    id: toggleswitch
    anchors.fill: parent

    property bool on: false

    function toggle() {
        if (toggleswitch.state == "on")
        {toggleswitch.state = "off",Connect.setSreenbrightness(50);}
        else
        {
            toggleswitch.state = "on";
            Connect.setSreenbrightness(0);}
    }


    MouseArea {
        anchors.fill: parent
        onClicked: toggle()
    }

    states: [
        State {
            name: "on"
            PropertyChanges { target: toggleswitch; on: true }
        },
        State {
            name: "off"
            PropertyChanges { target: toggleswitch; on: false }
        }
    ]

    Text {
        text: qsTr("Press to switch off screen")
        font.pixelSize: 20
        anchors.centerIn: parent
        font.bold: true
        font.family: "Eurostile"
        color: "white"
    }
}
