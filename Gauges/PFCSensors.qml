import QtQuick 2.6
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1

Rectangle {
    width: parent.width
    height:parent.height
    color:"transparent"
/*
    Row {
    spacing: 5
    Grid {
        rows: 8
        columns: 4
        spacing: 5

        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.SensorString1)

        }
        Text {
            font.pixelSize: (parent.width / 8)
            color:{ (Dashboard.Sens1 > "5") ? "green": "red"; }
            text: qsTr(Dashboard.Sens1)
        }

        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.SensorString2)
        }
        Text {
            font.pixelSize: (parent.width / 8)
            color:{ (Dashboard.Sens1 > "5") ? "green": "red"; }
            text: qsTr(Dashboard.Sens2)
        }
        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.SensorString3)
        }
        Text {
            font.pixelSize: (parent.width / 8)
            color:{ (Dashboard.Sens1 > "5") ? "green": "red"; }
            text: qsTr(Dashboard.Sens3)
        }
        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.SensorString4)
        }
        Text {
            font.pixelSize: (parent.width / 8
            color:{ (Dashboard.Sens1 > "5") ? "green": "red"; }
            text: qsTr(Dashboard.Sens4)
        }
        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.SensorString5)
        }
        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.Sens5)
        }
        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.SensorString6)
        }
        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.Sens6)
        }
        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.SensorString7)
        }
        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.Sens7)
        }
        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.SensorString8)
        }
        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.Sens8)
        }




    }
}
*/
// Sensor Status ON/OFF
Row {
    anchors.centerIn: parent
    spacing: 5
    Grid {
        rows: 8
        columns: 4
        spacing: 5


        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.FlagString1)
        }

        StatusIndicator {
            color: "green"
            active: { (Dashboard.Flag1 == "1") ? true: false; }
        }

        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.FlagString2)
        }
        StatusIndicator {
            color: "green"
            active: { (Dashboard.Flag2 == "1") ? true: false; }
        }


        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.FlagString3)
        }
        StatusIndicator {
            color: "green"
            active: { (Dashboard.Flag3 == "1") ? true: false; }

        }

        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.FlagString4)
        }
        StatusIndicator {
            color: "green"
            active: { (Dashboard.Flag4 == "1") ? true: false; }
        }


        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.FlagString5)
        }
        StatusIndicator {
            color: "green"
            active: { (Dashboard.Flag5 == "1") ? true: false; }
        }



        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.FlagString6)
        }
        StatusIndicator {
            color: "green"
            active: { (Dashboard.Flag6 == "1") ? true: false; }

        }


        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.FlagString7)
        }
        StatusIndicator {
            color: "green"
            active: { (Dashboard.Flag7 == "1") ? true: false; }
        }

        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.FlagString8)
        }
        StatusIndicator {
            color: "green"
            active: { (Dashboard.Flag8 == "1") ? true: false; }
        }


        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.FlagString9)
        }
        StatusIndicator {
            color: "green"
            active: { (Dashboard.Flag9 == "1") ? true: false; }
        }


        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.FlagString10)
        }
        StatusIndicator {
            color: "green"
            active: { (Dashboard.Flag10 == "1") ? true: false; }
        }


        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.FlagString11)
        }
        StatusIndicator {
            color: "green"
            active: { (Dashboard.Flag11 == "1") ? true: false; }
        }


        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.FlagString12)
        }
        StatusIndicator {
            color: "green"
            active: { (Dashboard.Flag1 == "12") ? true: false; }
        }


        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.FlagString13)
        }
        StatusIndicator {
            color: "green"
            active: { (Dashboard.Flag1 == "13") ? true: false; }
        }



        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.FlagString14)
        }
        StatusIndicator {
            color: "green"
            active: { (Dashboard.Flag14 == "1") ? true: false; }
        }



        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.FlagString15)
        }
        StatusIndicator {
            color: "green"
            active: { (Dashboard.Flag15 == "1") ? true: false; }
        }



        Text {
            font.pixelSize: (parent.width / 8)
            color:"white"
            text: qsTr(Dashboard.FlagString16)
        }
        StatusIndicator {
            color: "green"
            active: { (Dashboard.Flag16 == "1") ? true: false; }

        }


    }
}
}
