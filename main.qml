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
    title: qsTr("PowerTune ") + Dashboard.Platform + " Beta 24"
    color: "black"
    SwipeView {
        id: view

        currentIndex: 0
        anchors.fill: parent
 

        Loader {

            id: firstPageLoader
            source: ""

        }

        Loader {
            id: secondPageLoader
            source: ""

        }
        Loader {
            id: thirdPageLoader
            source: ""

         }
        
        Loader {
            id: fourthPageLoader
            source: ""
        }
        Loader {
            id: test
            source: "qrc:/Gauges/SensorTest.qml"
        }
        Item {
            id:lastPage
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

