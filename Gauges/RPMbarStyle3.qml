import QtQuick 2.8
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4


Item {
    id: userDash
    anchors.fill: parent

      Image
      {
        id:groove1
        source:"qrc:/graphics/fueltechempty.png"
        anchors.top:parent.top
        anchors.left:parent.left
        smooth: true

        Item{
              id: displayWindow1
              height: parent.height
              width: (800*(Dashboard.rpm)/Dashboard.maxRPM)
              clip: true

                anchors.bottom: parent.bottom
                anchors.left: parent.left

              Image
              {
                id:speedarcfill
                anchors.top:parent.top
                anchors.left:parent.left
                source:"qrc:/graphics/fueltechfill.png"
                smooth: true
                z: 1
              }
            }

      PathInterpolator {
        id: motionPath
        property int value

           path: Path {
           startX: 0; startY: 189
           PathLine { x: 800; y: 480 }
         }
        progress: Dashboard.rpm / Dashboard.maxRPM
      }
}
//
        ShiftLights{}


        Text {
            x: 0
            y: 43
            font.pixelSize: 70
            font.bold: true
            color: "white"
            text: Dashboard.rpm
            horizontalAlignment: Text.AlignLeft
            font.letterSpacing: 3
            font.wordSpacing: 0
        }
}
