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
    CreateSquareGaugeScript.createSquareGauge(165,150,220,180,300,0,"λ","Lambda",false,false,true,"Dashboard","LAMBDA","LAMBDATarget"),
    CreateSquareGaugeScript.createSquareGauge(200,120,10,340,150,0,"°C","MAT",false,true,false,"Dashboard","Intaketemp","Intaketemp"),
    CreateSquareGaugeScript.createSquareGauge(340,120,220,340,300,0,"°C","ECT",false,true,false,"Dashboard","Watertemp","Watertemp"),
    CreateSquareGaugeScript.createSquareGauge(165,150,395,180,100,0,"%","WG DC%",false,true,false,"Dashboard","BoostDuty","BoostDuty"),
    CreateSquareGaugeScript.createSquareGauge(215,280,570,180,500,0,"kPa","FuelP",true,false,false,"Dashboard","FuelPress","FuelPress");



 }
