import QtQuick 2.8
import QtCharts 2.1
import QtQuick.Controls 2.1

Item {
    anchors.fill: parent


    ChartView {
        title: "Chart Viewer"
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
                if (refreshTimer.running == false) refreshTimer.running = true;


            }
        }
        Button {
            id: stopButton
            text: "Stop"
            onClicked: {
                if (refreshTimer.running == true) refreshTimer.running = false;

            }
        }
}
        ValueAxis {
            id: axisX
            min: 0
            max: 100
            tickCount: 5
        }

        ValueAxis {
            id: axisY1
            min: 0
            max: 10000
        }
        ValueAxis {
            id: axisY2
            min: 0
            max: 300
        }

        SplineSeries {
            id: series1
            name: "RPM"
            axisX: axisX
            axisY: axisY1
        }

        SplineSeries {
            id: series2
            name: "SPEED"
            axisX: axisX
            axisY: axisY2
        }
    }

    //


    // Add data dynamically to the series
    Timer {
        property int amountOfData: 0 //So we know when we need to start
        property int timeline: 0 // Start of the timeline
        id: refreshTimer
        interval: 50
        running: false
        repeat: true
        onTriggered: {


               timeline++;
               amountOfData++; //This else is just to stop incrementing the variable unnecessarily

                //series1.append(timeline, 3000);
                //series2.append(timeline, 250);
                series1.append(timeline, Dashboard.revs);
                series2.append(timeline, Dashboard.speed);

                if(amountOfData > axisX.max){
                    axisX.min++;
                    axisX.max++;
                }


                //remove all data points that are not visible anymore
               if (series1.count > 100){

                   series1.remove(0);
                   series2.remove(0);

                    console.log (series1.count);}

 }
}
    Rectangle{
    anchors.fill: parent
    color: "transparent"
    WarningLoader{}
    }
}

