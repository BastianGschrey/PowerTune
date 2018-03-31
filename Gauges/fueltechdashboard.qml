//Dashboard in style of a fueltech ecu Dashboard

import QtQuick 2.8
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import "qrc:/Gauges/createsquaregauge.js" as CreateSquareGaugeScript



Item {
id: fueltechDash


//Needto replace the combobox with a ListModel but this seems to work for now ( very shitty workarround)
ComboBox{
id: dashvalue
width: 200
model: Dashboard.dashsetup
visible:true
}

//This slot is called every time a line from the UserDash.txt has been read
Connections{
target: Dashboard
//CreateSquareGaugeScript.createSquareGauge                                                                           (215,280,570,180,500,0,"kPa","FuelP",true,false,false,"Dashboard","FuelPress","FuelPress");
onDashsetupChanged: CreateSquareGaugeScript.createSquareGauge(dashvalue.textAt(0),dashvalue.textAt(1),dashvalue.textAt(2),dashvalue.textAt(3),dashvalue.textAt(4),dashvalue.textAt(5),dashvalue.textAt(6),dashvalue.textAt(7),true,false,false,Dashboard,dashvalue.textAt(12),dashvalue.textAt(13));
}

//Call Connect.cpp and read the UserDash.txt file ==> Works
Item {
Component.onCompleted: Connect.readdashsetup()
}






//
/*
//prototype of function:
//createVerticalGauge(setWidth,setHeight,setX,setY,setMaxValue,setDecPlace,setUnit,setID,setVertGaugeVis,setHoriGaugeVis,setSecValueVis,SetValueObject,SetValuePropertyMain,SetValuePropertySec)
Component.onCompleted:
    CreateSquareGaugeScript.createSquareGauge(200,150,10,180,300,0,"kPa","MAP",true,false,false,"Dashboard","MAP","MAP"),
    CreateSquareGaugeScript.createSquareGauge(165,150,220,180,300,2,"λ","Lambda",false,false,true,"Dashboard","LAMBDA","LAMBDATarget"),
    CreateSquareGaugeScript.createSquareGauge(200,120,10,340,150,0,"°C","MAT",false,true,false,"Dashboard","Intaketemp","Intaketemp"),
    CreateSquareGaugeScript.createSquareGauge(340,120,220,340,300,0,"°C","ECT",false,true,false,"Dashboard","Watertemp","Watertemp"),
    CreateSquareGaugeScript.createSquareGauge(165,150,395,180,100,0,"%","WG DC%",false,true,false,"Dashboard","BoostDuty","BoostDuty"),
    CreateSquareGaugeScript.createSquareGauge(215,280,570,180,500,0,"kPa","FuelP",true,false,false,"Dashboard","FuelPress","FuelPress");*/

         Gauge {
             id: revgauge
             width: 800
             height: 200

             tickmarkStepSize: 0
             minorTickmarkCount: 0
             tickmarkAlignment: Qt.AlignBottom
             orientation: Qt.Horizontal

             value: Dashboard.rpm
             minimumValue: 0
             maximumValue: 9000

             style: GaugeStyle {

                 valueBar: Rectangle {

                     width: 200
                     color: Qt.rgba(revgauge.value / revgauge.maximumValue, 0, 1 - revgauge.value / revgauge.maximumValue, 1)
                    }

                 }
             }


             Image {
                 height: 200
                 width: 800
                  source: "/graphics/vertrevcanvas.png"
             }


             Text {
                 x: 0
                 y: 43
                 font.pixelSize: 70
                 font.bold: true
                 color: "white"
                 text: Dashboard.rpm
                 horizontalAlignment: Text.AlignLeft
                 font.letterSpacing: 3
                 font.wordSpacing: 0
             }


}







