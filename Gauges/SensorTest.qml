import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Extras 1.4

Item {
    id: sensorwindow
    width: parent.width
    height: parent.height
Rectangle {
    anchors.fill: parent
    color: "grey"

    PieMenu {
        id: pieMenu

        MenuItem {
            text: "Action 1"
            onTriggered: print("Action 1")
        }
        MenuItem {
            text: "Action 2"
            onTriggered: print("Action 2")
        }
        MenuItem {
            text: "Action 3"
            onTriggered: print("Action 3")
        }
    }

    Grid {
        rows: 9
        columns: 2
        spacing: 5
        anchors.left: parent.left

        Text { text: "Accel X: "
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"
        }
        Text { text: Dashboard.accelx
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"
        }
        Text { text: "Accel Y: "
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"}
        Text { text: Dashboard.accely
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"}
        Text { text: "Accel Z: "
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"}
        Text { text: Dashboard.accelz
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"}
        Text { text: "Ambien Temp: "
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"}
        Text { text: Dashboard.ambitemp
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"}
        Text { text: "Ambient Pressure: "
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"}
        Text { text: Dashboard.ambipress
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"}
        Text { text: "Azimuth: "
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"}
        Text { text: Dashboard.compass
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"}
        Text { text: "Gyro X: "
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"
        }
        Text { text: Dashboard.gyrox
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"
        }
        Text { text: "Gyro y: "
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"
        }
        Text { text: Dashboard.gyroy
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"
        }
        Text { text: "Gyro Z: "
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"
        }
        Text { text: Dashboard.gyroz
            font.pixelSize: sensorwindow.width /20
            font.bold: true
            font.family: "Eurostile"
        }

    }
}
}


