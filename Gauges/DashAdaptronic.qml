import QtQuick 2.4
import QtGraphicalEffects 1.0
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4




Rectangle {
    width: parent.width
    height: parent.height
    color: "black"


//Left Row with 7 Bars


    Rectangle {
        id: rev
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.left: parent.left
        anchors.top: parent.top

        Gauge {
            id: revgauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 4
            tickmarkStepSize : 5000
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 10000

            value: Dashboard.revs
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                text:"RPM " + Dashboard.revs
                font.pixelSize: (parent.height / 3)
                anchors.top : parent.top
                // anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  rev.height /3
                    color: Qt.rgba(revgauge.value / revgauge.maximumValue, 0, 1 - revgauge.value / revgauge.maximumValue, 1)
                }
            }
      }
    }
    Rectangle {
        id: pim
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.left: parent.left
        anchors.top : rev.bottom

        Gauge {
            id: pimgauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 6
            tickmarkStepSize : 70
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 300

            value: Dashboard.MAP
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                text:"MAP " + Dashboard.MAP + "kpa "
                font.pixelSize: (parent.height / 3)
                 anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  rev.height /3

                    color: Qt.rgba(pimgauge.value / pimgauge.maximumValue, 0, 1 - pimgauge.value / pimgauge.maximumValue, 1)
                }
            }
      }
    }
    Rectangle {
        id : airtemp
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.left: parent.left
        anchors.top : pim.bottom

        Gauge {
            id: airtempgauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 6
            tickmarkStepSize : 70
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 120

            value: Dashboard.Intaketemp
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
               text:"Air Temp " + Dashboard.Intaketemp + "°C "
                font.pixelSize: (parent.height / 3)
                 anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  rev.height /3

                    color: Qt.rgba(airtempgauge.value / airtempgauge.maximumValue, 0, 1 - airtempgauge.value / airtempgauge.maximumValue, 1)
                }
            }
      }
    }
    Rectangle {
        id: watertemp
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.left: parent.left
        anchors.top : airtemp.bottom

        Gauge {
            id: watertempgauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 6
            tickmarkStepSize : 70
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 120

            value: Dashboard.Watertemp
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                text:"Coolant " + Dashboard.Watertemp + "°C "
                font.pixelSize: (parent.height / 3)
                 anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  rev.height /3

                    color: Qt.rgba(watertempgauge.value / watertempgauge.maximumValue, 0, 1 - watertempgauge.value / watertempgauge.maximumValue, 1)
                }
            }
      }
    }
    Rectangle {
        id: auxT
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.left: parent.left
        anchors.top : watertemp.bottom

        Gauge {
            id: auxTgauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 6
            tickmarkStepSize : 70
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 120

            value: Dashboard.AUXT
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                text:"AUX Temp " + Dashboard.AUXT + "°C "
                font.pixelSize: (parent.height / 3)
                 anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  rev.height /3

                    color: Qt.rgba(auxTgauge.value / auxTgauge.maximumValue, 0, 1 - auxTgauge.value / auxTgauge.maximumValue, 1)
                }
            }
      }
    }
    Rectangle {
        id: afr
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.left: parent.left
        anchors.top : auxT.bottom

        Gauge {
            id: afrgauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 4
            tickmarkStepSize : 10
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 20

            value: Dashboard.auxcalc1
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                text:"AFR " + Dashboard.auxcalc1
                font.pixelSize: (parent.height / 3)
                 anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  rev.height /3

                    color: Qt.rgba(afrgauge.value / afrgauge.maximumValue, 0, 1 - afrgauge.value / afrgauge.maximumValue, 1)
                }
            }
      }
    }
    Rectangle {
        id: knock
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.left: parent.left
        anchors.top : afr.bottom


        Gauge {
            id: knockgauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 0
            tickmarkStepSize : 125
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 250

            value: Dashboard.Knock
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                text:"Knock " + Dashboard.Knock
                font.pixelSize: (parent.height / 3)
                 anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  rev.height /3

                    color: Qt.rgba(knockgauge.value / knockgauge.maximumValue, 0, 1 - knockgauge.value / knockgauge.maximumValue, 1)
                }
            }
      }
    }



