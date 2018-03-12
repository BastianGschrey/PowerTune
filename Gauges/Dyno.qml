import QtQuick 2.8
import QtCharts 2.1
import QtQuick.Controls 2.1

Item {
    anchors.fill: parent
    property double finalPower
    property double finalTorque
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
            x: 5
            y: 5
            spacing: 5
            Button {
                id: startButton
                text: "Start"
                onClicked: {
                    if (refreshTimer.running == false) refreshTimer.running = true, previousrpm = Dashboard.revs, finalPower =0, finalTorque =0;


                }
            }
            Button {
                id: stopButton
                text: "clear"
                onClicked: {
                    series2.clear(),series1.clear();

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
            name: "Power " + finalPower + " " + powertext
            axisX: axisX
            axisY: axisY1
        }

        SplineSeries {
            id: series2
            name: "Torque " + finalTorque + " " + torquetext
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

            if (previousrpm <= Dashboard.revs)
            {

            previousrpm = Dashboard.revs

            if (finalPower < Dashboard.Power)
            {finalPower = Dashboard.Power}
            if (finalTorque < Dashboard.Torque)
            {finalTorque = Dashboard.Torque}

            series1.append(Dashboard.revs, Dashboard.Power);
            series2.append(Dashboard.revs, Dashboard.Torque);
            }
            if (previousrpm > Dashboard.revs) {refreshTimer.running = false}

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
}
