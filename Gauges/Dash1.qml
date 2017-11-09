import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4




Rectangle {
    width: parent.width
    height: parent.height
    color: "black"


    Rectangle {
        width: parent.width /8
        height: width
        color: "transparent"
        anchors.centerIn: parent


    }

// Air Temperature Gauge
    Rectangle {
        CircularGauge {
            height: parent.height
            width: height
            value: Dashboard.Intaketemp
            anchors.verticalCenter: parent.verticalCenter
            minimumValue: 0
            maximumValue: 270

            style: DashboardGaugeStyle {}
        }
        color: "transparent"
        height: width
        width: parent.width / 3.1

        x: 0
        y: (parent.height / 5)

        GaugeNeedle {
                 anchors.verticalCenterOffset: 0
                 anchors.centerIn: parent
                 value: (Dashboard.Intaketemp * 1.8 +32)/3.6

}


            AirTempGaugeInnerRingF  {
            id: innerring
            revolutions: Math.round(Dashboard.Intaketemp * 1.8 +32)
        }
    }

    Rectangle {
        width: parent.width /8
        height: width
        color: "transparent"
        anchors.centerIn: parent


    }

// Water Temp Gauge
    Rectangle {
        CircularGauge {

            height: parent.height
            width: height
            value: (Dashboard.Watertemp * 1.8 +32)
            anchors.verticalCenter: parent.verticalCenter
            maximumValue: 270

            style: DashboardGaugeStyle {}
        }
        color: "transparent"

        height: width
        width: parent.width / 3.1

        anchors.right: parent.right
        y: (parent.height / 5)

        GaugeNeedle {

                 anchors.verticalCenterOffset: 0
                 anchors.centerIn: parent
                 value:(Dashboard.Watertemp * 1.8 +32) /3.6

}


        WaterGaugeInnerRingF  {
        revolutions: Math.round(Dashboard.Watertemp * 1.8 +32)
        }
    }

//Boost Gauge
    Rectangle {
        CircularGauge {
            height: parent.height
            width: height
            value: Dashboard.pim * 14.22334
            anchors.verticalCenter: parent.verticalCenter
            minimumValue: 0
            maximumValue: 30


            style: DashboardGaugeStyle {
                minimumValueAngle: -90
                maximumValueAngle: -180
                labelStepSize: 5}
        }

        color: "transparent"
        //id: boost
        height: width
        width: parent.width / 3.1

        anchors.horizontalCenter: parent.horizontalCenter
        y: (parent.height / 5)

        Fullgauge180Needle {
        //    id: speedoNeedle

                 anchors.verticalCenterOffset: 0
                 anchors.centerIn: parent
                 value: Dashboard.pim

}


            BoostGaugeInnerRing   {
            revolutions: Math.round(Dashboard.pim * 14.22334) //Dashboard.speed
       }
    }
}
