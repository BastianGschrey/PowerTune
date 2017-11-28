import QtQuick 2.8
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
            Text { text: "Dash 1"; width: 200}
            ComboBox {
                id: dash1
                width: 200
                model: ["SensorCheck", "Adaptronic" ]
                property bool initialized: true
                onCurrentIndexChanged:{select1.selDash1() }
                Component.onCompleted: {select1.selDash1() }
                //  onCurrentIndexChanged: if (initialized) AppSettings.setBaudRate( currentIndex )
                //   Component.onCompleted: { currentIndex = AppSettings.getBaudRate(); initialized = true }
            }
        }
    }

    Item {
        id: select1
        function selDash1()
        {
            console.log (dash1.currentIndex);
            if (dash1.currentIndex == "0") {firstPageLoader.source = "qrc:/Gauges/PFCSensors.qml"};
            if (dash1.currentIndex == "1") firstPageLoader.source = "qrc:/Gauges/DashAdaptronic.qml";
        }

    }
}
