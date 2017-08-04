import QtQuick 2.6
import QtQuick.Extras 1.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4


Rectangle {
    width: parent.width
    height:parent.height
    color:"black"
    Gauge {
        id: gauge
        height: parent.height
        width: 780
        y:100
        minorTickmarkCount: 0
        tickmarkStepSize : 9000
        //labelStepSize: 9000
        orientation : Qt.Horizontal
        minimumValue: 0
        maximumValue: 9000

        value: Dashboard.revs
        Behavior on value {
            NumberAnimation {
                duration: 5
            }
        }
        style: GaugeStyle {
          valueBar: Rectangle {
             width:  400
              color: "yellow"
          }
    }
    }

    Image {
        height: parent.height
        width: parent.width
        source: "/graphics/Racedash800x480.png"

    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter

        spacing: 20
    StatusIndicator {
        color: "green"
        active: { (Dashboard.revs > "0") ? true: false; }
    }
    StatusIndicator {
        color: "green"
        active: { (Dashboard.revs > "2000") ? true: false; }
    }
    StatusIndicator {
        color: "yellow"
        active: { (Dashboard.revs > "5000") ? true: false; }
    }
    StatusIndicator {
        color: "yellow"
        active: { (Dashboard.revs > "6000") ? true: false; }
    }
    StatusIndicator {
        color: "red"
        active: { (Dashboard.revs > "8000") ? true: false; }
    }
    StatusIndicator {
        color: "red"
        active: { (Dashboard.revs > "8000") ? true: false; }
    }
    StatusIndicator {
        color: "yellow"
        active: { (Dashboard.revs > "6000") ? true: false; }
    }
    StatusIndicator {
        color: "yellow"
        active: { (Dashboard.revs > "5000") ? true: false; }
    }
    StatusIndicator {
        color: "green"
        active: { (Dashboard.revs > "2000") ? true: false; }
    }
    StatusIndicator {
        color: "green"
        active: { (Dashboard.revs > "0") ? true: false; }
    }
}
    Text {
        text: Dashboard.revs
        font.pixelSize: (parent.width / 25)
         y: 100
         x: 160
        font.bold: true
        font.family: "Eurostile"
        color: "black"

    }
    Text {
        text:" RPM "
        font.pixelSize: (parent.width / 25)
         y: 100
         x: 260
        font.bold: true
        font.family: "Eurostile"
        color: "black"

    }
    Text {
        text: Dashboard.speed
        font.pixelSize: (parent.width / 25)
         y: 100
         x: 520
        font.bold: true
        font.family: "Eurostile"
        color: "black"

    }
    Text {
        text:" KM/H "
        font.pixelSize: (parent.width / 25)
         y: 100
         x: 600
        font.bold: true
        font.family: "Eurostile"
        color: "black"

    }
}
