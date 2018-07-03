import QtQuick 2.5
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
Rectangle {
  visible: true
  color:"transparent"
  anchors.fill:parent



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
            width: (735*(Dashboard.rpm)/Dashboard.maxRPM)+47 //+61 is the pixel where the RPM bar starts and from there is 651 pixels wide

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
