import QtQuick 2.7
import QtQuick.Controls 2.1

Rectangle {
    width: parent.width
    height: parent.height
    color: "grey"
Item {
    Row {
        x: 5
        y: 5
        spacing: 5
        Grid {
            rows: 10
            columns: 2
            spacing: 5
Text { text: "Unit Display"; width: 200}
ComboBox {
    id: unitSetting
    width: 200
    model: [
        "Metric", "Imperial" ]
    property bool initialized: false
  //  onCurrentIndexChanged: if (initialized) AppSettings.setUnits( currentIndex )
 //   Component.onCompleted: { currentIndex = AppSettings.getUnits(); initialized = true }
        }

TextField {
    placeholderText: qsTr("Value @ 0V")
}

        }
    }
}
}
