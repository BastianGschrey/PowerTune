//Dashboard in style of a fueltech ecu Dashboard

import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import "qrc:/Gauges/createsquaregauge.js" as CreateSquareGaugeScript



Item {
id: adaptronicDash
//prototype of function:
//createVerticalGauge(setWidth,setHeight,setX,setY,setMaxValue,setDecPlace,setUnit,setID,setVertGaugeVis,setHoriGaugeVis,setSecValueVis,SetValueObject,SetValuePropertyMain,SetValuePropertySec)
Component.onCompleted:
    CreateSquareGaugeScript.createSquareGauge(200,150,10,180,300,0,"kPa","MAP",true,false,false,"Dashboard","MAP","MAP"),
    CreateSquareGaugeScript.createSquareGauge(165,150,220,180,300,2,"λ","Lambda",false,false,true,"Dashboard","LAMBDA","LAMBDATarget"),
    CreateSquareGaugeScript.createSquareGauge(200,120,10,340,150,0,"°C","MAT",false,true,false,"Dashboard","Intaketemp","Intaketemp"),
    CreateSquareGaugeScript.createSquareGauge(340,120,220,340,300,0,"°C","ECT",false,true,false,"Dashboard","Watertemp","Watertemp"),
    CreateSquareGaugeScript.createSquareGauge(165,150,395,180,100,0,"%","WG DC%",false,true,false,"Dashboard","BoostDuty","BoostDuty"),
    CreateSquareGaugeScript.createSquareGauge(215,280,570,180,500,0,"kPa","FuelP",true,false,false,"Dashboard","FuelPress","FuelPress");
/*
property int rpm: Dashboard.revs

         Gauge {
             id: gauge
             width: 800
             height: 200

             tickmarkStepSize: 0
             minorTickmarkCount: 0
             tickmarkAlignment: Qt.AlignBottom
             orientation: Qt.Horizontal

             value: parent.rpm
             minimumValue: 0
             maximumValue: 9000

             style: GaugeStyle {

                 valueBar: Rectangle {

                     width: 200
                     color: Qt.rgba(gauge.value / gauge.maximumValue, 0, 1 - gauge.value / gauge.maximumValue, 1)
                 }

                 background: Item {

                     Rectangle {
                         color: "yellow"
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
                 text: rpm
                 horizontalAlignment: Text.AlignLeft
                 font.letterSpacing: 3
                 font.wordSpacing: 0
                 font.family: "Verdana"

             }


         }


*/
}


