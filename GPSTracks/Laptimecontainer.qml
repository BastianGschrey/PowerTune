import QtQuick 2.8
import QtQuick.Controls 1.4

Rectangle {
    width: 400
    height: 350
    color: "black"
    Connections{
        target: Dashboard
        onCurrentLapChanged :{
            if (Dashboard.currentLap > 1)
            {
                laptimeModel.append({"lap":Dashboard.currentLap-1, "time":Dashboard.laptime})
                //tableview.selection.select(Dashboard.currentLap-2)
            }
            if (Dashboard.currentLap == 0){laptimeModel.clear()};
        }
    }
    ListModel {
        id: laptimeModel
    }
    ScrollView {
        id:scrollcontainer
        width: 400
        height: 350


        TableView {
            id:tableview
            width: 380
            height: 400

            TableViewColumn {
                role: "lap"
                title: "Lap"
                width: scrollcontainer.width /3
                delegate: imageDelegate
            }

            TableViewColumn {
                role: "time"
                title: "Time"
                width: scrollcontainer.width /1.65
                delegate: imageDelegate
            }
            itemDelegate: Item {
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    color: "black"
                    elide: styleData.elideMode
                    text: styleData.value
                    font.pixelSize: 20
                    font.bold: true
                }
            }
            model: laptimeModel
        }
    }
}
