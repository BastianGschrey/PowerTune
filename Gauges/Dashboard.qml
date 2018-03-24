import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4



Item {
    id: view
    anchors.fill: parent
    Component.onCompleted: {units.unitadjust()} // adjusts the Gauges to metric or imperial

    property  var unit : Dashboard.units;

    //fade in effect for the Gauges (Welcome animation)
    OpacityAnimator {
        target: intro;
        from: 1;
        to: 0;
        duration: 400
        running: true
    }

    OpacityAnimator {
        target: leftgaugeticks;
        from: 0;
        to: 1;
        duration: 6000
        running: true
    }
    OpacityAnimator {
        target: rightgaugeticks;
        from: 0;
        to: 1;
        duration: 6000
        running: true
    }
    OpacityAnimator {
        target: speedometer;
        from: 0;
        to: 1;
        duration: 6000
        running: true
    }
    OpacityAnimator {
        target: revcounter;
        from: 0;
        to: 1;
        duration: 6000
        running: true
    }

    OpacityAnimator {
        id: speedoopacity
        target: speedoNeedlemph;
        from: 0;
        to: 1;
        duration: 6000
        running: true
    }

    OpacityAnimator {
        target: value1;
        from: 0;
        to: 1;
        duration: 6000
        running: true
    }
    OpacityAnimator {
        target: value2;
        from: 0;
        to: 1;
        duration: 6000
        running: true
    }
    OpacityAnimator {
        target: value1label;
        from: 0;
        to: 1;
        duration: 6000
        running: true
    }
    OpacityAnimator {
        target: value2label;
        from: 0;
        to: 1;
        duration: 6000
        running: true
    }

    //Backround image for the Gauges
    Image {
        id: backround
        width: parent.width
        height: parent.height
        fillMode: Image.PreserveAspectFit
        source: "/graphics/MainDash.png"

    }


    //Rectangle which is centered in the image as reference for the gauge overlay during scaling
    Rectangle
    {
        id: scalerect
        width: backround.paintedWidth
        height: backround.paintedHeight
        anchors.centerIn: backround
        color: "transparent"

        //Test
        Rectangle {
            color: "transparent"
            id: test
            height: scalerect.height /6
            width: scalerect.width /4.3
            anchors.left: scalerect.left
            anchors.leftMargin: scalerect.width /2.6
            anchors.bottom: scalerect.bottom
            anchors.bottomMargin: scalerect.height / 3.5 //127

            Text {
                id: value1label
                text:"AFR"
                font.pixelSize: scalerect.width / 55
                anchors.left: parent.left
                anchors.leftMargin: scalerect.width / 26
                anchors.bottom: parent.bottom
                font.bold: true
                font.family: "Eurostile"
                color: "white"

            }
            Text {
                id: value1
                text: (Dashboard.auxcalc1).toFixed(1)
                font.pixelSize: scalerect.width / 55
                anchors.right: parent.right
                anchors.rightMargin: scalerect.width / 26
                anchors.bottom: parent.bottom
                font.bold: true
                font.family: "Eurostile"
                color: "white"

            }
            Text {
                id: value2label
                text:"Boost"
                font.pixelSize: scalerect.width / 55
                anchors.bottom: value1label.top
                anchors.left: parent.left
                anchors.leftMargin: scalerect.width / 26
                font.bold: true
                font.family: "Eurostile"
                color: "white"

            }
            Text {
                id: value2
                text:(Dashboard.pim).toFixed(2)
                font.pixelSize: scalerect.width / 55
                anchors.right: parent.right
                anchors.rightMargin: scalerect.width / 26
                anchors.bottom: value1.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"

            }

        }
        //Small gauge on the left
        Rectangle {
            color: "transparent"
            id: leftgauge
            height: scalerect.height /5.3
            width: height
            anchors.left: scalerect.left
            anchors.leftMargin: scalerect.width /26.66
            anchors.bottom: scalerect.bottom
            anchors.bottomMargin: scalerect.height / 3.79 //127

            // Paint Tickmarks and Labels on the left gauge
            CircularGauge {
                id: leftgaugeticks
                height: parent.height
                width: height
                value: Dashboard.Watertemp
                anchors.verticalCenter: parent.verticalCenter
                minimumValue: 30
                maximumValue: 110
                style: DashboardGaugeStyle {
                    id: leftgaugetickstyle
                    labelStepSize: 30
                    tickmarkStepSize: 20
                    labelInset: toPixels(0.21)
                    minimumValueAngle: -160
                    maximumValueAngle: -50
                    needleLength: toPixels(1)
                    needleBaseWidth: toPixels(0.1)
                    needleTipWidth: toPixels(0.04)
                    tickmark: Rectangle {
                        implicitWidth: toPixels(0.03)
                        antialiasing: true
                        implicitHeight: toPixels(0.08)
                        color: styleData.index === 4  ? Qt.rgba(0.5, 0, 0, 1) : "#c8c8c8"
                    }
                    minorTickmark: null
                    tickmarkLabel: Text {
                        font.pixelSize: Math.max(6, toPixels(0.18))
                        text: styleData.value
                        color: styleData.index === 4 ? Qt.rgba(0.5, 0, 0, 1) : "#c8c8c8"
                        antialiasing: true
                    }
                }
            }
        }
        // small gauge on the right

        Rectangle {
            color: "transparent"
            id: rightgauge
            height: scalerect.height /5.3
            width: height
            anchors.right: scalerect.right
            anchors.rightMargin: scalerect.width /39
            anchors.bottom: scalerect.bottom
            anchors.bottomMargin: scalerect.height / 3.85

            // Paint Tickmarks and Labels on the right gauge
            CircularGauge {
                id: rightgaugeticks
                height: parent.height
                width: height
                value: Dashboard.Intaketemp
                anchors.verticalCenter: parent.verticalCenter
                minimumValue: 20
                maximumValue: 80
                //
                style: DashboardGaugeStyle {
                    labelStepSize: 30
                    tickmarkStepSize: 20
                    labelInset: toPixels(0.3)
                    minimumValueAngle: 160
                    maximumValueAngle: 45
                    needleLength: toPixels(1)
                    needleBaseWidth: toPixels(0.1)
                    needleTipWidth: toPixels(0.04)
                    tickmark: Rectangle {
                        implicitWidth: toPixels(0.03)
                        antialiasing: true
                        implicitHeight: toPixels(0.08)
                        color: styleData.index === 2 || styleData.index === 3 ? Qt.rgba(0.5, 0, 0, 1) : "#c8c8c8"
                    }
                    minorTickmark: null
                    tickmarkLabel: Text {
                        font.pixelSize: Math.max(6, toPixels(0.18))
                        text: styleData.value
                        color: styleData.index === 2 ||styleData.index === 3  ? Qt.rgba(0.5, 0, 0, 1) : "#c8c8c8"
                        antialiasing: true
                    }



                }
            }

            //test

        }

        Rectangle {
            width: parent.width /6
            height: parent.height /2
            color: "transparent"
            anchors.horizontalCenter: parent.horizontalCenter
            y :parent.height /4

        }

        //Rectangle in which the Speedometer Resides
        Rectangle {
            color: "transparent"
            id: speedo
            height: scalerect.height /2.08
            width: height
            anchors.left: scalerect.left
            anchors.leftMargin:  scalerect.width / 7.47
            anchors.top: scalerect.top
            anchors.topMargin: scalerect.height / 3.69


            // Paint Tickmarks and Labels on the Speedo
            CircularGauge {
                id: speedometer
                height: parent.height
                width: height

                value: Dashboard.speed
                anchors.verticalCenter: parent.verticalCenter
                maximumValue: 320

                style: DashboardGaugeStyle {
                    labelStepSize: 20
                    labelInset: toPixels(0.21)
                    needleLength: 0
                    needleTipWidth: 0
                    needleBaseWidth: 0
                }
            }
            // Speedo Needle animation
            GaugeNeedle_minus180to90  {
                //visible: false
                id: speedoNeedlekph
                anchors.verticalCenterOffset: 0
                anchors.centerIn: parent
                value: Dashboard.speed / 4.155844155844156

            }
            GaugeNeedle_minus180to90  {
                //visible: false
                id: speedoNeedlemph
                anchors.verticalCenterOffset: 0
                anchors.centerIn: parent
                value: Dashboard.speed / 2.597402597402597


            }
        }
        //Rectangle in which the rev counter resides
        Rectangle {
            color: "transparent"
            id: revcounter
            height: scalerect.height /2.08 //230
            width: height
            anchors.top: scalerect.top
            anchors.topMargin: scalerect.height / 3.69
            anchors.right: scalerect.right
            anchors.rightMargin:  scalerect.width / 8.1

            // Paint Tickmarks and Labels on the Rev counter
            CircularGauge {
                id: revcounterticks
                height: parent.height
                width: height
                value: Dashboard.revs
                anchors.verticalCenter: parent.verticalCenter
                maximumValue: 10

                style: TachometerStyle {
                    //labelStepSize: 1
                    //labelInset: toPixels(0.21)
                    minimumValueAngle: -90
                    maximumValueAngle: 180
                    needleLength: 0
                    needleTipWidth: 0
                    needleBaseWidth: 0
                }
            }



            GaugeNeedle_minus90to180  {
                id: revneedele
                anchors.verticalCenterOffset: 0
                anchors.centerIn: parent
                value: Dashboard.revs *0.0077

            }
        }
    }

    Rectangle {
        id: touchsurface
        width: parent.width
        height: parent.height
        color: "transparent"
/*
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            onClicked: pieMenu.popup(mouseX, mouseY)

        }
*/
        PieMenu {
            id: pieMenu

            MenuItem {
                text: "Customise"

                onTriggered: sourceselect.visible = true;
            }


        }

        Rectangle {
            id: sourceselect
            visible: false
            width: parent.width
            height: parent.height
            color: "transparent"

            Grid {
                rows: 10
                columns: 4
                spacing: 5
                Text { text: "Data Display 1"
                    color : "white" }
                Text { text: "Data Display 2"
                    color : "white" }
                Text { text: "Data Display 3"
                    color : "white" }
                Text { text: "Data Display 4"
                    color : "white" }
                ComboBox {
                    id: dash1
                    width: 180
                    model: sourcelist
                    property bool initialized: true
                    // onCurrentIndexChanged:{select1.selDash1() }
                    // Component.onCompleted: {select1.selDash1() }
                }

                ComboBox {
                    id: dash2
                    width: 180
                    model: sourcelist
                    property bool initialized: true
                    // onCurrentIndexChanged:{select1.selDash2() }
                    // Component.onCompleted: {select1.selDash2() }
                }

                ComboBox {
                    id: dash3
                    width: 180
                    model: sourcelist
                    property bool initialized: true
                    //onCurrentIndexChanged:{select1.selDash4() }
                    //Component.onCompleted: {select1.selDash4() }
                }
                ComboBox {
                    id: dash4
                    width: 180
                    model: sourcelist
                    property bool initialized: true
                    //  onCurrentIndexChanged:{select1.selDash4() }
                    //  Component.onCompleted: {select1.selDash4() }
                }

                Button {
                    id: btn_apply
                    text: "Apply"
                    onClicked: sourceselect.visible = false;
                }
                //ListModel
                ListModel {
                    id : sourcelist
                    ListElement {text:"RPM" }
                    ListElement {text:"PIM" }
                    ListElement {text:"PIM Voltage" }
                    ListElement {text:"Throttle Voltage" }
                    ListElement {text:"Primary Injector Pulse width" }
                    ListElement {text:"Fuel Temp" }
                    ListElement {text:"IGN 1" }
                    ListElement {text:"IGN 2" }
                    ListElement {text:"Fuel Temp" }
                    ListElement {text:"Metering Oil Pump" }
                    ListElement {text:"Boost TP" }
                    ListElement {text:"Boost WG" }
                    ListElement {text:"WaterTemp" }
                    ListElement {text:"Intake Temp" }
                    ListElement {text:"Knock" }
                    ListElement {text:"Battery Voltage" }
                    ListElement {text:"Speed" }
                    ListElement {text:"ISCV Duty" }
                    ListElement {text:"O2 Voltage" }
                    ListElement {text:"na1" }
                    ListElement {text:"Secinjpulse" }
                    ListElement {text:"Injector Duty" }
                    ListElement {text:"Engline Load" }
                    ListElement {text:"MAF1 Voltage" }
                    ListElement {text:"MAF2 Voltage" }
                    ListElement {text:"injms" }
                    ListElement {text:"Inj" }
                    ListElement {text:"Ign" }
                    ListElement {text:"Dwell" }
                    ListElement {text:"Boost Pressure" }
                    ListElement {text:"Boost Duty" }
                    ListElement {text:"MAF Activity" }
                    ListElement {text:"O2 Volt2" }
                }

            }
        }
    }
    //Setting the scale of the speedo and temp gauges according to metric or imperial
    Item {
        id: units
        function unitadjust()
        {
            if (unit == "imperial") {speedoopacity.target = speedoNeedlemph,speedometer.maximumValue = 200,speedoNeedlemph.visible = true, speedoNeedlekph.visible = false,revneedele.visible = true; leftgaugeticks.minimumValue =40,leftgaugeticks.maximumValue =220, rightgaugeticks.minimumValue = 40,rightgaugeticks.maximumValue = 190};
            if (unit == "metric") {speedoopacity.target = speedoNeedlekph,speedometer.maximumValue = 320,speedoNeedlemph.visible = false, speedoNeedlekph.visible = true,leftgaugeticks.minimumValue =30,leftgaugeticks.maximumValue =110, rightgaugeticks.minimumValue =20,rightgaugeticks.maximumValue = 80};
        }


    }
    Item {
        id: applysource
        function sourceapply()
        {

        }

    }
Rectangle
{
    id: intro
    anchors.fill: view
    color: "black"
}
}
