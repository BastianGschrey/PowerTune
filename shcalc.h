#ifndef SHCALC_H
#define SHCALC_H


class SHCalc
{
public:
    SHCalc();
    long R1 = 2000;
    long R2 = 4000;
    long R3 = 7000;
    long double T1 = 5;
    long double T2 = 25;
    long double T3 = 45;

    long double A;
    long double B;
    long double C;

    float SteinHart(float R);
};

#endif // SHCALC_H
