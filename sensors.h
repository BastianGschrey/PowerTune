#ifndef SENSORS_H
#define SENSORS_H

#include <QObject>
#include <QAccelerometer>
#include <QGyroscope>
#include <QCompass>
#include <QAmbientTemperatureSensor>
#include <QPressureSensor>

class Sensors;
class DashBoard;

class Sensors : public QObject
{
    Q_OBJECT

public:


    explicit Sensors(QObject *parent = 0);
    explicit Sensors(DashBoard *dashboard, QObject *parent = 0);
    Q_INVOKABLE void Comp();
    Q_INVOKABLE void Accel();
    Q_INVOKABLE void Gyro();
    Q_INVOKABLE void Temperature();
    Q_INVOKABLE void Pressure();


public slots:
    void updateCompass();
    void updateAccel();
    void updateGyro();
    void updateAmbientSens();
    void updatePressureSens();
    void error(int);

private:
    DashBoard *m_dashboard;

    QCompass *Compass;
    QAccelerometer *Accelerometer;
    QGyroscope *Gyroscope;
    QAmbientTemperatureSensor *AmbientTemperatureSensor;
    QPressureSensor *PressureSensor;
    QCompassReading *compass_reading;
    QAccelerometerReading *accel_reading;
    QGyroscopeReading *gyro_reading;
    QAmbientTemperatureReading *temp_reading;
    QPressureReading *press_reading;




};

#endif // SENSORS_H
