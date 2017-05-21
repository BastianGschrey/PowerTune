import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import com.powertune 1.0

ApplicationWindow {


    visible: true
    minimumWidth: 800
    minimumHeight: 480
    // visibility: "FullScreen"
    title: qsTr("PowerTune")
    color: "black"

//Pane {
//    id: pane

    SwipeView {
        id: view

        currentIndex: 1
        anchors.fill: parent

        Item {
            id: firstPage
            Dashboard{}
        }
        Item {
            id: secondPage
            Advanced{}
        }
        Item {
            id: thirdPage
            HalfGauges_metric{}
        }
        Item {
            id: forthPage
            DashAdaptronic{}
        }
        Item {
            id: fifthPage
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
