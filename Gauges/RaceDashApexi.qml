import QtQuick 2.8
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import "../Gauges"
import ".."


Item {

    width: parent.width
    height:parent.height
    property  var unit : Dashboard.units;

    Component.onCompleted: {units.unitadjust()} // adjusts the Gauges to metric or imperial



    Rectangle {
        id:racedashwindow
        width: parent.width
        height:parent.height
        color:"black"

        RPMbar{}
        ShiftLights{}
/*
        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            spacing: 20
            StatusIndicator {
                color: "green"
                active: { (Dashboard.rpm > "3000") ? true: false; }
            }
            StatusIndicator {
                color: "green"
                active: { (Dashboard.rpm > "4000") ? true: false; }
            }
            StatusIndicator {
                color: "yellow"
                active: { (Dashboard.rpm > "5000") ? true: false; }
            }
            StatusIndicator {
                color: "yellow"
                active: { (Dashboard.rpm > "6000") ? true: false; }
            }
            StatusIndicator {
                color: "red"
                active: { (Dashboard.rpm > "7900") ? true: false; }
            }
            StatusIndicator {
                color: "red"
                active: { (Dashboard.rpm > "7900") ? true: false; }
            }
            StatusIndicator {
                color: "yellow"
                active: { (Dashboard.rpm > "6000") ? true: false; }
            }
            StatusIndicator {
                color: "yellow"
                active: { (Dashboard.rpm > "5000") ? true: false; }
            }
            StatusIndicator {
                color: "green"
                active: { (Dashboard.rpm > "4000") ? true: false; }
            }
            StatusIndicator {
                color: "green"
                active: { (Dashboard.rpm > "3000") ? true: false; }
            }
        }
*/

        Text {
            text:"RPM"
            font.pixelSize: 20
            y: 220
            x: 180
            font.bold: true
            font.family: "Eurostile"
            color: "grey"

        }
        Text {
            text: (Dashboard.rpm)
            font.pixelSize: 100
            y: 140
            x: 240
        font.italic: true
            font.bold: true
            font.family: "Eurostile"
            color: "white"

        }
        Text {
            id :speed
            font.pixelSize: 20
            y: 170
            x: 550
            font.bold: true
            font.family: "Eurostile"
            color: "grey"

        }
        Text {
            text: (Dashboard.speed)
            font.pixelSize: 50
            y: 145
            x: 620
        font.italic: true
            font.bold: true
            font.family: "Eurostile"
            color: "white"

        }
    Text {
            id:boost
            //text:"Boost [mmHg/bar]"
            font.pixelSize: 20
            y: 280
            x: 310
            font.bold: true
            font.family: "Eurostile"
            color: "grey"

        }
        Text {
            text: (Dashboard.pim).toFixed(1)
            font.pixelSize: 50
            y: 305
            x: 310
        font.italic: true
            font.bold: true
            font.family: "Eurostile"
            color: "white"

        }
        Text {
            text:"Knock"
            font.pixelSize: 18
            y: 370
            x: 310
            font.bold: true
            font.family: "Eurostile"
            color: "grey"

        }
        Text {
            text: (Dashboard.Knock).toFixed(0)
            font.pixelSize: 50
            y: 395
            x: 310
        font.italic: true
            font.bold: true
            font.family: "Eurostile"
            color: "white"

        }
        Text {
            id:air
            font.pixelSize: 18
            y: 370
            x: 550
            font.bold: true
            font.family: "Eurostile"
            color: "grey"

        }
        Text {
            text: (Dashboard.Intaketemp).toFixed(1)
            font.pixelSize: 50
            y: 395
            x: 550
        font.italic: true
            font.bold: true
            font.family: "Eurostile"
            color: "white"

        }
        Text {
            id: water
            font.pixelSize: 18
            y: 280
            x: 550
            font.bold: true
            font.family: "Eurostile"
            color: "grey"

        }
        Text {
            text: (Dashboard.Watertemp).toFixed(1)
            font.pixelSize: 50
            y: 305
            x: 550
        font.italic: true
            font.bold: true
            font.family: "Eurostile"
            color: "white"

        }
        Text {
            text:"AFR"
            font.pixelSize: 18
            y: 230
            x: 550
            font.bold: true
            font.family: "Eurostile"
            color: "grey"

        }
        Text {
            text: (Dashboard.auxcalc1).toFixed(1)
            font.pixelSize: 50
            y: 205
            x: 620
        font.italic: true
            font.bold: true
            font.family: "Eurostile"
            color: "white"

        }

    // Sensor Status ON/OFF

        Grid {
        anchors.left: parent.left
        anchors.leftMargin: 50
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
            rows: 8
            columns: 6
            spacing: 3

            //ROW 1
            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.SensorString1)

            }
            Text {
                font.pixelSize: 15
                color:{ (Dashboard.sens1 > "5") ? "red": "yellow"; }
                text: (Dashboard.sens1).toFixed(2) + " V   "
            }

            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.FlagString1)
            }

            StatusIndicator {
                height: 15
                width: height
                color: "green"
                active: { (Dashboard.Flag1 == "1") ? true: false; }
            }

            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.FlagString2)
            }
            StatusIndicator {
                height: 15
                width: height
                color: "green"
                active: { (Dashboard.Flag2 == "1") ? true: false; }
            }

            // ROW 2

            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.SensorString2)
            }
            Text {
                font.pixelSize: 15
                color:{ (Dashboard.sens2 > "5") ? "red": "yellow"; }
                text: (Dashboard.sens2).toFixed(2) + " V   "
            }

            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.FlagString3)
            }
            StatusIndicator {
                height: 15
                width: height
                color: "green"
                active: { (Dashboard.Flag3 == "1") ? true: false; }

            }

            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.FlagString4)
            }
            StatusIndicator {
                height: 15
                width: height
                color: "green"
                active: { (Dashboard.Flag4 == "1") ? true: false; }
            }
            // ROW 3

            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.SensorString3)
            }
            Text {
                font.pixelSize: 15
                color:{ (Dashboard.sens3 > "5") ? "red": "yellow"; }
                text: (Dashboard.sens3).toFixed(2) + " V   "
            }
            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.FlagString5)
            }
            StatusIndicator {
                height: 15
                width: height
                color: "green"
                active: { (Dashboard.Flag5 == "1") ? true: false; }
            }

            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.FlagString6)
            }
            StatusIndicator {
                height: 15
                width: height
                color: "green"
                active: { (Dashboard.Flag6 == "1") ? true: false; }

            }

            // ROW 4

            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.SensorString4)
            }
            Text {
                font.pixelSize: 15
                color:{ (Dashboard.sens4 > "5") ? "red": "yellow"; }
                text: (Dashboard.sens4).toFixed(2) + " V   "
            }

            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.FlagString7)
            }
            StatusIndicator {
                height: 15
                width: height
                color: "green"
                active: { (Dashboard.Flag7 == "1") ? true: false; }
            }

            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.FlagString8)
            }
            StatusIndicator {
                height: 15
                width: height
                color: "green"
                active: { (Dashboard.Flag8 == "1") ? true: false; }
            }
            // ROW 5

            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.SensorString5)
            }
            Text {
                font.pixelSize: 15
                color:{ (Dashboard.sens5 > "5") ? "red": "yellow"; }
                text: (Dashboard.sens5).toFixed(2) + " V   "
            }

            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.FlagString9)
            }
            StatusIndicator {
                height: 15
                width: height
                color: "green"
                active: { (Dashboard.Flag9 == "1") ? true: false; }
            }


            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.FlagString10)
            }
            StatusIndicator {
                height: 15
                width: height
                color: "green"
                active: { (Dashboard.Flag10 == "1") ? true: false; }
            }

            // ROW 6


            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.SensorString6)
            }
            Text {
                font.pixelSize: 15
                color:{ (Dashboard.sens6 > "5") ? "red": "yellow"; }
                text: (Dashboard.sens6).toFixed(2) + " V   "
            }

            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.FlagString11)
            }
            StatusIndicator {
                height: 15
                width: height
                color: "green"
                active: { (Dashboard.Flag11 == "1") ? true: false; }
            }


            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.FlagString12)
            }
            StatusIndicator {
                height: 15
                width: height
                color: "green"
                active: { (Dashboard.Flag12 == "1") ? true: false; }
            }

            // ROW 7


            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.SensorString7)
            }
            Text {
                font.pixelSize: 15
                color:{ (Dashboard.sens7 > "5") ? "red": "yellow"; }
                text: (Dashboard.sens7).toFixed(2) + " V   "
            }

            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.FlagString13)
            }
            StatusIndicator {
                height: 15
                width: height
                color: "green"
                active: { (Dashboard.Flag13 == "1") ? true: false; }
            }



            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.FlagString14)
            }
            StatusIndicator {
                height: 15
                width: height
                color: "green"
                active: { (Dashboard.Flag14 == "1") ? true: false; }
            }


            // ROW 8

            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.SensorString8)
            }
            Text {
                font.pixelSize: 15
                color:{ (Dashboard.sens8 > "5") ? "red": "yellow"; }
                text: (Dashboard.sens8).toFixed(2) + " V   "
            }


            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.FlagString15)
            }
            StatusIndicator {
                height: 15
                width: height
                color: "green"
                active: { (Dashboard.Flag15 == "1") ? true: false; }
            }



            Text {
                font.pixelSize: 15
                color:"white"
                text: qsTr(Dashboard.FlagString16)
            }
            StatusIndicator {
                height: 15
                width: height
                color: "green"
                active: { (Dashboard.Flag16 == "1") ? true: false; }

            }


        }
    }
    Item {
        id: units
        function unitadjust()
        {
            if (unit == "imperial") {boost.text = "Boost [inHg/PSI]",speed.text= "MP/H",air.text = "Air Temp [°F]",water.text = "Water Temp [°F]"};
            if (unit == "metric") {boost.text ="Boost [mmHg/kgcm2]",speed.text= "Km/H",air.text = "Air Temp [°C]",water.text = "Water Temp [°C]"};

        }


    }
    Connections{
        target: Dashboard
        onRpmChanged:{if (Dashboard.rpm > Dashboard.rpmwarn) {warning.visible = true} else warning.visible = false }
    }
    Rectangle{
    id: warning
    anchors.fill: racedashwindow
    color: "transparent"
    visible: false
    WarningDangertoManifold{}
    }
}
