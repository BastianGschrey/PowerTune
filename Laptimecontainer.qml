import QtQuick 2.8
import QtQuick.Controls 1.4

Rectangle {
    width: 400
    height: 400
    color: "black"

    Connections{
        target: Dashboard
        onCurrentLapChanged :{
            if (Dashboard.currentLap > 1)
            {
                laptimeModel.append({"lap":Dashboard.currentLap-1, "time":Dashboard.laptime})
                laptimelistview.incrementCurrentIndex()
            }
            if (Dashboard.currentLap == 0){
                laptimeModel.clear()
                laptimelistview.currentIndex = 0
            }
        }
    }
    ListModel {
        id: laptimeModel
    }

    Component {
        id: contactDelegate

        Item {
            id:leftcolum
            width: 400; height: 40
            Row {
            Column {
                Text {
                        text: "LAP " + lap
                        width: 110
                        color: "white"
                        font.pixelSize:  15
                        font.bold: true}
            }
            Column {
                Text { text: time
                       anchors.right: parent.right
                       width: 195
                       color: "white"
                       font.pixelSize:  30
                       font.bold: true}
            }
        }
        }
    }

    ListView {
        id: laptimelistview
        width: 400
        height: 200
        anchors.bottom: parent.bottom
        model: laptimeModel
        delegate: contactDelegate
        highlight: Rectangle { color: "#505050"; radius: 5}
        focus: true
    }

}
