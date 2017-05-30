import QtQuick 2.4
import QtGraphicalEffects 1.0
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4


//first try of full parameterised gauge

Rectangle {
        id: horizontalBarGauge
        width: 260
        height: 85
        color: "transparent"
        anchors.left: parent.left
        anchors.top : parent.top


        property alias title: titleText.text
        property alias type: gauge.value


        Gauge {
            id: gauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 6
            tickmarkStepSize : 70
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 300

            //value: Dashboard.MAP
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                id: titleText
                font.pixelSize: (parent.height / 3)
                anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  parent.height /3

                    color: Qt.rgba(gauge.value / gauge.maximumValue, 0, 1 - gauge.value / gauge.maximumValue, 1)
                }

              }

        }
    }

