import QtQuick 2.0
import QtGraphicalEffects 1.0
Item {

    property int revolutions: 0

    height: (parent.width / 1.5)
    width: height
    x: (parent.width / 2) - (width / 2)
    y: (parent.height / 2) - (height / 2)

    Image {
         id: innerRingRect
         height: parent.height
         width: parent.width
         source: "/graphics/Tacho_Mitte.png"


         Text {
             id: revdigit
             text: revolutions
             font.pixelSize: (parent.width / 5)
             font.bold: true
             font.family: "Eurostile"
             y: (parent.width / 3)
             color: "white"
             anchors.horizontalCenter: parent.horizontalCenter
         }

         DropShadow {
                 anchors.fill: revdigit
                 horizontalOffset: 0
                 verticalOffset: 8
                 radius: 4.0
                 samples: 16
                 color: "black"
                 source: revdigit
             }

         Text {
             text: "BOOST PSI"
             font.pixelSize: (parent.width / 14)
              y: (parent.width / 5)
             font.bold: true
             font.family: "Eurostile"
             color: "white"
             anchors.horizontalCenter: parent.horizontalCenter
         }
    }
}
