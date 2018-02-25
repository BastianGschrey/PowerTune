import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import "qrc:/Gauges/createverticalbargauge.js" as CreateVerticalGaugeScript



Item {
id: adaptronicDash
//createVerticalGauge(Width,height,X,Y,MAXVALUE,Unit,GAUGE-ID,DATASOURCE,DATA)
Component.onCompleted:
    CreateVerticalGaugeScript.createVerticalGauge(320,80,10,10,8000,"RPM","RPM",Dashboard,"revs"),
    CreateVerticalGaugeScript.createVerticalGauge(320,80,10,120,400,"kPa","MAP",Dashboard,"MAP"),
    CreateVerticalGaugeScript.createVerticalGauge(320,80,10,230,20,"V","BatV",Dashboard,"BatteryV"),
    CreateVerticalGaugeScript.createVerticalGauge(320,80,10,340,130,"°C Coolant","Coolant",Dashboard,"Watertemp"),
    CreateVerticalGaugeScript.createVerticalGauge(320,80,465,10,2,"λ","Lambda",Dashboard,"LAMBDA"),
    CreateVerticalGaugeScript.createVerticalGauge(320,80,465,120,2,"°C Air","IAT",Dashboard,"IntakeTemp");

 }
