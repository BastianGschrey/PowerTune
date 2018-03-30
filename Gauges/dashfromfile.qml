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
import "qrc:/Gauges/createsquaregauge.js" as CreateSquareGaugeScript

Item {
//Call Connect.cpp and read the UserDash.txt file ==> Works
Item {
Component.onCompleted: Connect.readdashsetup()
}

//Needto replace the combobox with a ListModel but this seems to work for now ( very shitty workarround)
ComboBox{
id: dashvalue
width: 200
model: Dashboard.dashsetup
visible:false
}

//Replace the button with a slot that is linked to the signal dashsetupChanged (this will setup a new gauge everytime a line in the text file is read )
Button{
    id: button
    anchors.centerIn: parent
    onClicked : CreateSquareGaugeScript.createSquareGauge(dashvalue.textAt(0),dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7),dashvalue.textAt(8),dashvalue.textAt(9),dashvalue.textAt(10),dashvalue.textAt(11),dashvalue.textAt(12),dashvalue.textAt(13));

}

/*
  Connect C++ Signal dashsetupChanged to a slot in QML , when slot is triggered create the gauge with the calues from the stringlist. ==> Help Needed
Connections {

    target: Dashboard
    ondashsetupChanged : CreateSquareGaugeScript.createSquareGauge(val1,val2,val3,val4,val5,val6,val7,val8,val9,val10,val11,val12,val13,val14),
}
*/

}
