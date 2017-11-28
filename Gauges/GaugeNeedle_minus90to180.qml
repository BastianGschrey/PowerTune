/*
Gauge Needle that moves from -90 degrees to 270 degrees which pulls a red Tail 
modified code from 
https://github.com/alex-adam/Tesla 
*/
import QtQuick 2.8
import QtGraphicalEffects 1.0

Canvas {
    id: canvas

    property real value : 0


    onValueChanged: {zeiger.rotation = Math.min(Math.max(-250, canvas.value*3.5 - 90), 180); canvas.currentValue = zeiger.rotation -270} //130 minrotation, -30 maxrotation
    width: parent.width;
    height: parent.height

    Rectangle {
        id: zeiger
        rotation: -90 //siehe minrotation
        width: parent.width / 85
        height: parent.width / 2.2
        transformOrigin: Item.Bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.verticalCenter

        smooth: true
        antialiasing: true
        color: "white"
        onRotationChanged: {canvas.currentValue = zeiger.rotation -270; canvas.requestPaint()}

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

      property real minimumValue: -360
      property real maximumValue: 0
      property real currentValue: -360

      // this is the angle that splits the circle in two arcs
      // first arc is drawn from 0 radians to angle radians
      // second arc is angle radians to 2*PI radians
      property real angle:(currentValue - minimumValue) / (maximumValue - minimumValue) * 2 * Math.PI //-0.01 //5.05
      property real angleOffset: Math.PI  //to start at 0mph



      onPaint: {
          var ctx = getContext("2d");
          ctx.save();

          var gradient2 = ctx.createRadialGradient((parent.width / 2),(parent.height / 2), 0, (parent.width / 2),(parent.height / 2),parent.height );
          gradient2.addColorStop(0.5, "#ffffff");   //outer needle ring color
          gradient2.addColorStop(0.46, "#e96448");   //middle needle ring color
          gradient2.addColorStop(0.45, "#f22900");   //inner needle ring color
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
