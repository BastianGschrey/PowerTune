import QtQuick 2.8
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtQml.Models 2.2


Rectangle {
        id: initalID
        width: 100
        height: 80
        color: "transparent"
        antialiasing: false
        Drag.active: dragArea.drag.active

        property alias gaugetext: gaugetextfield.text
        property alias gaugevalue: gauge.value
        property alias gaugemaxvalue: gauge.maximumValue


        MouseArea {
                  id: dragArea
                  width: parent.width
                  height: parent.height + 10 // easier to get
                  anchors.centerIn: parent
                  drag.target: parent
                  drag.axis: Drag.XAndYAxis
                  //onClicked: pieMenu.popup(mouseX, mouseY), console.log("clicked")
                }

        Gauge {
            id: gauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 4
            tickmarkStepSize : 5000
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 400

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
                   implicitWidth:  10
                    color: Qt.rgba(gauge.value / gauge.maximumValue, 0, 1 - gauge.value / gauge.maximumValue, 1)
                }
            }
      }
}
