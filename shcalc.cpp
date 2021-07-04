#include "shcalc.h"
#include "math.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QSettings>



/*
Todo Calculate the resistance of R2 from the Voltage divider circuit
Vin = 5V
R1 = 1000 Ohm
Vout = Value we get from EX analog X channels

R2= (VOUT * R1)/(VIN - VOUT) .

Exalmple

R2EXAN0 =  (m_dashboard->EXAnalog0()*1000)/(5/m_dashboard->EXAnalog0());

With R2 Known we can use the Steinhart-Hart Formula to derive the Temperature of the NTC

*/

SHCalc::SHCalc()
{

}

float SHCalc::SteinHart(float R)
{
    //R (Ω)
    long double L1 = log(R1); //Logrythm of Resistance 1
    long double L2 = log(R2); //Logrythm of Resistance 2
    long double L3 = log(R3); //Logrythm of Resistance 3

    //Convert Temperature from CELCIUS to Kelvin and get factor
    long double Y1 = 1/(T1+273.15);
    long double Y2 = 1/(T2+273.15);
    long double Y3 = 1/(T3+273.15);

    //Coefficent of L and Y
    long double V2 = (Y2-Y1)/(L2-L1);
    long double V3 = (Y3-Y1)/(L3-L1);

    //Coefficent Calculations
    C = ((V3 - V2)/(L3-L2))*(pow((L1+L2+L2),-1));
    B = (V3-C*(pow(L1,2)+L1*L2+pow(L2,2)));
    A = Y1 -(B+pow(L1,2)*C)*L1;

    QString tempString = "";
    tempString.append(QString::number((double) A));

    QString tempString2 = "";
    tempString2.append(QString::number((double) B));

    QString tempString3 = "";
    tempString3.append(QString::number((double) C));

    qDebug() << "A == " << tempString;
    qDebug() << "B == " << tempString2;
    qDebug() << "C == " << tempString3;

    //Steinhart-Hart
    long double tempK = 1/(A+(B*log(R)) + C* pow(log(R),3));
    //Convert from Kelvin to CELCIUS
    return tempK-273.15;
}
/*
void SHCalc::setStein(long R1, long R2, long R3, long double T1, long double T2, long double T3)
{
    this->R1 = R1;
    this->R2 = R2;
    this->R3 = R3;
    this->T1 = T1;
    this->T2 = T2;
    this->T3 = T3;
}
*/
