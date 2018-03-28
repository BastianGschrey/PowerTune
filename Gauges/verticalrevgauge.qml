import QtQuick 2.8
import QtQuick.Extras 1.4
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4

Item {
    id: revgauge
    width: 800
    height: 200

         Gauge {
             id: gauge
             width: parent.width
             height: parent.height

             tickmarkStepSize: 0
             minorTickmarkCount: 0
             tickmarkAlignment: Qt.AlignBottom
             orientation: Qt.Horizontal

             value: 10000
             minimumValue: 0
             maximumValue: 10000

             Behavior on value {
                 NumberAnimation {
                     duration: 5
                 }
             }

             style: GaugeStyle {
                 valueBar: Rectangle {
                     width: 200
                     color: Qt.rgba(gauge.value / gauge.maximumValue, 0, 1 - gauge.value / gauge.maximumValue, 1)
                 }
             }

         }

         Image {
             height: parent.height
             width: parent.width
              source: "/graphics/vertrevcanvas.png"
         }

}
