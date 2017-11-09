import QtQuick 2.8
import QtGraphicalEffects 1.0

Canvas {
    id: revcanvas

    property int value : 0

    onValueChanged: {revzeiger.rotation = Math.min(Math.max(-250, revcanvas.value*3.5 - 150), 150); revcanvas.revcurrentValue = revzeiger.rotation - 210} //130 minrotation, -30 maxrotation
    width: parent.width; height: parent.height

    Rectangle {
        id: revzeiger
        rotation: -150 //begin of rotation
        width: 4
        height: parent.width / 2
        transformOrigin: Item.Bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.verticalCenter

        smooth: true
        antialiasing: true
        color: "#ffffff" // needle color
        onRotationChanged: {revcanvas.revcurrentValue = revzeiger.rotation - 210; revcanvas.requestPaint()}//texti.text = revzeiger.rotation

            Behavior on rotation {
                NumberAnimation{
                    duration: 30
                    easing.type: Easing.OutCirc
                }
            }
    }


      antialiasing: true

      property color secondaryColor: revzeiger.color

      property real centerWidth: width / 2
      property real centerHeight: height / 2
      property real radius: Math.min(revcanvas.width, revcanvas.height) / 2

      property real revminimumValue: -360
      property real revmaximumValue: 0
      property real revcurrentValue: -360

      // this is the angle that splits the circle in two arcs
      // first arc is drawn from 0 radians to angle radians
      // second arc is angle radians to 2*PI rad27
      property real angle: (revcurrentValue - revminimumValue) / (revmaximumValue - revminimumValue) * 2 * Math.PI //+ 0.01
      property real angleOffset: 20.955 //to start at 0mph //-Math.PI / 2


      onPaint: {
          var ctx = getContext("2d");
          ctx.save();

          var gradient2 = ctx.createRadialGradient((parent.width / 2),(parent.height / 2), 0, (parent.width / 2),(parent.height / 2),parent.height);
          gradient2.addColorStop(0.5, "#ffffff");   //outer needle ring color
          gradient2.addColorStop(0.46, "#e96448");   //middle needle ring color
          gradient2.addColorStop(0.45, "#f22900");   //inner needle ring color
          gradient2.addColorStop(0.33, "transparent");   //unten

          ctx.clearRect(0, 0, revcanvas.width, revcanvas.height);

          ctx.beginPath();
          ctx.lineWidth = (parent.width / 2) ;
          ctx.strokeStyle = gradient2
          ctx.arc(revcanvas.centerWidth, revcanvas.centerHeight, revcanvas.radius - (ctx.lineWidth / 2), revcanvas.angleOffset, revcanvas.angleOffset + revcanvas.angle);
          ctx.stroke();


          ctx.restore();
      }
}

