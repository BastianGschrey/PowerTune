import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import "qrc:/Gauges/createverticalbargauge.js" as CreateVerticalGaugeScript



Item {
id: adaptronicDash
//Component.onCompleted: CreateVerticalGaugeScript.createVerticalGauge(300,10,10,"rpm","RPM","Dashboard.revs");
Component.onCompleted: CreateVerticalGaugeScript.createVerticalGauge(300,10,300,"map","MAP",Dashboard);


 }
