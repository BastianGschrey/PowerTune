import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import "qrc:/Gauges/createverticalbargauge.js" as CreateVerticalGaugeScript



Item {
id: adaptronicDash
//createVerticalGauge(Width,height,X,Y,MINVALUE,MAXVALUE,Unit,GAUGE-ID,DATASOURCE,DATA)
Component.onCompleted:
    //left column
    CreateVerticalGaugeScript.createVerticalGauge(320,80,10,0,0,8000,"RPM","RPM",Dashboard,"revs"),
    CreateVerticalGaugeScript.createVerticalGauge(320,80,10,90,0,400,"kPa","MAP",Dashboard,"MAP"),
    CreateVerticalGaugeScript.createVerticalGauge(320,80,10,180,0,20,"V","BatV",Dashboard,"BatteryV"),
    CreateVerticalGaugeScript.createVerticalGauge(320,80,10,270,0,130,"°C Coolant","Coolant",Dashboard,"Watertemp"),
    CreateVerticalGaugeScript.createVerticalGauge(320,80,10,360,-50,50,"°Deg T.Leading","Leadingign",Dashboard,"Leadingign"),

    //right Column
    CreateVerticalGaugeScript.createVerticalGauge(320,80,465,0,0,2,"λ","Lambda",Dashboard,"LAMBDA"),
    CreateVerticalGaugeScript.createVerticalGauge(320,80,465,90,0,2,"λ Target","Lambda Target",Dashboard,"Intaketemp"),
    CreateVerticalGaugeScript.createVerticalGauge(320,80,465,180,0,100,"°C Air","IAT",Dashboard,"Intaketemp"),
    CreateVerticalGaugeScript.createVerticalGauge(320,80,465,270,0,100,"%DC Wastegate","WGDC",Dashboard,"BoostDuty"),
    CreateVerticalGaugeScript.createVerticalGauge(320,80,465,360,0,100,"kPa Fuel Pressure","FueLPress",Dashboard,"FuelPress");
 }
