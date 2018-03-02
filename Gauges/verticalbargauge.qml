import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4



Rectangle {
        id: initalID
        width: 100
        height: 80
        color: "transparent"
        antialiasing: false
        //Drag.active: dragArea.drag.active

        property alias gaugetext: gaugetextfield.text
        property alias gaugevalue: gauge.value
        property alias gaugemaxvalue: gauge.maximumValue
        property alias gaugeminvalue: gauge.minimumValue



        MouseArea {
                  id: mouseArea
                  width: parent.width
                  height: parent.height + 10 // easier to get
                  anchors.centerIn: parent
                  //drag.target: parent
                  //drag.axis: Drag.XAndYAxis
                  //onClicked: touchmenu.popup(mouseX, mouseY)
                }

        /*Menu {
               id: touchmenu
               y: fileButton.height

               MenuItem {
                   text: "Change datasource"
                   onTriggered: sourcemenu.popup()
               }
               MenuItem {
                   text: "Increase size"
               }
               MenuItem {
                   text: "Decrease size"
               }
           }

        Menu{
            id: sourcemenu
            MenuItem {
                text: "RPM"
            }
            MenuItem {
                text: "MAP"
            }
            MenuItem {
                text: "Fuel Pressure"
                onTriggered: gaugetext = Dashboard.FuelPress, gaugevalue = 300, gaugemaxvalue = 600

            }
        }*/

        Gauge {
            id: gauge
            height: 200
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 4
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 400
            tickmarkStepSize : maximumValue / 4

            //value: Dashboard.MAP
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                id: gaugetextfield
                font.pixelSize: (parent.height / 3)
                anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  20
                    color: Qt.rgba(gauge.value / gauge.maximumValue, 0, 1 - gauge.value / gauge.maximumValue, 1)
                }
            }
      }
}
