#ifndef DASHBOARD_H
#define DASHBOARD_H

#endif // DASHBOARD_H

#include <QObject>

class DashBoard : public QObject
{
    Q_OBJECT

    // Advanced Info FD3S
    Q_PROPERTY(qreal revs READ revs WRITE setRevs NOTIFY revsChanged)
    Q_PROPERTY(qreal Intakepress READ Intakepress WRITE setIntakepress NOTIFY IntakepressChanged)
    Q_PROPERTY(qreal PressureV READ PressureV WRITE setPressureV NOTIFY PressureVChanged)
    Q_PROPERTY(qreal ThrottleV READ ThrottleV WRITE setThrottleV NOTIFY ThrottleVChanged)
    Q_PROPERTY(qreal Primaryinp READ Primaryinp WRITE setPrimaryinp NOTIFY PrimaryinpChanged)
    Q_PROPERTY(qreal Fuelc READ Fuelc WRITE setFuelc NOTIFY FuelcChanged)
    Q_PROPERTY(qreal Leadingign READ Leadingign WRITE setLeadingign NOTIFY LeadingignChanged)
    Q_PROPERTY(qreal Trailingign READ Trailingign WRITE setTrailingign NOTIFY TrailingignChanged)
    Q_PROPERTY(qreal Fueltemp READ Fueltemp WRITE setFueltemp NOTIFY FueltempChanged)
    Q_PROPERTY(qreal Moilp READ Moilp WRITE setMoilp NOTIFY MoilpChanged)
    Q_PROPERTY(qreal Boosttp READ Boosttp WRITE setBoosttp NOTIFY BoosttpChanged)
    Q_PROPERTY(qreal Boostwg READ Boostwg WRITE setBoostwg NOTIFY BoostwgChanged)
    Q_PROPERTY(qreal Watertemp READ Watertemp WRITE setWatertemp NOTIFY WatertempChanged)
    Q_PROPERTY(qreal Intaketemp READ Intaketemp WRITE setIntaketemp NOTIFY IntaketempChanged)
    Q_PROPERTY(qreal Knock READ Knock WRITE setKnock NOTIFY KnockChanged)
    Q_PROPERTY(qreal BatteryV READ BatteryV WRITE setBatteryV NOTIFY BatteryVChanged)
    Q_PROPERTY(qreal speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(qreal Iscvduty READ Iscvduty WRITE setIscvduty NOTIFY IscvdutyChanged)
    Q_PROPERTY(qreal O2volt READ O2volt WRITE setO2volt NOTIFY O2voltChanged)
    Q_PROPERTY(qreal na1 READ na1 WRITE setna1 NOTIFY na1Changed)
    Q_PROPERTY(qreal Secinjpulse READ Secinjpulse WRITE setSecinjpulse NOTIFY SecinjpulseChanged)
    Q_PROPERTY(qreal na2 READ Intaketemp WRITE setna2 NOTIFY na2Changed)


//Sensor Info

    Q_PROPERTY(qreal pim READ pim WRITE setpim NOTIFY pimChanged)
    Q_PROPERTY(qreal vta1 READ vta1 WRITE setvta1 NOTIFY vta1Changed)
    Q_PROPERTY(qreal vta2 READ vta2 WRITE setvta2 NOTIFY vta2Changed)
    Q_PROPERTY(qreal vmop READ vmop WRITE setvmop NOTIFY vmopChanged)
    Q_PROPERTY(qreal wtrt READ wtrt WRITE setwtrt NOTIFY wtrtChanged)
    Q_PROPERTY(qreal airt READ airt WRITE setairt NOTIFY airtChanged)
    Q_PROPERTY(qreal fuelt READ fuelt WRITE setfuelt NOTIFY fueltChanged)
    Q_PROPERTY(qreal O2S READ O2S WRITE setO2S NOTIFY O2SChanged)

    Q_PROPERTY(qreal Flag1 READ Flag1 WRITE setFlag1 NOTIFY Flag1Changed)
    Q_PROPERTY(qreal Flag2 READ Flag2 WRITE setFlag1 NOTIFY Flag2Changed)
    Q_PROPERTY(qreal Flag3 READ Flag3 WRITE setFlag1 NOTIFY Flag3Changed)
    Q_PROPERTY(qreal Flag4 READ Flag4 WRITE setFlag1 NOTIFY Flag4Changed)
    Q_PROPERTY(qreal Flag5 READ Flag5 WRITE setFlag1 NOTIFY Flag5Changed)
    Q_PROPERTY(qreal Flag6 READ Flag6 WRITE setFlag1 NOTIFY Flag6Changed)
    Q_PROPERTY(qreal Flag7 READ Flag7 WRITE setFlag1 NOTIFY Flag7Changed)
    Q_PROPERTY(qreal Flag8 READ Flag8 WRITE setFlag1 NOTIFY Flag8Changed)
    Q_PROPERTY(qreal Flag9 READ Flag9 WRITE setFlag1 NOTIFY Flag9Changed)
    Q_PROPERTY(qreal Flag10 READ Flag10 WRITE setFlag1 NOTIFY Flag10Changed)
    Q_PROPERTY(qreal Flag11 READ Flag11 WRITE setFlag1 NOTIFY Flag11Changed)
    Q_PROPERTY(qreal Flag12 READ Flag12 WRITE setFlag1 NOTIFY Flag12Changed)
    Q_PROPERTY(qreal Flag13 READ Flag13 WRITE setFlag1 NOTIFY Flag13Changed)
    Q_PROPERTY(qreal Flag14 READ Flag14 WRITE setFlag1 NOTIFY Flag14Changed)
    Q_PROPERTY(qreal Flag15 READ Flag15 WRITE setFlag1 NOTIFY Flag15Changed)
    Q_PROPERTY(qreal Flag16 READ Flag16 WRITE setFlag1 NOTIFY Flag16Changed)


public:
    DashBoard(QObject *parent = 0);
    // Advanced Info FD3S
    void setRevs(const qreal &revs);
    void setIntakepress(const qreal &Intakepress);
    void setPressureV(const qreal &PressureV);
    void setThrottleV(const qreal &ThrottleV);
    void setPrimaryinp(const qreal &Primaryinp);
    void setFuelc(const qreal &Fuelc);
    void setLeadingign(const qreal &Leadingign);
    void setTrailingign(const qreal &Trailingign);
    void setFueltemp(const qreal &Fueltemp);
    void setMoilp(const qreal &Moilp);
    void setBoosttp(const qreal &Boosttp);
    void setBoostwg(const qreal &Boostwg);
    void setWatertemp(const qreal &Watertemp);
    void setIntaketemp(const qreal &Intaketemp);
    void setKnock(const qreal &Knock);
    void setBatteryV(const qreal &BatteryV);
    void setSpeed(const qreal &speed);
    void setIscvduty (const qreal &Iscvduty );
    void setO2volt(const qreal &O2volt);
    void setna1(const qreal &na1);
    void setSecinjpulse(const qreal &Secinjpulse);
    void setna2(const qreal &na2);

    //Sensor Info
    void setpim(const qreal &pim);
    void setvta1(const qreal &vta1);
    void setvta2(const qreal &vta2);
    void setvmop(const qreal &vmop);
    void setwtrt(const qreal &wtrt);
    void setairt(const qreal &airt);
    void setfuelt(const qreal &fuelt);
    void setO2S(const qreal &O2S);

    //Flags

    void setFlag1(const qreal &Flag1);
    void setFlag2(const qreal &Flag2);
    void setFlag3(const qreal &Flag3);
    void setFlag4(const qreal &Flag4);
    void setFlag5(const qreal &Flag5);
    void setFlag6(const qreal &Flag6);
    void setFlag7(const qreal &Flag7);
    void setFlag8(const qreal &Flag8);
    void setFlag9(const qreal &Flag9);
    void setFlag10(const qreal &Flag10);
    void setFlag11(const qreal &Flag11);
    void setFlag12(const qreal &Flag12);
    void setFlag13(const qreal &Flag13);
    void setFlag14(const qreal &Flag14);
    void setFlag15(const qreal &Flag15);
    void setFlag16(const qreal &Flag16);

    // Advanced Info FD3S
    qreal revs() const;
    qreal Intakepress() const;
    qreal PressureV() const;
    qreal ThrottleV() const;
    qreal Primaryinp() const;
    qreal Fuelc() const;
    qreal Leadingign() const;
    qreal Trailingign() const;
    qreal Fueltemp() const;
    qreal Moilp() const;
    qreal Boosttp() const;
    qreal Boostwg() const;
    qreal Watertemp() const;
    qreal Intaketemp() const;
    qreal Knock() const;
    qreal speed() const;
    qreal BatteryV() const;
    qreal Iscvduty() const;
    qreal O2volt() const;
    qreal na1() const;
    qreal Secinjpulse() const;
    qreal na2() const;

    //Sensor info

    qreal pim() const;
    qreal vta1() const;
    qreal vta2() const;
    qreal vmop() const;
    qreal wtrt() const;
    qreal airt() const;
    qreal fuelt() const;
    qreal O2S() const;

    //Flags

    qreal Flag1() const;
    qreal Flag2() const;
    qreal Flag3() const;
    qreal Flag4() const;
    qreal Flag5() const;
    qreal Flag6() const;
    qreal Flag7() const;
    qreal Flag8() const;
    qreal Flag9() const;
    qreal Flag10() const;
    qreal Flag11() const;
    qreal Flag12() const;
    qreal Flag13() const;
    qreal Flag14() const;
    qreal Flag15() const;
    qreal Flag16() const;

signals:

    // Advanced Info FD3S
    void revsChanged(qreal revs);
    void IntakepressChanged(qreal Intakepress);
    void PressureVChanged(qreal PressureV);
    void ThrottleVChanged(qreal ThrottleV);
    void PrimaryinpChanged(qreal Primaryinp);
    void FuelcChanged(qreal Fuelc);
    void LeadingignChanged(qreal Leadingign);
    void TrailingignChanged(qreal Trailingign);
    void FueltempChanged(qreal Fueltemp);
    void MoilpChanged(qreal Moilp);
    void BoosttpChanged(qreal Boosttp);
    void BoostwgChanged(qreal Boostwg);
    void WatertempChanged(qreal Watertemp);
    void IntaketempChanged(qreal Intaketemp);
    void KnockChanged(qreal Knock);
    void speedChanged(qreal speed);
    void BatteryVChanged(qreal BatteryV);
    void IscvdutyChanged(qreal Iscvduty);
    void O2voltChanged(qreal O2volt);
    void na1Changed(qreal na1);
    void SecinjpulseChanged(qreal Secinjpulse);
    void na2Changed(qreal na2);

    //Sensor info

    void pimChanged(qreal pim);
    void vta1Changed(qreal vta1);
    void vta2Changed(qreal vta2);
    void vmopChanged(qreal vmop);
    void wtrtChanged(qreal wtrt);
    void airtChanged(qreal airt);
    void fueltChanged(qreal fuelt);
    void O2SChanged(qreal O2S);

    //Flags

    void Flag1Changed(qreal Flag1);
    void Flag2Changed(qreal Flag2);
    void Flag3Changed(qreal Flag3);
    void Flag4Changed(qreal Flag4);
    void Flag5Changed(qreal Flag5);
    void Flag6Changed(qreal Flag6);
    void Flag7Changed(qreal Flag7);
    void Flag8Changed(qreal Flag8);
    void Flag9Changed(qreal Flag9);
    void Flag10Changed(qreal Flag10);
    void Flag11Changed(qreal Flag11);
    void Flag12Changed(qreal Flag12);
    void Flag13Changed(qreal Flag13);
    void Flag14Changed(qreal Flag14);
    void Flag15Changed(qreal Flag15);
    void Flag16Changed(qreal Flag16);


private:
    // Advanced Info FD3S
    qreal m_revs;
    qreal m_Intakepress;
    qreal m_PressureV;
    qreal m_ThrottleV;
    qreal m_Primaryinp;
    qreal m_Fuelc;
    qreal m_Leadingign;
    qreal m_Trailingign;
    qreal m_Fueltemp;
    qreal m_Moilp;
    qreal m_Boosttp;
    qreal m_Boostwg;
    qreal m_Watertemp;
    qreal m_Intaketemp;
    qreal m_Knock;
    qreal m_speed;
    qreal m_BatteryV;
    qreal m_Iscvduty;
    qreal m_O2volt;
    qreal m_na1;
    qreal m_Secinjpulse;
    qreal m_na2;

    //Sensor info

    qreal m_pim;
    qreal m_vta1;
    qreal m_vta2;
    qreal m_vmop;
    qreal m_wtrt;
    qreal m_airt;
    qreal m_fuelt;
    qreal m_O2S;

    //Flags

    qreal m_Flag1;
    qreal m_Flag2;
    qreal m_Flag3;
    qreal m_Flag4;
    qreal m_Flag5;
    qreal m_Flag6;
    qreal m_Flag7;
    qreal m_Flag8;
    qreal m_Flag9;
    qreal m_Flag10;
    qreal m_Flag11;
    qreal m_Flag12;
    qreal m_Flag13;
    qreal m_Flag14;
    qreal m_Flag15;
    qreal m_Flag16;

};
