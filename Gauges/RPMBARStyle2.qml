import QtQuick 2.5
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
Rectangle {
  visible: true
  color:"transparent"
  anchors.fill:parent
  property  var unit : Dashboard.speedunits;
  Component.onCompleted: {units.unitadjust()}

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
      source:"qrc:/graphics/RPM_BG.png"
      anchors.top:parent.top
      anchors.left:parent.left
      smooth: true

      Item{
            id: displayWindow1
            height: parent.height
            width: (678*(Dashboard.rpm)/Dashboard.maxRPM)+70 //+70 is the pixel where the RPM bar starts and from there is 678 pixels wide

            clip: true

              anchors.bottom: parent.bottom
              anchors.left: parent.left
              anchors.rightMargin:{switch(true)
             {
                case Dashboard.rpm>=0 && Dashboard.rpm < 500:return 10;
                case Dashboard.rpm>=500 && Dashboard.rpm < 700:return 9.7;
                case Dashboard.rpm>=700 && Dashboard.rpm < 900:return 8.4;
                case Dashboard.rpm>=900 && Dashboard.rpm < 1000:return 8;
                case Dashboard.rpm>=1100 && Dashboard.rpm <= 1200:return 7.15;
                case Dashboard.rpm>=1200 && Dashboard.rpm <= 1300:return 6;

                }
              }

            Image
            {
              id:speedarcfill
              anchors.top:parent.top
              anchors.left:parent.left
              source:"qrc:/graphics/RPM_Fill.png"
              smooth: true
              z: 1
            }
          }

    PathInterpolator {
      id: motionPath
      property int value

         path: Path {
         startX: 47; startY: 186
         PathLine { x: 137; y: 123 }
         PathArc { x: 251; y: 88; radiusX: 90; radiusY: 90 }
         PathLine { x: 776; y: 76 }
       }
      progress: Dashboard.rpm / Dashboard.maxRPM
    }
    }
            ShiftLights{}
}
