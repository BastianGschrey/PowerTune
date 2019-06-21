import QtQuick 2.5
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
Rectangle {
  visible: true
  color:"transparent"
  anchors.fill:parent
  property  var unit : Dashboard.units;
  Component.onCompleted: {units.unitadjust();}

  Text {
      text:"RPM"
      font.pixelSize: 20
      y: 160
      x: 180
      font.bold: true
      font.family: "Eurostile"
      color: "grey"

  }
  Text {
      text: (Dashboard.rpm)
      font.pixelSize: 100
      y: 130
      x: 217
  font.italic: true
      font.bold: true
      font.family: "Eurostile"
      color: "white"

  }
  Text {
      id :speed
      text: "km/h"
      font.pixelSize: 20
      y: 160
      x: 510
      font.bold: true
      font.family: "Eurostile"
      color: "grey"

  }
  Text {
      text: (Dashboard.speed).toFixed(0)
      font.pixelSize: 100
      y: 130
      x: 570
  font.italic: true
      font.bold: true
      font.family: "Eurostile"
      color: "white"

  }

  Item {
      id: units
      function unitadjust()
      {
          if (unit == "imperial") {speed.text = "mph"};
          if (unit == "metric") {speed.text = "km/h"};
      }
  }


    Image
    {
      id:groove1
      source:"qrc:/graphics/empty.png"
      anchors.top:parent.top
      anchors.left:parent.left
      smooth: true

      Item{
            id: displayWindow1
            height: parent.height
            width: (651*(Dashboard.rpm)/Dashboard.maxRPM)+61 //+61 is the pixel where the RPM bar starts and from there is 651 pixels wide

            clip: true

              anchors.bottom: parent.bottom
              anchors.left: parent.left
             /* anchors.rightMargin:{switch(true)
             {
                case slider.value>=0 && slider.value < 111:return 10;
                case slider.value>=111 && slider.value < 124:return 9.7;
                case slider.value>=124 && slider.value < 132:return 8.4;
                case slider.value>=132 && slider.value < 135:return 8;
                case slider.value>=135 && slider.value <= 165:return 7.15;
                case slider.value>=165 && slider.value <= 240:return 6;

                }
              }*/

            Image
            {
              id:speedarcfill
              anchors.top:parent.top
              anchors.left:parent.left
              source:"qrc:/graphics/fill.png"
              smooth: true
              z: 1
            }
          }

    PathInterpolator {
      id: motionPath
      property int value

     /* path: Path {
        startX: 27; startY: 189
        PathLine { x: 98; y: 54 }
        PathArc { x: 176; y: 11; radiusX: 90; radiusY: 90 }
        PathLine { x: 245; y: 11 }
      }*/
         path: Path {
         startX: 61; startY: 189
         PathLine { x: 712; y: 480 }
         //PathArc { x: 176; y: 11; radiusX: 90; radiusY: 90 }
         //PathLine { x: 800; y: 11 }
       }
      progress: Dashboard.rpm / Dashboard.maxRPM //slider.value/8000 // replace this with Dashboard.rpm
    }
    }
            ShiftLights{}
// remove slider
/*
    Slider {
          id: slider
          anchors.bottom: parent.bottom
          width: parent.width-10
          height: 100

          style: SliderStyle {
            handle:
              Rectangle {
                    anchors.centerIn: parent
                    color: control.pressed ? "white" : "lightgray"
                    border.color: "gray"
                    implicitWidth: 10
                    implicitHeight: 40
                  }

            groove: Rectangle {
              width: slider.width
              height: 10
              color:"black"

              LinearGradient {
                anchors.verticalCenter: parent.verticalCenter
                start: Qt.point(0, 0)
                end: Qt.point(parent.width, 0)
                width: styleData.handlePosition
                height: 10

                gradient: Gradient {
                  GradientStop {position: 0.0; color: "#008BFF" }
                  GradientStop {position: 0.5; color: "#3FFFD0" }
                  GradientStop { position: 1.0; color: "#3FFF41" }
                }
              }
            }

          }

          maximumValue: 8000

        }*/
//Remove till here

}
