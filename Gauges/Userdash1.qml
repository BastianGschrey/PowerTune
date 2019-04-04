import QtQuick 2.8
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import "../Gauges"
import "qrc:/Gauges/createsquaregaugeUserDash.js" as CreateSquareGaugeScript


Item {
    id: userDash
    anchors.fill: parent


    Connections{
        target: Dashboard

        onRpmstyle1Changed:
        {
            rpmgauge.selctor();
        }
    }

    Loader{
        id: rpmbarloader
        anchors.fill:parent
        source: ""
    }
    ComboBox{
        id: dashvalue
        width: 200
        model: Dashboard.dashsetup1
        visible:false
        Component.onCompleted: {Connect.readdashsetup1(),rpmgauge.selctor();}
    }
    Item{
        id: rpmgauge
        function selctor()
        {
            switch (Dashboard.rpmstyle1) {

            case 0:
            {
                rpmbarloader.source = ""
                break;
            }
            case 1:
            {
                rpmbarloader.source = "qrc:/Gauges/RPMBarStyle1.qml"
                break;
            }
            case 2:
            {
                rpmbarloader.source = "qrc:/Gauges/RPMBARStyle2.qml"
                break;
            }
            case 3:
            {
                rpmbarloader.source = "qrc:/Gauges/RPMbarStyle3.qml"
                break;
            }
            case 4:
            {
                rpmbarloader.source = "qrc:/Gauges/RPMbar.qml"
                break;
            }
            }
        }
    }
    Rectangle{
        anchors.fill: parent
        z:100 //This makes the Rectangle appear in front of the bar gauges
        color: "transparent"
        WarningLoader{}
    }

}







