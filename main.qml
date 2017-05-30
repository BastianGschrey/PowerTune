import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import com.powertune 1.0

ApplicationWindow {


    visible: true
    minimumWidth: 800
    minimumHeight: 480
    // visibility: "FullScreen"
    title: qsTr("PowerTune ") + Dashboard.Platform
    color: "black"

//Pane {
//    id: pane



    SwipeView {
        id: view

        currentIndex: 0
        anchors.fill: parent
/*
        Item {
            width: 200; height: 200

            Loader { id: pageLoader }

            MouseArea {
                anchors.fill: parent
                onClicked: pageLoader.source = "qrc:/Gauges/Dashboard.qml"
            }
        }
*/
        Loader {

           id: firstPageLoader
           source: "qrc:/Gauges/Dashboard.qml"
        }

        Loader {
            id: secondPageLoader
            source: "qrc:/Gauges/PFCSensors.qml"
        }

        Loader {
            id: thirdPageLoader
           source: "qrc:/Gauges/HalfGauges_metric"
        }
        Loader {
            id: fourthPageLoader
            source: "qrc:/Gauges/DashAdaptronic.qml"
        }
        Item {
            id: fifthPage
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
