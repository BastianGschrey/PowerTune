import QtQuick 2.8
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import "../Gauges"
import "qrc:/Gauges/createsquaregaugeUserDash.js" as CreateSquareGaugeScript


Item {
    id: userDash
    anchors.fill: parent

    property var val1: false
    property var val2: false
    property var val3: false
    property double val4 : 20000
    property int val5 : -20000



    Connections{
        target: Dashboard
        onDashsetupChanged: {
            //Need to do this nicer but it works
            if (dashvalue.textAt(8) == "true") {val1 = true};
            if (dashvalue.textAt(8) == "false") {val1 = false};
            if (dashvalue.textAt(9) == "true") {val2 = true};
            if (dashvalue.textAt(9) == "false") {val2 = false};
            if (dashvalue.textAt(10) == "true") {val3 = true};
            if (dashvalue.textAt(10) == "false") {val3 = false};
            if (dashvalue.textAt(14) != "") {val4 = dashvalue.textAt(14),console.log("Hello " + dashvalue.textAt(14));}else {val4 = 20000;}
            if (dashvalue.textAt(15) != "") {val5 = dashvalue.textAt(15),console.log("Hello2 " + dashvalue.textAt(15));}else {val5 = -20000;}

            CreateSquareGaugeScript.createSquareGauge(dashvalue.textAt(0),dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7),val1,val2,val3,Dashboard,dashvalue.textAt(12),dashvalue.textAt(13),val4,val5);

        }
    }
    ComboBox{
        id: dashvalue
        width: 200
        model: Dashboard.dashsetup
        visible:false
        Component.onCompleted: Connect.readdashsetup()
    }

    Rectangle{
    anchors.fill: parent
    z:100 //This makes the Rectangle appear in front of the bar gauges
    color: "transparent"
    WarningLoader{}
    }

}







