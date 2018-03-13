import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtMultimedia 5.8


Item {
    id : cameraUI
    width: parent.width
    height: parent.height


    Camera
    {
       id:camera
       captureMode: Camera.CaptureVideo
       videoRecorder.audioSampleRate: 48000
       videoRecorder.audioBitRate: 96
       videoRecorder.audioChannels: 1
       videoRecorder.audioCodec: "audio/mpeg, mpegversion=(int)4"
       videoRecorder.outputLocation:""
       videoRecorder.frameRate: 30
       videoRecorder.videoCodec: "video/x-h264"
       videoRecorder.mediaContainer: "video/x-matroska"

       videoRecorder.onRecorderStateChanged: {
          if (camera.videoRecorder.recorderState == CameraRecorder.StartingStatus) {
              console.log("saved to: " + camera.videoRecorder.outputLocation)

          }

       }



    }

    Button {
        id: recordButton
        text: "Record"
        //visible: camera.videoRecorder.recorderStatus == CameraRecorder.LoadedStatus
        onClicked: Camera.videoRecorder.record(),console.log (Camera.videoRecorder.recorderStatus);
        anchors.right: parent.right
        anchors.top : parent.top
    }
    Button {
        id: stopButton
        text: "Stop"
       // visible: camera.videoRecorder.recorderStatus == CameraRecorder.RecordingStatus
        onClicked: camera.videoRecorder.stop()
        anchors.right: parent.right
        anchors.top : recordButton.bottom
    }

    VideoOutput {
        id: videoscreen
        source: camera
        focus : visible
        //anchors.fill: parent
        anchors.fill: parent;
        fillMode: VideoOutput.PreserveAspectFit
         autoOrientation:true;
//Overlay Video with various gauges that display live data from the Car
         Rectangle {
            id: gauges
            color: "transparent";
            //opacity: 0.3
            width: videoscreen.width;
            height: videoscreen.height / 3;
            anchors.bottom: videoscreen.bottom;

            Image {
                id: backround
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.horizontalCenter
                anchors.rightMargin: parent.width /20
                width: height
                height: gauges.height
                fillMode: Image.PreserveAspectFit
                source: "/graphics/Tacho_Mitte.png"
                CircularGauge {
                    id: speedometer
                    value: Dashboard.speed
                    //anchors.verticalCenter: parent.verticalCenter
                    //anchors.right: parent.horizontalCenter
                    width: height
                    height: parent.height /1.13
                    anchors.centerIn: backround
                    maximumValue: 300

                    style: DashboardGaugeStyle {
                        labelStepSize: 30
                        minimumValueAngle: -120
                        maximumValueAngle: 120
                        needleLength: toPixels(0.85)
                        needleBaseWidth: toPixels(0.08)
                        needleTipWidth: toPixels(0.03)
                    }
                }
        }
            Gauge {
                id: forcebargauge
                width: height /3
                height: gauges.height / 2
                anchors.right: parent.horizontalCenter
                anchors.rightMargin: parent.width /80
                anchors.verticalCenter: parent.verticalCenter
                minimumValue: -2
                maximumValue: 2
                tickmarkStepSize: 0


                value: 0


                style: GaugeStyle {
                    valueBar: Rectangle {
                        implicitWidth: forcebargauge.width /1.5
                        color: "green"
                    }
                }
                Text {
                    id: name1
                    text: qsTr("G")
                    anchors.top: forcebargauge.bottom
                    anchors.right:  forcebargauge.right
                }
            }

            Gauge {
                id: throttlebargauge
                width: height /3
                height: gauges.height / 2
                anchors.left: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
               // anchors.leftMargin: parent.width /80
                minimumValue: 0
                maximumValue: 100
                tickmarkStepSize: 0


                value: 50

                style: GaugeStyle {
                    valueBar: Rectangle {
                        implicitWidth: throttlebargauge.width /1.5
                        color: "green"
                    }
                }
                Text {
                    id: name
                    text: qsTr("THR")
                    anchors.top: throttlebargauge.bottom
                    anchors.right: throttlebargauge.right
                }
            }
            Image {
                id: backroundrev
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.horizontalCenter
                anchors.leftMargin: parent.width /20
                width: height
                height: gauges.height
                fillMode: Image.PreserveAspectFit
                source: "/graphics/Tacho_Mitte.png"
                CircularGauge {
                    id: revcounter
                    value: Dashboard.revs /1000
                    anchors.centerIn: backroundrev
                    width: height
                    height: parent.height /1.13
                    maximumValue: 9
                    style: TachometerStyle {
                        minimumValueAngle: -120
                        maximumValueAngle: 120
                        needleLength: toPixels(0.85)
                        needleBaseWidth: toPixels(0.08)
                        needleTipWidth: toPixels(0.03)
                    }
                }

        }


//Gauge End

        }
    }
}
