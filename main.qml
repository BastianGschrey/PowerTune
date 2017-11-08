import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import com.powertune 1.0

ApplicationWindow {


    visible: true
    width: 800
    height: 480
    minimumWidth: 800
    minimumHeight: 480
    // visibility: "FullScreen"
    title: qsTr("PowerTune ") + Dashboard.Platform + "Beta 17"
    color: "black"
    SwipeView {
        id: view

        currentIndex: 0
        anchors.fill: parent
 
        Loader {

            id: firstPageLoader
            source: "qrc:/Gauges/RaceDash.qml"

        }

        Loader {
            id: secondPageLoader
            source: "qrc:/Gauges/PFCSensors.qml"
        }

        /*
        Loader {
            id: thirdPageLoader
            source: "qrc:/Gauges/PFCSensors.qml"
           // source: "qrc:/Gauges/HalfGauges_metric.qml"
        }
        */
        Loader {
            id: fourthPageLoader
            source: "qrc:/Gauges/DashAdaptronic.qml"
        }
        Loader {
            id: fifthPageLoader
            //source: "qrc:/Gauges/Charts.qml"
            source: "qrc:/Gauges/GPS.qml"
        
        /*
        Loader {
            id: sixtPageLoader
            source: "qrc:/Gauges/Dashboard.qml"
            //source: "qrc:/Gauges/DynamicDash.qml"

        }
        */
        Item {
            id:seventhPage
            Settings{}
        }
    }



    PageIndicator {
        id: indicator

        count: view.count
        currentIndex: view.currentIndex

        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}

