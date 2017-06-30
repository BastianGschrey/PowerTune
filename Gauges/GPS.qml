import QtQuick 2.6
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0
import Qt.labs.settings 1.0


Rectangle {
    width: parent.width
    height: parent.height
    color: "grey"

        Grid {
            rows: 6
            columns: 2
            spacing: 5

            Text { text: "Time: " }
            Text { text: Dashboard.gpsTime}
            Text { text: "Speed: " }
            Text { text: Dashboard.gpsSpeed }
            Text { text: "Altitude: " }
            Text { text: Dashboard.gpsAltitude }
            Text { text: "Latitude: " }
            Text { text: Dashboard.gpsLatitude }
            Text { text: "Longitude: " }
            Text { text: Dashboard.gpsLongitude }
            Text { text: "Visible Satelites: " }
            Text { text: Dashboard.gpsVisibleSatelites }



}
}

