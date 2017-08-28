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




    Rectangle {
        width: parent.width /6
        height: parent.height /2
        color: "transparent"
        anchors.horizontalCenter: parent.horizontalCenter
        y :parent.height /4
/*
        Timer {
            running: true
            repeat: true
            interval: 2000
            onTriggered: gauge.value = gauge.value == gauge.maximumValue ? 5 : gauge.maximumValue
        }
*/
        Gauge {
            id: gauge
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
                font.pixelSize: (parent.width / 14)
                 y: (parent.heigth / 22)
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth: 20

                    color: Qt.rgba(gauge.value / gauge.maximumValue, 0, 1 - gauge.value / gauge.maximumValue, 1)
                }
            }
      }
    }
    Rectangle{
        id: displaybox
        color: "lightsteelblue"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width /7
        height: parent.height /4
    Text {
        id: afrtext
        text:"Battery Voltage"
        font.pixelSize: (parent.width / 10)
         y: parent.height / 4
        font.bold: true
        font.family: "Eurostile"
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top :parent.top
    }
    Text {
        id: aux
        text:(Dashboard.BatteryV).toFixed(2)
        font.pixelSize: (parent.width / 10)
        font.bold: true
        font.family: "Eurostile"
        color: "white"
        anchors.top : afrtext.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }



    Text {
        id:boost
        text:"Boost"
        font.pixelSize: (parent.width / 10)
         y: parent.height / 6
        font.bold: true
        font.family: "Eurostile"
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top : aux.bottom
    }
    Text {
        id: pimval
        text: (Dashboard.pim).toFixed(2)
        font.pixelSize: (parent.width / 10)
         y: parent.height / 6
        font.bold: true
        font.family: "Eurostile"
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top : boost.bottom
    }
    Text {
        id: knock
        text:"Knock"
        font.pixelSize: (parent.width / 10)
         y: parent.height / 6
        font.bold: true
        font.family: "Eurostile"
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top : pimval.bottom
    }
    Text {
        text: Dashboard.Knock
        font.pixelSize: (parent.width / 10)
         y: parent.height / 6
        font.bold: true
        font.family: "Eurostile"
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top : knock.bottom
    }
}
    Rectangle {
        id : intaketemp
        width: parent.width /6
        height: parent.height /2
        color: "transparent"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top :displaybox.bottom
/*
        Timer {
            running: true
            repeat: true
            interval: 2000
            onTriggered: gauge.value = gauge.value == gauge.maximumValue ? 5 : gauge.maximumValue
        }
*/
        Gauge {
            anchors.fill: parent
            anchors.margins: 10
            orientation : Qt.Horizontal
            minorTickmarkCount: 3
            tickmarkStepSize : 40
            //labelStepSize: 50
            minimumValue: 0
            maximumValue: 80

            value: Dashboard.Intaketemp
            Behavior on value {
                NumberAnimation {
                    duration: 5
                }
            }
            Text {
                text:"Intake " + Dashboard.Intaketemp + "°C "
                font.pixelSize: (parent.width / 14)
                 y: (parent.heigth / 22)
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
              style: GaugeStyle {
                valueBar: Rectangle {
                   implicitWidth: 20

                    color: Qt.rgba(gauge.value / gauge.maximumValue, 0, 1 - gauge.value / gauge.maximumValue, 1)
                }
            }
      }
    }
    Rectangle {
        width: parent.width /8
        height: width
        color: "transparent"
        anchors.centerIn: parent


    }


    Rectangle {
        CircularGauge {
            id: speedometer
            height: parent.height
            width: height
            value: Dashboard.speed
            anchors.verticalCenter: parent.verticalCenter
            maximumValue: 320

            style: DashboardGaugeStyle {}
        }
        color: "transparent"
        id: speedo
        height: parent.height / 1.5
        width: height

        x: 20
        y: (parent.height / 5)

        GaugeNeedle {
            id: speedoNeedle

                 anchors.verticalCenterOffset: 0
                 anchors.centerIn: parent
                 value: Dashboard.speed / 4.155844155844156

}


        SpeedGaugeInnerRing   {
            id: innerring
            speed: Dashboard.speed
        }
    }


     Rectangle {
         CircularGauge {
             id: tachometer
             height: parent.height
             width: height
             value: Dashboard.revs / 1000
             maximumValue: 10
             anchors.centerIn: parent

             style: TachometerStyle {}
         }

        color: "transparent"
        height: parent.height / 1.5
        width: height
        y: (parent.height / 5)
        x: ((parent.width - parent.height / 1.5 )-20)
        // anchors.right:parent.right

        GaugeNeedle {
            id: revNeedle
            anchors.verticalCenterOffset: 0
            anchors.centerIn: parent
            value: Dashboard.revs * 0.0077

        }
        RevGaugeInnerRing   {
            id: revinnerring
            revolutions: Dashboard.revs
        }
    }


}
