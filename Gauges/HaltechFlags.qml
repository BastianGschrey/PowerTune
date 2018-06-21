import QtQuick 2.8
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1




Rectangle {
    id: sensorwindow
    width: parent.width
    height:parent.height
    color:"transparent"

    // Sensor Status ON/OFF
    Row {
        anchors.centerIn: parent
        spacing: 20
        Grid {
            rows: 8
            columns: 6
            spacing: 5

            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("NOS SW")
            }

            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag1 == "1") ? true: false; }
            }

            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("NOS")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag2 == "1") ? true: false; }
            }

            // ROW 2



            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("Gear SW")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag3 == "1") ? true: false; }

            }

            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("DecelCut")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag4 == "1") ? true: false; }
            }
            // ROW 3



            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("Tr.Thro")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag5 == "1") ? true: false; }
            }

            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("Brake")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag6 == "1") ? true: false; }

            }

            // ROW 4


            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("Clutch")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag7 == "1") ? true: false; }
            }

            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("Reserved")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag8 == "1") ? true: false; }
            }

            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("ALag Launch")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag9 == "1") ? true: false; }
            }


            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("Antilag SW")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag10 == "1") ? true: false; }
            }

            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("RevLim SW")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag11 == "1") ? true: false; }
            }


            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("R A.Lag SW")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag12 == "1") ? true: false; }
            }

            // ROW 7



            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("Flat Shift")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag13 == "1") ? true: false; }
            }

            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("Timed Duty")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag14 == "1") ? true: false; }
            }

            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("Torque Red")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag15 == "1") ? true: false; }
            }

            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("Torque Red Cut")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag16 == "1") ? true: false; }

            }
//
            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("MIL")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag17 == "1") ? true: false; }

            }
            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("Batt. Light")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag18 == "1") ? true: false; }

            }
            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("Limp Mode")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag19 == "1") ? true: false; }

            }
            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("L.Indicator")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag20 == "1") ? true: false; }

            }
            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("R.Indicator")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag21 == "1") ? true: false; }

            }
            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("High Beam")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag22 == "1") ? true: false; }

            }
            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("Hand Brake")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag23 == "1") ? true: false; }

            }
            Text {
                font.pixelSize: sensorwindow.width /32
                color:"white"
                text: qsTr("Reserved")
            }
            StatusIndicator {
                height: sensorwindow.width /32
                width: height
                color: "green"
                active: { (Dashboard.Flag24 == "1") ? true: false; }

            }


        }
    }
}
