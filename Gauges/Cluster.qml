import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import "../Gauges"
import "qrc:/Gauges/createMaindash.js" as CreateGauges



Item {
    id: view
    anchors.fill: parent
    Component.onCompleted: {units.unitadjust()} // adjusts the Gauges to metric or imperial

    property bool val1: false
    property bool val2: false
    property bool val3: false
    property double val4 : 20000
    property int val5 : -20000
    property string val6 : "transparent"
    property string val7 : "transparent"
    property string val8 : "transparent"
    property string val9 : "transparent"
    property string val10 : "transparent"
    property string val11 : "transparent"
    property int val12
    property int val13

    Connections{
        target: Dashboard
        onMaindashsetupChanged: {
            //Need to do this nicer but it works
            //console.log(Dashboard.dashsetup1)
            if (dashvalue.textAt(8) === "true") {val1 = true};
            if (dashvalue.textAt(8) === "false") {val1 = false};
            if (dashvalue.textAt(9) === "true") {val2 = true};
            if (dashvalue.textAt(9) === "false") {val2 = false};
            if (dashvalue.textAt(10) === "true") {val3 = true};
            if (dashvalue.textAt(10) === "false") {val3 = false};
            if (dashvalue.textAt(14) !== "") {val4 = dashvalue.textAt(14);}else {val4 = 20000;}
            if (dashvalue.textAt(15) !== "") {val5 = dashvalue.textAt(15);}else {val5 = -20000;}
            if (dashvalue.textAt(16) !== "") {val6 = dashvalue.textAt(16);}else {val6 = "#9f9f9f";}
            if (dashvalue.textAt(17) !== "") {val7 = dashvalue.textAt(17);}else {val7 = "black";}
            if (dashvalue.textAt(18) !== "") {val8 = dashvalue.textAt(18);}else {val8 = "#9f9f9f";}
            if (dashvalue.textAt(19) !== "") {val9 = dashvalue.textAt(19);}else {val9 = "white";}
            if (dashvalue.textAt(20) !== "") {val10 = dashvalue.textAt(20);}else {val10 = "white";}
            if (dashvalue.textAt(21) !== "") {val11 = dashvalue.textAt(21);}else {val11 = "grey";}
            if (dashvalue.textAt(22) !== "") {val12 = dashvalue.textAt(22);}else {val12 = 28;}
            if (dashvalue.textAt(23) !== "") {val13 = dashvalue.textAt(23);}else {val13 = 50;}
            CreateGauges.createMainGauges(dashvalue.textAt(0),dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7),val1,val2,val3,Dashboard,dashvalue.textAt(12),dashvalue.textAt(13),val4,val5,val6,val7,val8,val9,val10,val11,val12,val13);

        }

    }

    //adjusts the Gauges to metric or imperial

    property  var unit : Dashboard.units;

    //fade in effect for the Gauges (Welcome animation)



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



    //Backround image for the Gauges
    Image {
        id: backround
        width: parent.width
        height: parent.height
        fillMode: Image.PreserveAspectFit
        source: "/graphics/MainDashnew.png"

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

        Rectangle{
            id: odotrip
            //height: scalerect.height /6
            height: scalerect.height /15
            width: scalerect.width /3.5
            anchors.left: scalerect.left
            anchors.leftMargin: scalerect.width / 2.75
            anchors.bottom: scalerect.bottom
            anchors.bottomMargin: scalerect.height / 3.6
            color: "transparent"


            Text {
                id: tripname
                text:"Trip "
                font.pixelSize: scalerect.width / 50
                anchors.right: trip.left
                anchors.bottom: odotrip.bottom
                font.family: "Eurostile"
                color: "grey"

            }
            Text {
                id: trip
                text:(Dashboard.Trip).toFixed(1)
                font.pixelSize: scalerect.width / 45
                anchors.right: tripunits.left
                anchors.bottom: odotrip.bottom
                font.bold: true
                font.family: "Eurostile"
                color: "grey"

            }
            Text {
                id: tripunits
                text:" km"
                font.pixelSize: scalerect.width / 50
                anchors.right: parent.right
                anchors.bottom: odotrip.bottom
                //font.bold: true
                font.family: "Eurostile"
                color: "grey"

            }
            Text {
                id: odoname
                text:"Total "
                font.pixelSize: scalerect.width / 50
                anchors.left: parent.left
                anchors.bottom: odotrip.bottom
                font.family: "Eurostile"
                color: "grey"

            }
            Text {
                id: odo
                text: (Dashboard.Odo).toFixed(0)
                font.pixelSize: scalerect.width / 45
                anchors.left: odoname.right
                anchors.bottom: odotrip.bottom
                font.bold: true
                font.family: "Eurostile"
                color: "grey"

            }
            Text {
                id: odounit
                text:" km"
                font.pixelSize: scalerect.width / 60
                anchors.left: odo.right
                anchors.bottom: odotrip.bottom
                font.family: "Eurostile"
                color: "grey"

            }
        }


        //Rectangle in which the Speedometer Resides
        Rectangle {
            color: "transparent"
            id: speedo
            height: scalerect.height /1.6
            width: height
            anchors.left: scalerect.left
            anchors.leftMargin: scalerect.width / 18.18 //44
            anchors.top: scalerect.top
            anchors.topMargin: scalerect.height / 9.23 //52


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
                    labelInset: toPixels(0.25)
                    needleLength: 0
                    needleTipWidth: 0
                    needleBaseWidth: 0
                    tickmarkLabel:  Text {
                        font.pixelSize: styleData.value >= speedometer.value+15 || styleData.value <= speedometer.value-15  ? speedo.height /22 : (speedometer.value-styleData.value)+speedo.height /11

                        text: styleData.value
                        font.bold : styleData.value >= speedometer.value+10 || styleData.value <= speedometer.value-10  ? false : true
                        color: styleData.value >= speedometer.value+10 || styleData.value <= speedometer.value-10  ? "grey" : "white"
                        antialiasing: true
                    }
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
            Image {
                id: speedoinner
                width: parent.width /1.70
                height: width
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
                source: "qrc:/graphics/Tacho_Mitte.png"

            }
            Text {
                id: speedinnertext
                text: Dashboard.speed
                font.pixelSize: scalerect.width / 20
                anchors.centerIn: parent
                font.family: "Eurostile"
                color: "white"

            }
        }
        //Rectangle in which the rev counter resides
        Rectangle {
            color: "transparent"
            id: revcounter
            height: scalerect.height /1.6
            width: height
            anchors.top: scalerect.top
            anchors.topMargin: scalerect.height / 9.23
            anchors.right: scalerect.right
            anchors.rightMargin: scalerect.height / 13 //44

            // Paint Tickmarks and Labels on the Rev counter
            CircularGauge {
                id: revcounterticks
                height: parent.height
                width: height
                value: Dashboard.rpm
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
                    tickmarkLabel:  Text {
                        font.pixelSize: styleData.value >= Dashboard.rpm/1000+0.5 || styleData.value <= Dashboard.rpm/1000-0.5  ? revcounterticks.height /22 : (revcounterticks.value-Dashboard.rpm/1000)+speedo.height /11
                        text: styleData.value
                        font.bold : styleData.value >= Dashboard.rpm/1000+0.5 || styleData.value <= Dashboard.rpm/1000-0.5  ? false : true
                        color: styleData.value <= Dashboard.rpm/1000 ? "white" : "grey"
                        antialiasing: true
                    }
                }

            }



            GaugeNeedle_minus90to180  {
                id: revneedele
                anchors.verticalCenterOffset: 0
                anchors.centerIn: parent
                value: Dashboard.rpm *0.0077

            }
            Image {
                id: revinner
                width: parent.width /1.70
                height: width
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
                source: "qrc:/graphics/Tacho_Mitte.png"

            }
            Text {
                id: revinnertesxt
                text: Dashboard.rpm
                font.pixelSize: scalerect.width / 20
                anchors.centerIn: parent
                font.family: "Eurostile"
                color: "white"

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
    //Setting the scale of the speedo and temp gauges according to metric or imperial
    Item {
        id: units
        function unitadjust()
        {
            if (unit == "imperial") {speedoopacity.target = speedoNeedlemph,speedometer.maximumValue = 200,speedoNeedlemph.visible = true, speedoNeedlekph.visible = false,revneedele.visible = true;tripunits.text = " mi",odounit.text = " mi" };
            if (unit == "metric") {speedoopacity.target = speedoNeedlekph,speedometer.maximumValue = 320,speedoNeedlemph.visible = false, speedoNeedlekph.visible = true,tripunits.text = " km" ,odounit.text = " km"};

        }


    }
    Item {
        id: applysource
        function sourceapply()
        {

        }

    }
    Item {
        id: userDash
        anchors.fill: parent



        ComboBox{
            id: dashvalue
            width: 200
            model: Dashboard.maindashsetup
            visible:false
            Component.onCompleted: {Connect.readMaindashsetup()}
        }



    }
Rectangle{
anchors.fill: view
color: "transparent"
WarningLoader{}
}
}
}
