import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

Rectangle {
        id: initialID
        width: 250
        height: 200
        color: "black"
        border.color: "#9f9f9f"
        border.width: 2

        property alias title: gaugetextfield.text
        property alias mainunit: mainvalueunittextfield.text
        property alias vertgaugevisible: vertgauge.visible
        property alias horigaugevisible: horizgauge.visible
        property alias secvaluevisible: secondaryvaluetextfield.visible
        property alias secvalue: secondaryvaluetextfield.text
        property alias maintextvalue: mainvaluetextfield.text
        property alias mainvalue: mainvaluetextfield.text
        property alias maxvalue: vertgauge.maximumValue

        //property double mainvalue
        //property int maxvalue

        Rectangle {
            id: titlebar
            width: parent.width - 4
            //height: (parent.height) * 0.2
            height: 30
            anchors.top : parent.top
            anchors.left: parent.left
            color: "#808080"
            clip: false
            visible: true
            anchors.topMargin: 2
            anchors.leftMargin: 2

            Text {
                id: gaugetextfield
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 23
                font.bold: true
                //font.family: "Verdana"
                color: "white"

            }
        }

        Text {
            id: mainvaluetextfield
            /*anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 30*/
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 50
            //font.family: "Eurostile"
            color: "white"
        }

        Text {
            id: mainvalueunittextfield
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.verticalCenter: parent.verticalCenter

            font.pixelSize: 28
            //font.family: "Eurostile"
            font.bold: true
            color: "white"
        }


        Text {
            id: secondaryvaluetextfield
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            height: parent.height * 0.2
            font.pixelSize: 28
            //font.family: "Eurostile"
            color: "white"
        }

        Gauge {
            id: vertgauge
            height: parent.height - 50
            width: parent.width * 0.1
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            orientation: Qt.Vertical
            tickmarkStepSize : 0
            minorTickmarkCount: 0
            tickmarkAlignment: Qt.AlignRight
            value: parent.mainvalue
            //maximumValue: parent.maxvalue

            style: GaugeStyle {
                valueBar: Rectangle {
                    implicitWidth: 25
                    color: "#9f9f9f"
                }
            }

        }

        Gauge {
            id: horizgauge
            height: parent.height * 0.2
            width: parent.width * 0.9
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            orientation: Qt.Horizontal
            tickmarkStepSize : 0
            minorTickmarkCount: 0
            tickmarkAlignment: Qt.AlignRight
            value: parent.mainvalue
            maximumValue: parent.maxvalue

            style: GaugeStyle {
                valueBar: Rectangle {
                    implicitWidth: 25
                    color: "#9f9f9f"
                }
            }

        }


}
