import QtQuick 2.0

Rectangle {
    id: dangertomanifold
    width: parent.width
    height:parent.height
    color:"transparent"

    Rectangle {
        id: warningsquare
        anchors.centerIn: parent
        width: parent.width /1.5
        height:parent.height /1.5
        color:"red"

        /*
        Item {
            Timer {
                interval: 500; running: true; repeat: true
                onTriggered: { console.log(warningsquare.color);
                if (warningsquare.color == "#ff0000") {warningsquare.color = "orange"};
                if (warningsquare.color == "#ffa500"){warningsquare.color = "red"};
                }

            }

        }*/

        Text {
            id: warning
            text: "Warning!!!"
            font.pixelSize: 60
            anchors.top : parent.top
            anchors.topMargin: parent.height / 5
            anchors.horizontalCenter: warningsquare.horizontalCenter
            font.bold: true
            font.family: "Eurostile"
            color: "black"

        }

        Text {
            text: "Danger to Manifold"
            font.pixelSize: 40
            anchors.top : warning.bottom
            anchors.topMargin: parent.height / 5
            anchors.horizontalCenter: warningsquare.horizontalCenter
            font.bold: true
            font.family: "Eurostile"
            color: "black"

        }
    }
}
