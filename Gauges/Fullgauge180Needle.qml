import QtQuick 2.8
import QtGraphicalEffects 1.0
// Needle movement from -90 to +90 degrees 180 degree total
Canvas {
    id: canvas

    property real value : 0


    onValueChanged: {zeiger.rotation = Math.min(Math.max(-90, canvas.value*3.5 - 90), 90); canvas.currentValue = zeiger.rotation - 90} //130 minrotation, -30 maxrotation
    width: parent.width;
    height: parent.height

    Rectangle {
        id: zeiger
        rotation: -90 //siehe minrotation
        width: parent.width / 90
        height: parent.width / 2.08
        transformOrigin: Item.Bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.verticalCenter

        smooth: true
        antialiasing: true
        color: "white"
        onRotationChanged: {canvas.currentValue = zeiger.rotation - 90; canvas.requestPaint()}//texti.text = zeiger.rotation

            Behavior on rotation {
                NumberAnimation{
                    duration: 5
                    easing.type: Easing.OutCirc
                }
            }
    }


      antialiasing: true

      property color secondaryColor: zeiger.color

      property real centerWidth: width / 2
      property real centerHeight: height / 2
      property real radius: Math.min(canvas.width, canvas.height) / 2.08

      property real minimumValue: -180
      property real maximumValue: 0
      property real currentValue: -180

      // this is the angle that splits the circle in two arcs
      // first arc is drawn from 0 radians to angle radians
      // second arc is angle radians to 2*PI radians
      property real angle:(currentValue - minimumValue) / (maximumValue - minimumValue) * 2 * Math.PI /2
      property real angleOffset: 3.14


      onPaint: {
          var ctx = getContext("2d");
          ctx.save();

          var gradient2 = ctx.createRadialGradient((parent.width / 2),(parent.height / 2), 0, (parent.width / 2),(parent.height / 2),parent.height );
          gradient2.addColorStop(0.5, "#81FFFE");   //oben
          gradient2.addColorStop(0.46, "#81FFFE");   //oben
          gradient2.addColorStop(0.45, "#112478");   //mitte
          gradient2.addColorStop(0.33, "transparent");   //unten


          ctx.clearRect(0, 0, canvas.width, canvas.height);

          ctx.beginPath();
          ctx.lineWidth = 150;
          ctx.strokeStyle = gradient2
          ctx.arc(canvas.centerWidth, canvas.centerHeight, canvas.radius - (ctx.lineWidth / 2), canvas.angleOffset, canvas.angleOffset + canvas.angle);
          ctx.stroke();

          ctx.restore();
      }
}

