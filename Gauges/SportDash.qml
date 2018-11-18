import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
Item {
    anchors.fill:parent
    //Rectangle in which the rev counter resides
    Rectangle {
        color: "transparent"
        id: main
        height: parent.height / 1.2
        width: height
        anchors.centerIn: parent

        // Paint Tickmarks and Labels on the Rev counter
        CircularGauge {
            id: revcounter
            height: parent.height
            width: height
            value: Dashboard.rpm/1000
            anchors.verticalCenter: parent.verticalCenter
            maximumValue: 10

            style:NormalGaugeStyle{
                labelStepSize: 1
                labelInset: toPixels(0.21)
                minimumValueAngle: -180
                maximumValueAngle: 90
                innertext :Dashboard.speed
                tickmarkLabel:  Text {
                    font.pixelSize: styleData.value >= Dashboard.rpm/1000+0.5 || styleData.value <= Dashboard.rpm/1000-0.5  ?  revcounter.height /11 : (styleData.value-Dashboard.rpm/1000)+revcounter.height /7
                    text: styleData.value
                    font.bold : styleData.value >= Dashboard.rpm/1000+0.5 || styleData.value <= Dashboard.rpm/1000-0.5  ? false : true
                    color: styleData.value <= Dashboard.rpm/1000 ? "white" : "grey"
                    antialiasing: true
                }
                Canvas {
                    property int value: revcounter.value

                    anchors.fill: parent
                    onValueChanged: requestPaint()

                    function degreesToRadians(degrees) {
                      return degrees * (Math.PI / 180);
                    }

                    onPaint: {
                        var ctx = getContext("2d");
                        ctx.reset();
                        ctx.beginPath();
                        ctx.strokeStyle = "blue"
                        ctx.lineWidth = outerRadius
                        ctx.arc(outerRadius,
                              outerRadius,
                              outerRadius + ctx.lineWidth / 2,
                              degreesToRadians(valueToAngle(revcounter.maximumValue) - 90),
                              degreesToRadians(valueToAngle(revcounter.value + 1) - 90));
                        ctx.stroke();
                    }
                }
            }

        }

    }
}
