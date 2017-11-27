import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import com.powertune 1.0

ApplicationWindow {


    visible: true
    width: 800
    height: 480
    minimumWidth: 800
    minimumHeight: 480
    // visibility: "FullScreen"
    title: qsTr("PowerTune ") + Dashboard.Platform + "Beta 19"
    color: "black"
    SwipeView {
        id: view

        currentIndex: 0
        anchors.fill: parent
 
        Loader {

            id: firstPageLoader
            source: "qrc:/Gauges/Dashboard.qml"

        }

        Loader {
            id: secondPageLoader
            source: "qrc:/Gauges/Racedash.qml"
        }
        
        Loader {
            id: fourthPageLoader
            source: "qrc:/Gauges/DashAdaptronic.qml"
        }
        Loader {
            id: fifthPageLoader
            source: "qrc:/Gauges/Charts.qml"
           
         }

        Loader {
            id: sixtPageLoader
            source: "qrc:/Gauges/PFCSensors.qml"
        }
        
        Loader {
            id: seventhPageLoader
            source: "qrc:/Gauges/GPS.qml"
        }

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

