import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    visible: true
    width: 200
    height: 200

    ComboBox {
        width: 200
        editable: false
        id:portsel
        model: ["test", "test1"]
        }

}
