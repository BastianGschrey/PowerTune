import QtQuick 2.8
import QtCharts 2.1
import QtQuick.Controls 2.1

Item {
    anchors.fill: parent
    property double finalPower
    property double finalTorque
    property double previousrpm



    ChartView {
        title: "Virtual Dyno"
        id: chartView
        theme: ChartView.ChartThemeDark
        anchors.fill: parent
        legend.visible: true
        antialiasing: false

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
            min: 0
            max: 10000
            tickCount: 11
        }

        ValueAxis {
            id: axisY1
            min: 0
            max: 700
        }


        SplineSeries {
            id: series1
            name: "Power"
            axisX: axisX
            axisY: axisY1
        }

        SplineSeries {
            id: series2
            name: "Torque"
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
}
