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

        RPMBarStyle1{}
        //RPMbar{}
        ShiftLights{}


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
        Rectangle{
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        height: parent.height /2.2
        width: parent.width /2.7
        color: "transparent"
        PFCSensors{sizeoftext : racedashwindow.width /54 }
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
    Rectangle{
    anchors.fill: parent
    color: "transparent"
    WarningLoader{}
    }

}
