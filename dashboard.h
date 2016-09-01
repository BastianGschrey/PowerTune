#ifndef DASHBOARD_H
#define DASHBOARD_H

#endif // DASHBOARD_H

#include <QObject>

class DashBoard : public QObject
{
    Q_OBJECT

    // Advanced Info FD3S
    Q_PROPERTY(qint16 revs READ revs WRITE setRevs NOTIFY revsChanged)
    Q_PROPERTY(qint16 Intakepress READ Intakepress WRITE setIntakepress NOTIFY IntakepressChanged)
    Q_PROPERTY(qint16 PressureV READ PressureV WRITE setPressureV NOTIFY PressureVChanged)
    Q_PROPERTY(qint16 ThrottleV READ ThrottleV WRITE setThrottleV NOTIFY ThrottleVChanged)
    Q_PROPERTY(qint16 Primaryinp READ Primaryinp WRITE setPrimaryinp NOTIFY PrimaryinpChanged)
    Q_PROPERTY(qint16 Fuelc READ Fuelc WRITE setFuelc NOTIFY FuelcChanged)
    Q_PROPERTY(qint16 Leadingign READ Leadingign WRITE setLeadingign NOTIFY LeadingignChanged)
    Q_PROPERTY(qint16 Trailingign READ Trailingign WRITE setTrailingign NOTIFY TrailingignChanged)
    Q_PROPERTY(qint16 Fueltemp READ Fueltemp WRITE setFueltemp NOTIFY FueltempChanged)
    Q_PROPERTY(qint16 Moilp READ Moilp WRITE setMoilp NOTIFY MoilpChanged)
    Q_PROPERTY(qint16 Boosttp READ Boosttp WRITE setBoosttp NOTIFY BoosttpChanged)
    Q_PROPERTY(qint16 Boostwg READ Boostwg WRITE setBoostwg NOTIFY BoostwgChanged)
    Q_PROPERTY(qint16 Watertemp READ Watertemp WRITE setWatertemp NOTIFY WatertempChanged)
    Q_PROPERTY(qint16 Intaketemp READ Intaketemp WRITE setIntaketemp NOTIFY IntaketempChanged)
    Q_PROPERTY(qint16 Knock READ Knock WRITE setKnock NOTIFY KnockChanged)
    Q_PROPERTY(qint16 BatteryV READ BatteryV WRITE setBatteryV NOTIFY BatteryVChanged)
    Q_PROPERTY(qint16 speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(qint16 Iscvduty READ Iscvduty WRITE setIscvduty NOTIFY IscvdutyChanged)
    Q_PROPERTY(qint16 O2volt READ O2volt WRITE setO2volt NOTIFY O2voltChanged)
    Q_PROPERTY(qint16 na1 READ na1 WRITE setna1 NOTIFY na1Changed)
    Q_PROPERTY(qint16 Secinjpulse READ Secinjpulse WRITE setSecinjpulse NOTIFY SecinjpulseChanged)
    Q_PROPERTY(qint16 na2 READ Intaketemp WRITE setna2 NOTIFY na2Changed)


//Sensor Info

    Q_PROPERTY(qint16 pim READ pim WRITE setpim NOTIFY pimChanged)
    Q_PROPERTY(qint16 vta1 READ vta1 WRITE setvta1 NOTIFY vta1Changed)
    Q_PROPERTY(qint16 vta2 READ vta2 WRITE setvta2 NOTIFY vta2Changed)
    Q_PROPERTY(qint16 vmop READ vmop WRITE setvmop NOTIFY vmopChanged)
    Q_PROPERTY(qint16 wtrt READ wtrt WRITE setwtrt NOTIFY wtrtChanged)
    Q_PROPERTY(qint16 airt READ airt WRITE setairt NOTIFY airtChanged)
    Q_PROPERTY(qint16 fuelt READ fuelt WRITE setfuelt NOTIFY fueltChanged)
    Q_PROPERTY(qint16 O2S READ O2S WRITE setO2S NOTIFY O2SChanged)

    Q_PROPERTY(qint16 Flag1 READ Flag1 WRITE setFlag1 NOTIFY Flag1Changed)
    Q_PROPERTY(qint16 Flag2 READ Flag2 WRITE setFlag1 NOTIFY Flag2Changed)
    Q_PROPERTY(qint16 Flag3 READ Flag3 WRITE setFlag1 NOTIFY Flag3Changed)
    Q_PROPERTY(qint16 Flag4 READ Flag4 WRITE setFlag1 NOTIFY Flag4Changed)
    Q_PROPERTY(qint16 Flag5 READ Flag5 WRITE setFlag1 NOTIFY Flag5Changed)
    Q_PROPERTY(qint16 Flag6 READ Flag6 WRITE setFlag1 NOTIFY Flag6Changed)
    Q_PROPERTY(qint16 Flag7 READ Flag7 WRITE setFlag1 NOTIFY Flag7Changed)
    Q_PROPERTY(qint16 Flag8 READ Flag8 WRITE setFlag1 NOTIFY Flag8Changed)
    Q_PROPERTY(qint16 Flag9 READ Flag9 WRITE setFlag1 NOTIFY Flag9Changed)
    Q_PROPERTY(qint16 Flag10 READ Flag10 WRITE setFlag1 NOTIFY Flag10Changed)
    Q_PROPERTY(qint16 Flag11 READ Flag11 WRITE setFlag1 NOTIFY Flag11Changed)
    Q_PROPERTY(qint16 Flag12 READ Flag12 WRITE setFlag1 NOTIFY Flag12Changed)
    Q_PROPERTY(qint16 Flag13 READ Flag13 WRITE setFlag1 NOTIFY Flag13Changed)
    Q_PROPERTY(qint16 Flag14 READ Flag14 WRITE setFlag1 NOTIFY Flag14Changed)
    Q_PROPERTY(qint16 Flag15 READ Flag15 WRITE setFlag1 NOTIFY Flag15Changed)
    Q_PROPERTY(qint16 Flag16 READ Flag16 WRITE setFlag1 NOTIFY Flag16Changed)


public:
    DashBoard(QObject *parent = 0);
    // Advanced Info FD3S
    void setRevs(const qint16 &revs);
    void setIntakepress(const qint16 &Intakepress);
    void setPressureV(const qint16 &PressureV);
    void setThrottleV(const qint16 &ThrottleV);
    void setPrimaryinp(const qint16 &Primaryinp);
    void setFuelc(const qint16 &Fuelc);
    void setLeadingign(const qint16 &Leadingign);
    void setTrailingign(const qint16 &Trailingign);
    void setFueltemp(const qint16 &Fueltemp);
    void setMoilp(const qint16 &Moilp);
    void setBoosttp(const qint16 &Boosttp);
    void setBoostwg(const qint16 &Boostwg);
    void setWatertemp(const qint16 &Watertemp);
    void setIntaketemp(const qint16 &Intaketemp);
    void setKnock(const qint16 &Knock);
    void setBatteryV(const qint16 &BatteryV);
    void setSpeed(const qint16 &speed);   
    void setIscvduty (const qint16 &Iscvduty );
    void setO2volt(const qint16 &O2volt);
    void setna1(const qint16 &na1);
    void setSecinjpulse(const qint16 &Secinjpulse);
    void setna2(const qint16 &na2);

    //Sensor Info
    void setpim(const qint16 &pim);
    void setvta1(const qint16 &vta1);
    void setvta2(const qint16 &vta2);
    void setvmop(const qint16 &vmop);
    void setwtrt(const qint16 &wtrt);
    void setairt(const qint16 &airt);
    void setfuelt(const qint16 &fuelt);
    void setO2S(const qint16 &O2S);

    //Flags

    void setFlag1(const qint16 &Flag1);
    void setFlag2(const qint16 &Flag2);
    void setFlag3(const qint16 &Flag3);
    void setFlag4(const qint16 &Flag4);
    void setFlag5(const qint16 &Flag5);
    void setFlag6(const qint16 &Flag6);
    void setFlag7(const qint16 &Flag7);
    void setFlag8(const qint16 &Flag8);
    void setFlag9(const qint16 &Flag9);
    void setFlag10(const qint16 &Flag10);
    void setFlag11(const qint16 &Flag11);
    void setFlag12(const qint16 &Flag12);
    void setFlag13(const qint16 &Flag13);
    void setFlag14(const qint16 &Flag14);
    void setFlag15(const qint16 &Flag15);
    void setFlag16(const qint16 &Flag16);

    // Advanced Info FD3S
    qint16 revs() const;
    qint16 Intakepress() const;
    qint16 PressureV() const;
    qint16 ThrottleV() const;
    qint16 Primaryinp() const;
    qint16 Fuelc() const;
    qint16 Leadingign() const;
    qint16 Trailingign() const;
    qint16 Fueltemp() const;
    qint16 Moilp() const;
    qint16 Boosttp() const;
    qint16 Boostwg() const;
    qint16 Watertemp() const;
    qint16 Intaketemp() const;
    qint16 Knock() const;
    qint16 speed() const;
    qint16 BatteryV() const;
    qint16 Iscvduty() const;
    qint16 O2volt() const;
    qint16 na1() const;
    qint16 Secinjpulse() const;
    qint16 na2() const;

    //Sensor info

    qint16 pim() const;
    qint16 vta1() const;
    qint16 vta2() const;
    qint16 vmop() const;
    qint16 wtrt() const;
    qint16 airt() const;
    qint16 fuelt() const;
    qint16 O2S() const;

    //Flags

    qint16 Flag1() const;
    qint16 Flag2() const;
    qint16 Flag3() const;
    qint16 Flag4() const;
    qint16 Flag5() const;
    qint16 Flag6() const;
    qint16 Flag7() const;
    qint16 Flag8() const;
    qint16 Flag9() const;
    qint16 Flag10() const;
    qint16 Flag11() const;
    qint16 Flag12() const;
    qint16 Flag13() const;
    qint16 Flag14() const;
    qint16 Flag15() const;
    qint16 Flag16() const;

signals:

    // Advanced Info FD3S
    void revsChanged(qint16 revs);
    void IntakepressChanged(qint16 Intakepress);
    void PressureVChanged(qint16 PressureV);
    void ThrottleVChanged(qint16 ThrottleV);
    void PrimaryinpChanged(qint16 Primaryinp);
    void FuelcChanged(qint16 Fuelc);
    void LeadingignChanged(qint16 Leadingign);
    void TrailingignChanged(qint16 Trailingign);
    void FueltempChanged(qint16 Fueltemp);
    void MoilpChanged(qint16 Moilp);
    void BoosttpChanged(qint16 Boosttp);
    void BoostwgChanged(qint16 Boostwg);
    void WatertempChanged(qint16 Watertemp);
    void IntaketempChanged(qint16 Intaketemp);
    void KnockChanged(qint16 Knock);
    void speedChanged(qint16 speed);
    void BatteryVChanged(qint16 BatteryV);
    void IscvdutyChanged(qint16 Iscvduty);
    void O2voltChanged(qint16 O2volt);
    void na1Changed(qint16 na1);
    void SecinjpulseChanged(qint16 Secinjpulse);
    void na2Changed(qint16 na2);

    //Sensor info

    void pimChanged(qint16 pim);
    void vta1Changed(qint16 vta1);
    void vta2Changed(qint16 vta2);
    void vmopChanged(qint16 vmop);
    void wtrtChanged(qint16 wtrt);
    void airtChanged(qint16 airt);
    void fueltChanged(qint16 fuelt);
    void O2SChanged(qint16 O2S);

    //Flags

    void Flag1Changed(qint16 Flag1);
    void Flag2Changed(qint16 Flag2);
    void Flag3Changed(qint16 Flag3);
    void Flag4Changed(qint16 Flag4);
    void Flag5Changed(qint16 Flag5);
    void Flag6Changed(qint16 Flag6);
    void Flag7Changed(qint16 Flag7);
    void Flag8Changed(qint16 Flag8);
    void Flag9Changed(qint16 Flag9);
    void Flag10Changed(qint16 Flag10);
    void Flag11Changed(qint16 Flag11);
    void Flag12Changed(qint16 Flag12);
    void Flag13Changed(qint16 Flag13);
    void Flag14Changed(qint16 Flag14);
    void Flag15Changed(qint16 Flag15);
    void Flag16Changed(qint16 Flag16);


private:
    // Advanced Info FD3S
    qint16 m_revs;
    qint16 m_Intakepress;
    qint16 m_PressureV;
    qint16 m_ThrottleV;
    qint16 m_Primaryinp;
    qint16 m_Fuelc;
    qint16 m_Leadingign;
    qint16 m_Trailingign;
    qint16 m_Fueltemp;
    qint16 m_Moilp;
    qint16 m_Boosttp;
    qint16 m_Boostwg;
    qint16 m_Watertemp;
    qint16 m_Intaketemp;
    qint16 m_Knock;
    qint16 m_speed;
    qint16 m_BatteryV;
    qint16 m_Iscvduty;
    qint16 m_O2volt;
    qint16 m_na1;
    qint16 m_Secinjpulse;
    qint16 m_na2;

    //Sensor info

    qint16 m_pim;
    qint16 m_vta1;
    qint16 m_vta2;
    qint16 m_vmop;
    qint16 m_wtrt;
    qint16 m_airt;
    qint16 m_fuelt;
    qint16 m_O2S;

    //Flags

    qint16 m_Flag1;
    qint16 m_Flag2;
    qint16 m_Flag3;
    qint16 m_Flag4;
    qint16 m_Flag5;
    qint16 m_Flag6;
    qint16 m_Flag7;
    qint16 m_Flag8;
    qint16 m_Flag9;
    qint16 m_Flag10;
    qint16 m_Flag11;
    qint16 m_Flag12;
    qint16 m_Flag13;
    qint16 m_Flag14;
    qint16 m_Flag15;
    qint16 m_Flag16;

};