//Middle Row with 7 Bars

    Rectangle {
        id: mvss
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

        Gauge {
            id: mvssgauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 0
            tickmarkStepSize : 100
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 300

            value: Dashboard.MVSS
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                text:"MSpeed " + Dashboard.MVSS + "KMH"
                font.pixelSize: (parent.height / 3)
                 anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  rev.height /3

                    color: Qt.rgba(mvssgauge.value / mvssgauge.maximumValue, 0, 1 - mvssgauge.value / mvssgauge.maximumValue, 1)
                }
            }
      }
    }
    Rectangle {
        id: svss
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top : mvss.bottom

        Gauge {
            id: svssgauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 0
            tickmarkStepSize : 100
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 300

            value: Dashboard.SVSS
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                text:"SSpeed " + Dashboard.SVSS + "KMH"
                font.pixelSize: (parent.height / 3)
                 anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  rev.height /3

                    color: Qt.rgba(svssgauge.value / svssgauge.maximumValue, 0, 1 - svssgauge.value / svssgauge.maximumValue, 1)
                }
            }
      }
    }


    Rectangle {
        id: inj1
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top : svss.bottom

        Gauge {
            id: inj1gauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 6
            tickmarkStepSize : 1000
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 1000

            value: Dashboard.Inj1
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                text:"inj1 pulse " + Dashboard.Inj1 + " μs"
                font.pixelSize: (parent.height / 3)
                anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  rev.height /3

                    color: Qt.rgba(inj1gauge.value / inj1gauge.maximumValue, 0, 1 - inj1gauge.value / inj1gauge.maximumValue, 1)
                }
            }
      }
    }
    Rectangle {
        id: inj2
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top : inj1.bottom

        Gauge {
            id: inj2gauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 6
            tickmarkStepSize : 1000
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 1000

            value: Dashboard.Inj2
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                text:"inj2 pulse " + Dashboard.Inj2 + " μs"
                font.pixelSize: (parent.height / 3)
                 anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  rev.height /3

                    color: Qt.rgba(inj2gauge.value / inj2gauge.maximumValue, 0, 1 - inj2gauge.value / inj2gauge.maximumValue, 1)
                }
            }
      }
    }
    Rectangle {
        id: inj3
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: inj2.bottom

        Gauge {
            id: inj3gauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 6
            tickmarkStepSize : 1000
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 1000

            value: Dashboard.Inj3
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                text:"inj3 pulse " + Dashboard.Inj3 + " μs"
                font.pixelSize: (parent.height / 3)
                 anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  rev.height /3

                    color: Qt.rgba(inj3gauge.value / inj3gauge.maximumValue, 0, 1 - inj3gauge.value / inj3gauge.maximumValue, 1)
                }
            }
      }
    }
    Rectangle {
        id:inj4
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: inj3.bottom

        Gauge {
            id: inj4gauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 6
            tickmarkStepSize : 1000
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 1000

            value: Dashboard.Inj4
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                text:"inj4 pulse " + Dashboard.Inj4 + " μs"
                font.pixelSize: (parent.height / 3)
                 anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  rev.height /3

                    color: Qt.rgba(inj4gauge.value / inj4gauge.maximumValue, 0, 1 - inj4gauge.value / inj4gauge.maximumValue, 1)
                }
            }
      }
    }
    Rectangle {
        id: idle
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top : inj4.bottom

        Gauge {
            id: idleValuegauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 0
            tickmarkStepSize : 120
            minimumValue: 0
            maximumValue: 120

            value: Dashboard.IdleValue
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                text:"Idle Step Duty " + Dashboard.IdleValue
                font.pixelSize: (parent.height / 3)
                 anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  rev.height /3

                    color: Qt.rgba(idleValuegauge.value / idleValuegauge.maximumValue, 0, 1 - idleValuegauge.value / idleValuegauge.maximumValue, 1)
                }
            }
      }
    }
 //7 Bars on the right

    Rectangle {
        id: tps
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.right: parent.right
        anchors.top : parent.top

        Gauge {
            id: tpsgauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 4
            tickmarkStepSize : 50
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 100

            value: Dashboard.TPS
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                text:"TPS " + Dashboard.TPS + "%"
                font.pixelSize: (parent.height / 3)
                 anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  rev.height /3

                    color: Qt.rgba(tpsgauge.value / tpsgauge.maximumValue, 0, 1 - tpsgauge.value / tpsgauge.maximumValue, 1)
                }
            }
      }
    }
    Rectangle {
        id: battery
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.right: parent.right
        anchors.top : tps.bottom

        Gauge {
            id: batteryVgauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 0
            tickmarkStepSize : 15
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 15

            value: Dashboard.BatteryV
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                text:"Battery " + Dashboard.BatteryV + "V "
                font.pixelSize: (parent.height / 3)
                 anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  rev.height /3

                    color: Qt.rgba(batteryVgauge.value / batteryVgauge.maximumValue, 0, 1 - batteryVgauge.value / batteryVgauge.maximumValue, 1)
                }
            }
      }
    }
    Rectangle {
        id: ign1
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.right: parent.right
        anchors.top : battery.bottom

        Gauge {
            id: ign1gauge
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 6
            tickmarkStepSize : 70
            //labelStepSize: 50
            minimumValue: -40
            maximumValue: 40

            value: Dashboard.Ign1
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                text:"IGN1 " + Dashboard.Ign1 + " Deg "
                font.pixelSize: (parent.height / 3)
                 anchors.top : parent.top
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth:  rev.height /3

                    color: Qt.rgba(ign1gauge.value / ign1gauge.maximumValue, 0, 1 - ign1gauge.value / ign1gauge.maximumValue, 1)
                }
            }
      }
 }
    Rectangle {
        id: ign2
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.right: parent.right
        anchors.top :ign1.bottom
    Gauge {
        id: ign2gauge
        anchors.fill: parent
        anchors.margins: 10
        orientation : Qt.Horizontal
        minorTickmarkCount: 6
        tickmarkStepSize : 70
        //labelStepSize: 50
        minimumValue: -40
        maximumValue: 40

        value: Dashboard.Ign2
        Behavior on value {
            NumberAnimation {
                duration: 5
            }
        }
        Text {
            text:"IGN2 " + Dashboard.Ign2 + " Deg "
            font.pixelSize: (parent.height / 3)
             anchors.top : parent.top
            font.bold: true
            font.family: "Eurostile"
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
        }
          style: GaugeStyle {
            valueBar: Rectangle {
               implicitWidth:  rev.height /3

                color: Qt.rgba(ign2gauge.value / ign2gauge.maximumValue, 0, 1 - ign2gauge.value / ign2gauge.maximumValue, 1)
            }
        }
  }
}
    Rectangle {
        id: ign3
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.right: parent.right
        anchors.top :ign2.bottom
Gauge {
    id: ign3gauge
    anchors.fill: parent
    anchors.margins: 10
    orientation : Qt.Horizontal
    minorTickmarkCount: 6
    tickmarkStepSize : 70
    //labelStepSize: 50
    minimumValue: -40
    maximumValue: 40

    value: Dashboard.Ign3
    Behavior on value {
        NumberAnimation {
            duration: 5
        }
    }
    Text {
        text:"IGN3 " + Dashboard.Ign3 + " Deg "
        font.pixelSize: (parent.height / 3)
         anchors.top : parent.top
        font.bold: true
        font.family: "Eurostile"
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
    }
      style: GaugeStyle {
        valueBar: Rectangle {
           implicitWidth:  rev.height /3

            color: Qt.rgba(ign3gauge.value / ign3gauge.maximumValue, 0, 1 - ign3gauge.value / ign3gauge.maximumValue, 1)
        }
    }
}
    }
