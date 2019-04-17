import QtQuick 2.8
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1




Rectangle {
    id: sensorwindow
    anchors.fill: parent
    color:"transparent"
    property int sizeoftext : sensorwindow.width /32

    // Sensor Status ON/OFF
    Row {
        anchors.centerIn: parent
        spacing: 20
        Grid {
            rows: 8
            columns: 6
            spacing: parent.width /160

            //ROW 1
            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.SensorString1)

            }
            Text {
                font.pixelSize: sizeoftext
                color:{ (Dashboard.sens1 > "5") ? "red": "green"; }
                text: (Dashboard.sens1).toFixed(2) + " V   "
            }

            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.FlagString1)
            }

            StatusIndicator {
                height: sizeoftext
                width: height
                color: "green"
                active: { (Dashboard.Flag1 == "1") ? true: false; }
            }

            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.FlagString2)
            }
            StatusIndicator {
                height: sizeoftext
                width: height
                color: "green"
                active: { (Dashboard.Flag2 == "1") ? true: false; }
            }

            // ROW 2

            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.SensorString2)
            }
            Text {
                font.pixelSize: sizeoftext
                color:{ (Dashboard.sens2 > "5") ? "red": "green"; }
                text: (Dashboard.sens2).toFixed(2) + " V   "
            }

            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.FlagString3)
            }
            StatusIndicator {
                height: sizeoftext
                width: height
                color: "green"
                active: { (Dashboard.Flag3 == "1") ? true: false; }

            }

            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.FlagString4)
            }
            StatusIndicator {
                height: sizeoftext
                width: height
                color: "green"
                active: { (Dashboard.Flag4 == "1") ? true: false; }
            }
            // ROW 3

            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.SensorString3)
            }
            Text {
                font.pixelSize: sizeoftext
                color:{ (Dashboard.sens3 > "5") ? "red": "green"; }
                text: (Dashboard.sens3).toFixed(2) + " V   "
            }
            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.FlagString5)
            }
            StatusIndicator {
                height: sizeoftext
                width: height
                color: "green"
                active: { (Dashboard.Flag5 == "1") ? true: false; }
            }

            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.FlagString6)
            }
            StatusIndicator {
                height: sizeoftext
                width: height
                color: "green"
                active: { (Dashboard.Flag6 == "1") ? true: false; }

            }

            // ROW 4

            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.SensorString4)
            }
            Text {
                font.pixelSize: sizeoftext
                color:{ (Dashboard.sens4 > "5") ? "red": "green"; }
                text: (Dashboard.sens4).toFixed(2) + " V   "
            }

            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.FlagString7)
            }
            StatusIndicator {
                height: sizeoftext
                width: height
                color: "green"
                active: { (Dashboard.Flag7 == "1") ? true: false; }
            }

            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.FlagString8)
            }
            StatusIndicator {
                height: sizeoftext
                width: height
                color: "green"
                active: { (Dashboard.Flag8 == "1") ? true: false; }
            }
            // ROW 5

            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.SensorString5)
            }
            Text {
                font.pixelSize: sizeoftext
                color:{ (Dashboard.sens5 > "5") ? "red": "green"; }
                text: (Dashboard.sens5).toFixed(2) + " V   "
            }

            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.FlagString9)
            }
            StatusIndicator {
                height: sizeoftext
                width: height
                color: "green"
                active: { (Dashboard.Flag9 == "1") ? true: false; }
            }


            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.FlagString10)
            }
            StatusIndicator {
                height: sizeoftext
                width: height
                color: "green"
                active: { (Dashboard.Flag10 == "1") ? true: false; }
            }

            // ROW 6


            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.SensorString6)
            }
            Text {
                font.pixelSize: sizeoftext
                color:{ (Dashboard.sens6 > "5") ? "red": "green"; }
                text: (Dashboard.sens6).toFixed(2) + " V   "
            }

            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.FlagString11)
            }
            StatusIndicator {
                height: sizeoftext
                width: height
                color: "green"
                active: { (Dashboard.Flag11 == "1") ? true: false; }
            }


            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.FlagString12)
            }
            StatusIndicator {
                height: sizeoftext
                width: height
                color: "green"
                active: { (Dashboard.Flag12 == "1") ? true: false; }
            }

            // ROW 7


            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.SensorString7)
            }
            Text {
                font.pixelSize: sizeoftext
                color:{ (Dashboard.sens7 > "5") ? "red": "green"; }
                text: (Dashboard.sens7).toFixed(2) + " V   "
            }

            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.FlagString13)
            }
            StatusIndicator {
                height: sizeoftext
                width: height
                color: "green"
                active: { (Dashboard.Flag13 == "1") ? true: false; }
            }



            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.FlagString14)
            }
            StatusIndicator {
                height: sizeoftext
                width: height
                color: "green"
                active: { (Dashboard.Flag14 == "1") ? true: false; }
            }


            // ROW 8

            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.SensorString8)
            }
            Text {
                font.pixelSize: sizeoftext
                color:{ (Dashboard.sens8 > "5") ? "red": "green"; }
                text: (Dashboard.sens8).toFixed(2) + " V   "
            }


            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.FlagString15)
            }
            StatusIndicator {
                height: sizeoftext
                width: height
                color: "green"
                active: { (Dashboard.Flag15 == "1") ? true: false; }
            }



            Text {
                font.pixelSize: sizeoftext
                color:"white"
                text: qsTr(Dashboard.FlagString16)
            }
            StatusIndicator {
                height: sizeoftext
                width: height
                color: "green"
                active: { (Dashboard.Flag16 == "1") ? true: false; }

            }


        }
    }
}
