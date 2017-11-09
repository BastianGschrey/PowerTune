import QtQuick 2.8
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4




Rectangle {
    width: parent.width
    height: parent.height
    color: "black"
//Gauge 1 Left Top Water Temp

    Rectangle {
        CircularGauge {
            height: parent.height
            width: parent.width
            value: Dashboard.Watertemp
            anchors.verticalCenter: parent.verticalCenter
            anchors.top: parent.top
            minimumValue: 0
            maximumValue: 140

            style: HalfGaugeStyle {}
        }

        color: "transparent"

        height: parent.width / 3.7
        width: height
        x : parent.width /27
        y : parent.width /27

        Text {
            text: "°C"
            font.pixelSize: (parent.width / 12)
             y: (parent.width / 5)
            font.bold: true
            font.family: "Eurostile"
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            text: "COOLANT TEMP"
            font.pixelSize: (parent.width / 14)
             y: (parent.width / 2.4)
            font.bold: true
            font.family: "Eurostile"
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            id: coolant
            text: Math.round (Dashboard.Watertemp)
            font.pixelSize: (parent.width / 10)
            font.bold: true
            font.family: "Eurostile"
            y: (parent.width / 3.5)
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        DropShadow {
                anchors.fill: coolant
                horizontalOffset: 0
                verticalOffset: 8
                radius: 4.0
                samples: 16
                color: "black"
                source: coolant
            }
        HalfNeedle {
            id: waterneedle
            anchors.verticalCenterOffset: 0
            anchors.centerIn: parent
            value: Dashboard.Watertemp / 2.692307692307692


        }

    }
    //Gauge 2 Left bottom Intake Air Temp
        Rectangle {
            CircularGauge {
                height: parent.height
                width: parent.width
                value: Dashboard.Intaketemp
                anchors.verticalCenter: parent.verticalCenter
                anchors.top: parent.top
                minimumValue: 0
                maximumValue: 140

                style: HalfGaugeStyle {}
            }

            color: "transparent"

            height: parent.width / 3.7
            width: height
            x: parent.width /27
            y: parent.height /2
            Text {
                text: "°C"
                font.pixelSize: (parent.width / 12)
                 y: (parent.width / 5)
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {
                text: "INTAKE AIR TEMP"
                font.pixelSize: (parent.width / 14)
                 y: (parent.width / 2.4)
                font.bold: true
                font.family: "Eurostile"
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {
                id: air
                text: Math.round (Dashboard.Intaketemp)
                font.pixelSize: (parent.width / 10)
                font.bold: true
                font.family: "Eurostile"
                y: (parent.width / 3.5)
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }

            DropShadow {
                    anchors.fill: air
                    horizontalOffset: 0
                    verticalOffset: 8
                    radius: 4.0
                    samples: 16
                    color: "black"
                    source: air
                }
            HalfNeedle {
                anchors.verticalCenterOffset: 0
                anchors.centerIn: parent
                value: Dashboard.Intaketemp / 2.692307692307692


            }

        }
        //Gauge 3 top middle Boost Gauge
            Rectangle {
                CircularGauge {
                    height: parent.height
                    width: parent.width
                    value: Dashboard.pim
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.top: parent.top
                    minimumValue: 0
                    maximumValue: 1.5

                    style: HalfGaugeStyle {
                        labelStepSize: 0.5
                        tickmarkStepSize: 0.5

                    }
                }

                color: "transparent"

                height: parent.width / 3.7
                width: height
                x: parent.width /2.73
                y : parent.width /27

                Text {
                    text: "BOOST"
                    font.pixelSize: (parent.width / 12)
                     y: (parent.width / 5)
                    font.bold: true
                    font.family: "Eurostile"
                    color: "white"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    text: "mmHg / kg/cm²"
                    font.pixelSize: (parent.width / 14)
                     y: (parent.width / 2.4)
                    font.bold: true
                    font.family: "Eurostile"
                    color: "white"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Text {
                    //id: coolant
                    text: (Dashboard.pim).toFixed(2);
                    font.pixelSize: (parent.width / 10)
                    font.bold: true
                    font.family: "Eurostile"
                    y: (parent.width / 3.5)
                    color: "white"
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                DropShadow {
                      //  anchors.fill: coolant
                        horizontalOffset: 0
                        verticalOffset: 8
                        radius: 4.0
                        samples: 16
                        color: "black"
                        source: coolant
                    }

                HalfNeedle {
                    anchors.verticalCenterOffset: 0
                    anchors.centerIn: parent
                    value: Dashboard.pim / 0.0288461538461538
                }

            }
            //Gauge 4 bottom middle Injector Duty
                Rectangle {
                    CircularGauge {
                        height: parent.height
                        width: parent.width
                        value: Dashboard.Iscvduty
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.top: parent.top
                        minimumValue: 0
                        maximumValue: 100

                        style: HalfGaugeStyle {}
                    }

                    color: "transparent"

                    height: parent.width / 3.7
                    width: height
                    x: parent.width /2.73
                    y: parent.height /2

                    Text {
                        text: "%"
                        font.pixelSize: (parent.width / 12)
                         y: (parent.width / 5)
                        font.bold: true
                        font.family: "Eurostile"
                        color: "white"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        text: "INJECTOR DUTY"
                        font.pixelSize: (parent.width / 14)
                         y: (parent.width / 2.4)
                        font.bold: true
                        font.family: "Eurostile"
                        color: "white"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        id: injDuty
                        text: Dashboard.InjDuty
                        font.pixelSize: (parent.width / 10)
                        font.bold: true
                        font.family: "Eurostile"
                        y: (parent.width / 3.5)
                        color: "white"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    DropShadow {
                            anchors.fill: injDuty
                            horizontalOffset: 0
                            verticalOffset: 8
                            radius: 4.0
                            samples: 16
                            color: "black"
                            source: injDuty
                        }
                    HalfNeedle {
                        //id: waterneedle
                        anchors.verticalCenterOffset: 0
                        anchors.centerIn: parent
                        value: Dashboard.InjDuty /1.886792452830189


                    }


                }
                //Gauge 5 top right
                    Rectangle {
                        CircularGauge {
                            height: parent.height
                            width: parent.width
                            value: Dashboard.speed
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.top: parent.top
                            minimumValue: 0
                            maximumValue: 20

                            style: HalfGaugeStyle {}
                        }

                        color: "transparent"

                        height: parent.width / 3.7
                        width: height
                        x: parent.width /1.44
                        y : parent.width /27

                        Text {
                            text: "A/F"
                            font.pixelSize: (parent.width / 12)
                             y: (parent.width / 5)
                            font.bold: true
                            font.family: "Eurostile"
                            color: "white"
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                        Text {
                            text: "AIR FUEL RATIO"
                            font.pixelSize: (parent.width / 14)
                             y: (parent.width / 2.4)
                            font.bold: true
                            font.family: "Eurostile"
                            color: "white"
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                        Text {
                            //id: coolant
                            text: Dashboard.auxcalc1
                            font.pixelSize: (parent.width / 10)
                            font.bold: true
                            font.family: "Eurostile"
                            y: (parent.width / 3.5)
                            color: "white"
                            anchors.horizontalCenter: parent.horizontalCenter
                        }

                        DropShadow {
                              //  anchors.fill: coolant
                                horizontalOffset: 0
                                verticalOffset: 8
                                radius: 4.0
                                samples: 16
                                color: "black"
                                source: coolant
                            }
                        HalfNeedle {
                            //id: waterneedle
                            anchors.verticalCenterOffset: 0
                            anchors.centerIn: parent
                            value: Dashboard.auxcalc1 / 0.3846153846153846


                        }


                    }
                    //Gauge 6 bottom right Knock
                        Rectangle {
                            CircularGauge {
                                height: parent.height
                                width: parent.width
                                value: Dashboard.Knock
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.top: parent.top
                                minimumValue: 0
                                maximumValue: 140

                                style: HalfGaugeStyle {}
                            }

                            color: "transparent"

                            height: parent.width / 3.7
                            width: height
                            x: parent.width /1.44
                            y : parent.height /2
                       /*     Text {
                                text: "PSI"
                                font.pixelSize: (parent.width / 12)
                                 y: (parent.width / 5)
                                font.bold: true
                                font.family: "Eurostile"
                                color: "white"
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                            */
                            Text {
                                text: "KNOCK"
                                font.pixelSize: (parent.width / 14)
                                 y: (parent.width / 2.4)
                                font.bold: true
                                font.family: "Eurostile"
                                color: "white"
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                            Text {
                                //id: coolant
                                text: Dashboard.Knock
                                font.pixelSize: (parent.width / 10)
                                font.bold: true
                                font.family: "Eurostile"
                                y: (parent.width / 3.5)
                                color: "white"
                                anchors.horizontalCenter: parent.horizontalCenter
                            }

                            DropShadow {
                                  //  anchors.fill: coolant
                                    horizontalOffset: 0
                                    verticalOffset: 8
                                    radius: 4.0
                                    samples: 16
                                    color: "black"
                                    source: coolant
                                }
                            HalfNeedle {
                                //id: waterneedle
                                anchors.verticalCenterOffset: 0
                                anchors.centerIn: parent
                                value: Dashboard.Knock / 2.641509


                            }


                        }
}

