import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import "qrc:/Gauges/createverticalbargauge.js" as CreateVerticalGaugeScript



Item {
id: adaptronicDash
//createVerticalGauge(Width,height,X,Y,MAXVALUE,GAUGE-ID,DATASOURCE,DATA)
Component.onCompleted:
    CreateVerticalGaugeScript.createVerticalGauge(300,80,10,10,300,"RPM",Dashboard,"revs"),
    CreateVerticalGaugeScript.createVerticalGauge(300,80,10,100,400,"MAP",Dashboard,"MAP"),
    CreateVerticalGaugeScript.createVerticalGauge(300,80,10,190,20,"BatteryV",Dashboard,"BatteryV");

 }