Rectangle {
    id: ign4
    width: parent.width /3.2
    height: parent.height /7
    color: "transparent"
    anchors.right: parent.right
    anchors.top :ign3.bottom
Gauge {
id: ign4gauge
anchors.fill: parent
anchors.margins: 10
orientation : Qt.Horizontal
minorTickmarkCount: 6
tickmarkStepSize : 70
//labelStepSize: 50
minimumValue: -40
maximumValue: 40

value: Dashboard.Ign4
Behavior on value {
    NumberAnimation {
        duration: 5
    }
}
Text {
    text:"IGN4 " + Dashboard.Ign4 + " Deg "
    font.pixelSize: (parent.height / 3)
     anchors.top : parent.top
    font.bold: true
    font.family: "Eurostile"
    color: "white"
    anchors.horizontalCenter: parent.horizontalCenter
}
  style: GaugeStyle {
    valueBar: Rectangle {
       implicitWidth:  rev.height /3

        color: Qt.rgba(ign4gauge.value / ign4gauge.maximumValue, 0, 1 - ign4gauge.value / ign4gauge.maximumValue, 1)
    }
}
}
}
    Rectangle {
        id: trim
        width: parent.width /3.2
        height: parent.height /7
        color: "transparent"
        anchors.right: parent.right
        anchors.top :ign4.bottom
Gauge {
    id: trimgauge
    anchors.fill: parent
    anchors.margins: 10
    orientation : Qt.Horizontal
    minorTickmarkCount: 0
    tickmarkStepSize : 50
    //labelStepSize: 50
    minimumValue: 0
    maximumValue: 100

    value: Dashboard.TRIM
    Behavior on value {
        NumberAnimation {
            duration: 5
        }
    }
    Text {
        text:"TRIM " + Dashboard.TRIM + " % "
        font.pixelSize: (parent.height / 3)
         anchors.top : parent.top
        font.bold: true
        font.family: "Eurostile"
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
    }
      style: GaugeStyle {
        valueBar: Rectangle {
           implicitWidth:  rev.height /3

            color: Qt.rgba(trimgauge.value / trimgauge.maximumValue, 0, 1 - trimgauge.value / trimgauge.maximumValue, 1)
        }
    }
}
}

 }
