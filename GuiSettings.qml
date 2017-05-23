import QtQuick 2.7
import QtQuick.Controls 2.1

Item {
    Row {
        x: 5
        y: 5
        spacing: 5
        Grid {
            rows: 10
            columns: 2
            spacing: 5
Text { text: "Gauge 1"; width: 200}
ComboBox {
    id: gauge1
    width: 200
    model: [
        "HalfGaugeWaterDegC", "HalfGaugeWaterDegF" ]
    property bool initialized: false
  //  onCurrentIndexChanged: if (initialized) AppSettings.setBaudRate( currentIndex )
 //   Component.onCompleted: { currentIndex = AppSettings.getBaudRate(); initialized = true }
}
}
    }
}
