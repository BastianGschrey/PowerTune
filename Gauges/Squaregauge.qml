import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

Rectangle {

        id: initialID
        width: 250
        height: 200
        //color: "black"
        border.color: "#9f9f9f"
        border.width: 2
        Component.onCompleted: colorsettings.set()

        property alias title: gaugetextfield.text
        property alias mainunit: mainvalueunittextfield.text
        property alias vertgaugevisible: vertgauge.visible
        property alias horigaugevisible: horizgauge.visible
        property alias secvaluevisible: secondaryvaluetextfield.visible
        property alias secvalue: secondaryvaluetextfield.text
        property alias maintextvalue: mainvaluetextfield.text
        property alias mainvalue: mainvaluetextfield.text
        property alias maxvalue: vertgauge.maximumValue
        property alias titlecolor: titlebar.color
        property alias titlefontsize :gaugetextfield.font.pixelSize
        property alias mainfontsize :mainvaluetextfield.font.pixelSize
        property string resettitlecolor
        property string resetbackroundcolor
        property string framecolor
        property string titletextcolor
        property string textcolor
        property string barcolor
        property double mainvalue
        property int maxvalue
        property double warnvaluehigh: 20000
        property double warnvaluelow : -20000

        Rectangle {
            id: titlebar
            width: parent.width - 4
            //height: (parent.height) * 0.2
            height: 30
            anchors.top : parent.top
            anchors.left: parent.left
            color: titlecolor
            clip: false
            visible: true
            anchors.topMargin: 2
            anchors.leftMargin: 2

            }

        SequentialAnimation {
            id: anim
            loops: Animation.Infinite
            running: false
            PropertyAnimation {
                target: titlebar
                property: "color"
                from: "darkred"
                to: "red"
                duration: 500
            }
            PropertyAnimation {
                target: titlebar
                property: "color"
                from: "red"
                to: "darkred"
                duration: 500
            }
            }
        SequentialAnimation {
            id: anim2
            loops: Animation.Infinite
            running: false
            PropertyAnimation {
                target: initialID
                property: "color"
                from: "darkred"
                to: "red"
                duration: 500
            }
            PropertyAnimation {
                target: initialID
                property: "color"
                from: "red"
                to: "darkred"
                duration: 500
            }
            }
            Text {
                id: gaugetextfield
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 23
                font.bold: true
                font.family: "Eurostile"
                color: titletextcolor

            }

        Text {
            id: mainvaluetextfield
            /*anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 30*/
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 50
            font.family: "Eurostile"
            color: "white"
            onTextChanged: warningindication.warn()
        }

        Text {
            id: mainvalueunittextfield
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.verticalCenter: parent.verticalCenter

            font.pixelSize: 28
            font.family: "Eurostile"
            font.bold: true
            color: textcolor
        }


        Text {
            id: secondaryvaluetextfield
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            height: parent.height * 0.2
            font.pixelSize: 28
            font.family: "Eurostile"
            color: textcolor
        }

        Gauge {
            id: vertgauge
            height: parent.height - 50
            width: parent.width * 0.1
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 10
            orientation: Qt.Vertical
            minorTickmarkCount: 0
            tickmarkAlignment: Qt.AlignRight
            value: parent.mainvalue
            maximumValue: parent.maxvalue

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
                    implicitWidth: 25
                    color: barcolor
                }
            }

        }
        Item {
            //to change the warning
            id: warningindication
            function warn()
            {
               if (mainvaluetextfield.text > warnvaluehigh || mainvaluetextfield.text < warnvaluelow )anim.running = true,anim2.running = true;
               else anim.running = false,anim2.running = false,titlebar.color = resettitlecolor ,initialID.color = resetbackroundcolor;

            }
        }
        Item {
            //Set the colors of backround and Boarder
            id: colorsettings
            function set()
            {
            initialID.color = resetbackroundcolor;
            initialID.border.color = framecolor;
            }
        }
        Gauge {
            id: horizgauge
            height: parent.height * 0.2
            width: parent.width * 0.9
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 0
            //anchors.right: parent.right
            //anchors.rightMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter
            orientation: Qt.Horizontal
            minorTickmarkCount: 0
            tickmarkAlignment: Qt.AlignRight
            value: parent.mainvalue
            maximumValue: parent.maxvalue

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
                    implicitWidth: 25
                    color: barcolor
                }
            }

        }

}
