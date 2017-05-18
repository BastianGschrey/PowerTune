import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import com.powertune 1.0

ApplicationWindow {


    visible: true
    width: 800
    height: 480
    // visibility: "FullScreen"
    title: qsTr("PowerTune")
    color: "black"

    TabView {
        id: tabView
        anchors.fill: parent
        Tab {
            title: "Dashboard"
            Dashboard{}
        }
        Tab {
            title: "Adaptronic"
            DashAdaptronic{}
        }
        Tab {
            title: "Advanced Info"
            Advanced{}
        }

        Tab {
            title: "Imperial"
            Dashboard_Imperial{}
        }

        Tab {
            title: "Half Gauges Metric"
            HalfGauges_metric{}
        }
        Tab {
            title: "Serial settings"
            SerialSettings{}
        }




    }


}
