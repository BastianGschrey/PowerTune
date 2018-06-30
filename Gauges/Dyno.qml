import QtQuick 2.8
import QtCharts 2.1
import QtQuick.Controls 2.1

Item {
    anchors.fill: parent
    property double finalPower
    property double finalTorque
    property int finalTorqueRPM
    property int finalPowerRPM
    property double previousrpm
    property var powertext
    property var torquetext
    property var unit : Dashboard.units;
    Component.onCompleted: {units.unitadjust()} // adjusts the Gauges to metric or imperial

    ChartView {
        title: "PowerTune Virtual Dyno V1.0"
        titleColor: "white"
        titleFont.pixelSize: parent.width /40
        id: chartView
        theme: ChartView.ChartThemeDark
        anchors.fill: parent
        legend.visible: true
        legend.font.pixelSize: parent.width /40
        antialiasing: true


        Row {
            anchors.top :parent.top
            anchors.topMargin: parent.height / 20
            spacing: 5
            Button {
                id: startButton
                text: "Start"
                onClicked: {
                    if (refreshTimer.running == false) refreshTimer.running = true ,series2.clear(),series1.clear(), previousrpm = Dashboard.rpm, finalPower =0, finalTorque =0, finalTorqueRPM = 0, finalPowerRPM =0,startButton.enabled =false;


                }
            }
            Button {
                id: stopButton
                text: "clear"
                onClicked: {
                    series2.clear(),series1.clear(),startButton.enabled =true;

                }
            }
        }
        ValueAxis {
            id: axisX
            titleText: "RPM"
            titleFont.pixelSize: parent.width /50
            titleFont.bold: true
            min: 0
            max: 9000
            tickCount: 10
            labelFormat: "%.0f";

        }

        ValueAxis {
            id: axisY1
            titleText: "Torque " + "(" + torquetext + ")" + " / Power "+ "(" +powertext + ")"
            titleFont.pixelSize: parent.width /50
            min: 0
            max: 500
            labelFormat: "%.0f";

        }


        SplineSeries {
            id: series1
            name: "Power " + finalPower + " " + powertext +" @" + finalPowerRPM + " RPM"
            axisX: axisX
            axisY: axisY1
        }

        SplineSeries {
            id: series2
            name: "Torque " + finalTorque + " " + torquetext +" @" + finalTorqueRPM + " RPM"
            axisX: axisX
            axisY: axisY1
        }
    }

    //


    // Add data dynamically to the series
    Timer {

        id: refreshTimer
        interval: 50
        running: false
        repeat: true
        onTriggered: {

            if (previousrpm <= Dashboard.rpm)
            {

            previousrpm = Dashboard.rpm

            if (finalPower < Dashboard.Power)
            {finalPower = (Dashboard.Power).toFixed(1),finalPowerRPM = Dashboard.rpm}
            if (finalTorque < Dashboard.Torque)
            {finalTorque = (Dashboard.Torque).toFixed(1) ,finalTorqueRPM = Dashboard.rpm}
            series1.append(Dashboard.rpm, Dashboard.Power);
            series2.append(Dashboard.rpm, Dashboard.Torque);
            }
            if (previousrpm > Dashboard.rpm) {refreshTimer.running = false,startButton.enabled =true}

        }
    }

    Item {
        id: units
        function unitadjust()
        {
            if (unit == "imperial") {powertext = "HP",torquetext = "ft-lbs"};
            if (unit == "metric") {powertext = "KW",torquetext = "NM"};
        }


    }
    Rectangle{
    anchors.fill: parent
    color: "transparent"
    WarningLoader{}
    }
}
