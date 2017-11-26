import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtCharts 2.0




Rectangle {
    width: parent.width
    height: parent.height
    color: "black"

    Image {
         id: backround
         width: 800; height: 480
         fillMode: Image.PreserveAspectFit
         source: "/graphics/MainDash.png"
    }



    Rectangle {
        width: parent.width /6
        height: parent.height /2
        color: "transparent"
        anchors.horizontalCenter: parent.horizontalCenter
        y :parent.height /4

    }

    Rectangle {


      color: "transparent"
        id: speedo
        height: 240
        width: height
        x: 110
        y: 125

        GaugeNeedle_minus180to90  {
            id: speedoNeedle

                 anchors.verticalCenterOffset: 0
                 anchors.centerIn: parent
                 value: Dashboard.speed / 4.155844155844156

}


        Rectangle {


          color: "transparent"
            id: revcounter
            height: 240
            width: height
            x: 345
            y: 0

            GaugeNeedle_minus90to180  {
                id: revneedele

                     anchors.verticalCenterOffset: 0
                     anchors.centerIn: parent
                     value: Dashboard.revs *0.0077

    }
    }



}
}
