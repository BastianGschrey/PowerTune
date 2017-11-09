import QtQuick 2.8
import QtQuick.Controls 2.1
import QtGraphicalEffects 1.0
import Qt.labs.settings 1.0


Rectangle {
    id: gpswindow
    width: parent.width
    height: parent.height
    color: "grey"

        Grid {
            rows: 6
            columns: 2
            spacing: 5

            Text { text: "Time: "
            font.pixelSize: gpswindow.width /20
            font.bold: true
            font.family: "Eurostile"
            }
            Text { text: Dashboard.gpsTime
                font.pixelSize: gpswindow.width /20
                font.bold: true
                font.family: "Eurostile"
            }
            Text { text: "Speed: "
                font.pixelSize: gpswindow.width /20
                font.bold: true
                font.family: "Eurostile"}
            Text { text: Dashboard.gpsSpeed
                font.pixelSize: gpswindow.width /20
                font.bold: true
                font.family: "Eurostile"}
            Text { text: "Altitude: "
                font.pixelSize: gpswindow.width /20
                font.bold: true
                font.family: "Eurostile"}
            Text { text: Dashboard.gpsAltitude
                font.pixelSize: gpswindow.width /20
                font.bold: true
                font.family: "Eurostile"}
            Text { text: "Latitude: "
                font.pixelSize: gpswindow.width /20
                font.bold: true
                font.family: "Eurostile"}
            Text { text: Dashboard.gpsLatitude
                font.pixelSize: gpswindow.width /20
                font.bold: true
                font.family: "Eurostile"}
            Text { text: "Longitude: "
                font.pixelSize: gpswindow.width /20
                font.bold: true
                font.family: "Eurostile"}
            Text { text: Dashboard.gpsLongitude
                font.pixelSize: gpswindow.width /20
                font.bold: true
                font.family: "Eurostile"}
            Text { text: "Visible Satelites: "
                font.pixelSize: gpswindow.width /20
                font.bold: true
                font.family: "Eurostile"}
            Text { text: Dashboard.gpsVisibleSatelites
                font.pixelSize: gpswindow.width /20
                font.bold: true
                font.family: "Eurostile"}



}
}

