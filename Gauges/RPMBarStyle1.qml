import QtQuick 2.8
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.1
import QtQuick.Extras 1.4


Item {
  anchors.fill:parent
  property  var unit : Dashboard.speedunits;
  Component.onCompleted: {units.unitadjust();}

Rectangle{
id: gaugebackround
height: parent.height /2.2
width: parent.width
color: "darkgrey"

}
  Gauge {
      id: gauge
      height: parent.height
      width: parent.width /1.024
      y:0
      minorTickmarkCount: 0
      tickmarkStepSize : Dashboard.maxRPM
      orientation : Qt.Horizontal
      minimumValue: 0
      maximumValue: Dashboard.maxRPM

      value: Dashboard.rpm
      Behavior on value {
          NumberAnimation {
              duration: 5
          }
      }
      style: GaugeStyle {
          tickmarkLabel: Text {
          font.pixelSize: 14
          color: "transparent"
          }
          tickmark: Item {
              implicitWidth: 18
              implicitHeight: 1

              Rectangle {
                  color: "transparent"
                  anchors.fill: parent
                  anchors.leftMargin: 3
                  anchors.rightMargin: 3
              }
          }
          valueBar: Rectangle {
              width:  210
              color: Qt.rgba(gauge.value / gauge.maximumValue, 1.1 - gauge.value / gauge.maximumValue, 0, 1)
          }
      }
}

Image
    {
      source:"qrc:/graphics/Racedash.png"
      anchors.fill: parent
      smooth: true

 }
Text {
    text:"RPM"
    font.pixelSize: 20
    y: 150
    x: 180
    font.bold: true
    font.family: "Eurostile"
    color: "grey"

}
Text {
    text: (Dashboard.rpm)
    font.pixelSize: 100
    y: 110
    x: 220
font.italic: true
    font.bold: true
    font.family: "Eurostile"
    color: "white"

}
Text {
    id :speed
    text: "km/h"
    font.pixelSize: 20
    y: 150
    x: 510
    font.bold: true
    font.family: "Eurostile"
    color: "grey"

}
Text {
    text: (Dashboard.speed).toFixed(0);
    font.pixelSize: 100
    y: 110
    x: 570
font.italic: true
    font.bold: true
    font.family: "Eurostile"
    color: "white"

}
        ShiftLights{}

Item {
    id: units
    function unitadjust()
    {
        if (unit == "imperial") {speed.text = "mph"};
        if (unit == "metric") {speed.text = "km/h"};
    }
}
}
