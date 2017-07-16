import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import com.powertune 1.0

ApplicationWindow {


    visible: true
    minimumWidth: 800
    minimumHeight: 480
    // visibility: "FullScreen"
    title: qsTr("PowerTune ") + Dashboard.Platform + "Beta 12"
    color: "black"

    //Pane {
    //    id: pane

    property real hideValue: 0
    Behavior on hideValue {
        NumberAnimation {duration: 200}
    }

    menuBar:  MenuBar {
        id: menu
        //__contentItem.scale: value                        // (1)
        //__contentItem.opacity: hideValue                  // (2)
        __contentItem.transform: Scale {yScale: hideValue}  // (3)

        Menu {
            id: m1
            title: "File"
            MenuItem { text: "Open..."
                onTriggered: {
                   hideValue = 0                            // hide the bar
                }
            }
            MenuItem { text: "Close"
                onTriggered: {
                   hideValue = 0                            // hide the bar
                }
            }
        }
    }
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
            source: "qrc:/Gauges/HalfGauges_metric.qml"
        }
        Loader {
            id: fourthPageLoader
            source: "qrc:/Gauges/DashAdaptronic.qml"
        }
        Loader {
            id: fifthPageLoader
            source: "qrc:/Gauges/GPS.qml"
        }
        Loader {
            id: sixtPageLoader
            source: "qrc:/Gauges/DynamicDash.qml"

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

