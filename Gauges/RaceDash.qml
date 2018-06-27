import QtQuick 2.8
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import "../Gauges"


Item {

 anchors.fill: parent

    Rectangle {
        id:racedashwindow
        width: parent.width
        height:parent.height
        color:"black"


        RPMbar{}
        ShiftLights{}



        Text {
            text:" RPM : " + Dashboard.rpm
            font.pixelSize: 32
            y: 160
            x: 190
            font.bold: true
            font.family: "Eurostile"
            color: "white"

        }
        Text {
            text: " Speed : " +(Dashboard.speed).toFixed(0)
            font.pixelSize: 32
            y: 160
            x: 520
            font.bold: true
            font.family: "Eurostile"
            color: "white"

        }
        Text {
            text:" AFR "
            font.pixelSize: 32
            y: 330
            x: 40
            font.bold: true
            font.family: "Eurostile"
            color: "white"

        }
        Text {
            text: (Dashboard.auxcalc1).toFixed(1)
            font.pixelSize: 32
            y: 380
            x: 50
            font.bold: true
            font.family: "Eurostile"
            color: "white"

        }

        Text {
            text:" Boost "
            font.pixelSize: 32
            y: 330
            x: 170
            font.bold: true
            font.family: "Eurostile"
            color: "white"

        }
        Text {
            text: (Dashboard.pim).toFixed(2)
            font.pixelSize: 32
            y: 380
            x: 190
            font.bold: true
            font.family: "Eurostile"
            color: "white"

        }
        Text {
            text:" Air T. "
            font.pixelSize: 32
            y: 330
            x: 350
            font.bold: true
            font.family: "Eurostile"
            color: "white"

        }
        Text {
            text: (Dashboard.Intaketemp).toFixed(0)
            font.pixelSize: 32
            y: 380
            x: 370
            font.bold: true
            font.family: "Eurostile"
            color: "white"

        }
        Text {
            text:" Water T. "
            font.pixelSize: 32
            y: 330
            x: 500
            font.bold: true
            font.family: "Eurostile"
            color: "white"

        }
        Text {
            text: (Dashboard.Watertemp).toFixed(0)
            font.pixelSize: 32
            y: 380
            x: 560
            font.bold: true
            font.family: "Eurostile"
            color: "white"

        }
    }
}
