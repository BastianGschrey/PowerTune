/*
Todos :
Call Connect.cpp and read the UserDash.txt file ==> Done
in c++ read one line (one line = 1 gauge) and write values to QStringList dashsetup and expose to QML ==> Done
Connect C++ Signal dashsetupChanged to a slot in QML , when slot is triggered create the gauge with the calues from the stringlist. ==> Help Needed


*/
import QtQuick 2.8
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
//import "qrc:/Gauges/createsquaregauge.js" as CreateSquareGaugeScript

Item {
//Call Connect.cpp and read the UserDash.txt file ==> Works
Item {
Component.onCompleted: Connect.readdashsetup()
}

//This is just for testing , will only show the last line of the file is read
ComboBox{
id: justcheckingifthestringlistisreceived
width: 200
model: Dashboard.dashsetup
}

//


/*
  Connect C++ Signal dashsetupChanged to a slot in QML , when slot is triggered create the gauge with the calues from the stringlist. ==> Help Needed
Connections {

    target: Dashboard
    ondashsetupChanged : CreateSquareGaugeScript.createSquareGauge(val1,val2,val3,val4,val5,val6,val7,val8,val9,val10,val11,val12,val13,val14),
}
*/

}
