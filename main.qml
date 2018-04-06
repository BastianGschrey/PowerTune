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
    title: qsTr("PowerTune ") + Dashboard.Platform + " Beta 24"
    // visibility: "FullScreen"
    color: "black"
    Item {
        id: name
        Component.onCompleted: Connect.checkifraspberrypi()
    }
    SwipeView {
        id: view

        currentIndex: 0
        anchors.fill: parent
/*
        Loader {

            id: sensor
            source: "qrc:/Gauges/Camera.qml"

        }
*/
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

        Item {
            id:lastPage
            SerialSettings{}
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

