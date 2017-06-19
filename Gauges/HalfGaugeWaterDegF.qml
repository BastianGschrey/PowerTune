import QtQuick 2.4
import QtGraphicalEffects 1.0
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import Qt.labs.settings 1.0



Rectangle {
    id:coolantImperialGauge
    width: 200
    height: width
    color: "transparent"

CircularGauge {
        height: parent.height
        width: parent.width
        value: Math.round(Dashboard.Watertemp * 1.8 +32)
        anchors.verticalCenter: parent.verticalCenter
        anchors.top: parent.top
        style: HalfGaugeStyle {}
    }



    Text {
        text: "°F"
        font.pixelSize: (parent.width / 12)
         y: (parent.width / 5)
        font.bold: true
        font.family: "Eurostile"
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Text {
        text: "COOLANT TEMP"
        font.pixelSize: (parent.width / 14)
         y: (parent.width / 2.4)
        font.bold: true
        font.family: "Eurostile"
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Text {
        id: coolant
        text: Math.round(Dashboard.Watertemp * 1.8 +32)
        font.pixelSize: (parent.width / 10)
        font.bold: true
        font.family: "Eurostile"
        y: (parent.width / 3.5)
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
    }

    DropShadow {
            anchors.fill: coolant
            horizontalOffset: 0
            verticalOffset: 8
            radius: 4.0
            samples: 16
            color: "black"
            source: coolant
        }
    HalfNeedle {
        id: waterneedle
        anchors.verticalCenterOffset: 0
        anchors.centerIn: parent
        value: (Dashboard.Watertemp * 1.8 + 32) / 5.13


    }

}
