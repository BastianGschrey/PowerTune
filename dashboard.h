#ifndef DASHBOARD_H
#define DASHBOARD_H

#endif // DASHBOARD_H

#include <QObject>

class DashBoard : public QObject
{
    Q_OBJECT

    // Odometer
    Q_PROPERTY(qreal Odo READ Odo WRITE setOdo NOTIFY OdoChanged)

    // Advanced Info
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
    Q_PROPERTY(qreal InjDuty READ InjDuty WRITE setInjDuty NOTIFY InjDutyChanged)
    Q_PROPERTY(qreal pim READ pim WRITE setpim NOTIFY pimChanged)

    Q_PROPERTY(qreal EngLoad READ EngLoad WRITE setEngLoad NOTIFY EngLoadChanged)
    Q_PROPERTY(qreal MAF1V READ MAF1V WRITE setMAF1V NOTIFY MAF1VChanged)
    Q_PROPERTY(qreal MAF2V READ MAF2V WRITE setMAF2V NOTIFY MAF2VChanged)
    Q_PROPERTY(qreal injms READ injms WRITE setinjms NOTIFY injmsChanged)
    Q_PROPERTY(qreal Inj READ Inj WRITE setInj NOTIFY InjChanged)
    Q_PROPERTY(qreal Ign READ Ign WRITE setIgn NOTIFY IgnChanged)
    Q_PROPERTY(qreal Dwell READ Dwell WRITE setDwell NOTIFY DwellChanged)
    Q_PROPERTY(qreal BoostPres READ BoostPres WRITE setBoostPres NOTIFY BoostPresChanged)
    Q_PROPERTY(qreal BoostDuty READ BoostDuty WRITE setBoostDuty NOTIFY BoostDutyChanged)
    Q_PROPERTY(qreal MAFactivity READ MAFactivity WRITE setMAFactivity NOTIFY MAFactivityChanged)
    Q_PROPERTY(qreal O2volt_2 READ O2volt_2 WRITE setO2volt_2 NOTIFY O2volt_2Changed)

    // Sensor Voltage
    Q_PROPERTY(qreal sens1 READ sens1 WRITE setsens1 NOTIFY sens1Changed)
    Q_PROPERTY(qreal sens2 READ sens2 WRITE setsens2 NOTIFY sens2Changed)
    Q_PROPERTY(qreal sens3 READ sens3 WRITE setsens3 NOTIFY sens3Changed)
    Q_PROPERTY(qreal sens4 READ sens4 WRITE setsens4 NOTIFY sens4Changed)
    Q_PROPERTY(qreal sens5 READ sens5 WRITE setsens5 NOTIFY sens5Changed)
    Q_PROPERTY(qreal sens6 READ sens6 WRITE setsens6 NOTIFY sens6Changed)
    Q_PROPERTY(qreal sens7 READ sens7 WRITE setsens7 NOTIFY sens7Changed)
    Q_PROPERTY(qreal sens8 READ sens8 WRITE setsens8 NOTIFY sens8Changed)

    // Differential Aux Calculations
    Q_PROPERTY(qreal auxcalc1 READ auxcalc1 WRITE setauxcalc1 NOTIFY auxcalc1Changed)
    Q_PROPERTY(qreal auxcalc2 READ auxcalc2 WRITE setauxcalc2 NOTIFY auxcalc2Changed)
    Q_PROPERTY(qreal auxcalc3 READ auxcalc3 WRITE setauxcalc3 NOTIFY auxcalc3Changed)
    Q_PROPERTY(qreal auxcalc4 READ auxcalc4 WRITE setauxcalc4 NOTIFY auxcalc4Changed)

    // Flags

    Q_PROPERTY(qreal Flag1 READ Flag1 WRITE setFlag1 NOTIFY Flag1Changed)
    Q_PROPERTY(qreal Flag2 READ Flag2 WRITE setFlag2 NOTIFY Flag2Changed)
    Q_PROPERTY(qreal Flag3 READ Flag3 WRITE setFlag3 NOTIFY Flag3Changed)
    Q_PROPERTY(qreal Flag4 READ Flag4 WRITE setFlag4 NOTIFY Flag4Changed)
    Q_PROPERTY(qreal Flag5 READ Flag5 WRITE setFlag5 NOTIFY Flag5Changed)
    Q_PROPERTY(qreal Flag6 READ Flag6 WRITE setFlag6 NOTIFY Flag6Changed)
    Q_PROPERTY(qreal Flag7 READ Flag7 WRITE setFlag7 NOTIFY Flag7Changed)
    Q_PROPERTY(qreal Flag8 READ Flag8 WRITE setFlag8 NOTIFY Flag8Changed)
    Q_PROPERTY(qreal Flag9 READ Flag9 WRITE setFlag9 NOTIFY Flag9Changed)
    Q_PROPERTY(qreal Flag10 READ Flag10 WRITE setFlag10 NOTIFY Flag10Changed)
    Q_PROPERTY(qreal Flag11 READ Flag11 WRITE setFlag11 NOTIFY Flag11Changed)
    Q_PROPERTY(qreal Flag12 READ Flag12 WRITE setFlag12 NOTIFY Flag12Changed)
    Q_PROPERTY(qreal Flag13 READ Flag13 WRITE setFlag13 NOTIFY Flag13Changed)
    Q_PROPERTY(qreal Flag14 READ Flag14 WRITE setFlag14 NOTIFY Flag14Changed)
    Q_PROPERTY(qreal Flag15 READ Flag15 WRITE setFlag15 NOTIFY Flag15Changed)
    Q_PROPERTY(qreal Flag16 READ Flag16 WRITE setFlag16 NOTIFY Flag16Changed)

    //Flag Strings
    Q_PROPERTY(QString FlagString1 READ FlagString1 WRITE setFlagString1 NOTIFY FlagString1Changed)
    Q_PROPERTY(QString FlagString2 READ FlagString2 WRITE setFlagString2 NOTIFY FlagString2Changed)
    Q_PROPERTY(QString FlagString3 READ FlagString3 WRITE setFlagString3 NOTIFY FlagString3Changed)
    Q_PROPERTY(QString FlagString4 READ FlagString4 WRITE setFlagString4 NOTIFY FlagString4Changed)
    Q_PROPERTY(QString FlagString5 READ FlagString5 WRITE setFlagString5 NOTIFY FlagString5Changed)
    Q_PROPERTY(QString FlagString6 READ FlagString6 WRITE setFlagString6 NOTIFY FlagString6Changed)
    Q_PROPERTY(QString FlagString7 READ FlagString7 WRITE setFlagString7 NOTIFY FlagString7Changed)
    Q_PROPERTY(QString FlagString8 READ FlagString8 WRITE setFlagString8 NOTIFY FlagString8Changed)
    Q_PROPERTY(QString FlagString9 READ FlagString9 WRITE setFlagString9 NOTIFY FlagString9Changed)
    Q_PROPERTY(QString FlagString10 READ FlagString10 WRITE setFlagString10 NOTIFY FlagString10Changed)
    Q_PROPERTY(QString FlagString11 READ FlagString11 WRITE setFlagString11 NOTIFY FlagString11Changed)
    Q_PROPERTY(QString FlagString12 READ FlagString12 WRITE setFlagString12 NOTIFY FlagString12Changed)
    Q_PROPERTY(QString FlagString13 READ FlagString13 WRITE setFlagString13 NOTIFY FlagString13Changed)
    Q_PROPERTY(QString FlagString14 READ FlagString14 WRITE setFlagString14 NOTIFY FlagString14Changed)
    Q_PROPERTY(QString FlagString15 READ FlagString15 WRITE setFlagString15 NOTIFY FlagString15Changed)
    Q_PROPERTY(QString FlagString16 READ FlagString16 WRITE setFlagString16 NOTIFY FlagString16Changed)


    // Sensor Strings

    Q_PROPERTY(QString SensorString1 READ SensorString1 WRITE setSensorString1 NOTIFY SensorString1Changed)
    Q_PROPERTY(QString SensorString2 READ SensorString2 WRITE setSensorString2 NOTIFY SensorString2Changed)
    Q_PROPERTY(QString SensorString3 READ SensorString3 WRITE setSensorString3 NOTIFY SensorString3Changed)
    Q_PROPERTY(QString SensorString4 READ SensorString4 WRITE setSensorString4 NOTIFY SensorString4Changed)
    Q_PROPERTY(QString SensorString5 READ SensorString5 WRITE setSensorString5 NOTIFY SensorString5Changed)
    Q_PROPERTY(QString SensorString6 READ SensorString6 WRITE setSensorString6 NOTIFY SensorString6Changed)
    Q_PROPERTY(QString SensorString7 READ SensorString7 WRITE setSensorString7 NOTIFY SensorString7Changed)
    Q_PROPERTY(QString SensorString8 READ SensorString8 WRITE setSensorString8 NOTIFY SensorString8Changed)

    Q_PROPERTY(QString Platform READ Platform WRITE setPlatform NOTIFY PlatformChanged)


    //Adaptronic extra

    Q_PROPERTY(qreal MAP READ MAP WRITE setMAP NOTIFY MAPChanged)
    Q_PROPERTY(qreal AUXT READ AUXT WRITE setAUXT NOTIFY AUXTChanged)
    Q_PROPERTY(qreal AFR READ AFR WRITE setAFR NOTIFY AFRChanged)
    Q_PROPERTY(qreal TPS READ TPS WRITE setTPS NOTIFY TPSChanged)
    Q_PROPERTY(qreal IdleValue READ IdleValue WRITE setIdleValue NOTIFY IdleValueChanged)
    Q_PROPERTY(qreal MVSS READ MVSS WRITE setMVSS NOTIFY MVSSChanged)
    Q_PROPERTY(qreal SVSS READ SVSS WRITE setSVSS NOTIFY SVSSChanged)
    Q_PROPERTY(qreal Inj1 READ Inj1 WRITE setInj1 NOTIFY Inj1Changed)
    Q_PROPERTY(qreal Inj2 READ Inj2 WRITE setInj2 NOTIFY Inj2Changed)
    Q_PROPERTY(qreal Inj3 READ Inj3 WRITE setInj3 NOTIFY Inj3Changed)
    Q_PROPERTY(qreal Inj4 READ Inj4 WRITE setInj4 NOTIFY Inj4Changed)
    Q_PROPERTY(qreal Ign1 READ Ign1 WRITE setIgn1 NOTIFY Ign1Changed)
    Q_PROPERTY(qreal Ign2 READ Ign2 WRITE setIgn2 NOTIFY Ign2Changed)
    Q_PROPERTY(qreal Ign3 READ Ign3 WRITE setIgn3 NOTIFY Ign3Changed)
    Q_PROPERTY(qreal Ign4 READ Ign4 WRITE setIgn4 NOTIFY Ign4Changed)
    Q_PROPERTY(qreal TRIM READ TRIM WRITE setTRIM NOTIFY TRIMChanged)


public:
    DashBoard(QObject *parent = 0);

    // Odometer
    void setOdo(const qreal &Odo);


    // Advanced Info
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
    void setInjDuty(const qreal &InjDuty);

    void setEngLoad(const qreal &EngLoad);
    void setMAF1V(const qreal &MAF1V);
    void setMAF2V(const qreal &MAF2V);
    void setinjms(const qreal &injms);
    void setInj(const qreal &Inj);
    void setIgn(const qreal &Ign);
    void setDwell(const qreal &Dwell);
    void setBoostPres(const qreal &BoostPres);
    void setBoostDuty(const qreal &BoostDuty);
    void setMAFactivity(const qreal &MAFactivity);
    void setO2volt_2(const qreal &O2volt_2);



    //Boost

    void setpim(const qreal &pim);

    //Aux Differential inputs
    void setauxcalc1(const qreal &auxcalc1);
    void setauxcalc2(const qreal &auxcalc2);
    void setauxcalc3(const qreal &auxcalc3);
    void setauxcalc4(const qreal &auxcalc4);
    //Sensor Info

    void setsens1(const qreal &sens1);
    void setsens2(const qreal &sens2);
    void setsens3(const qreal &sens3);
    void setsens4(const qreal &sens4);
    void setsens5(const qreal &sens5);
    void setsens6(const qreal &sens6);
    void setsens7(const qreal &sens7);
    void setsens8(const qreal &sens8);

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

    //Flag Strings

    void setFlagString1(const QString &FlagString1);
    void setFlagString2(const QString &FlagString2);
    void setFlagString3(const QString &FlagString3);
    void setFlagString4(const QString &FlagString4);
    void setFlagString5(const QString &FlagString5);
    void setFlagString6(const QString &FlagString6);
    void setFlagString7(const QString &FlagString7);
    void setFlagString8(const QString &FlagString8);
    void setFlagString9(const QString &FlagString9);
    void setFlagString10(const QString &FlagString10);
    void setFlagString11(const QString &FlagString11);
    void setFlagString12(const QString &FlagString12);
    void setFlagString13(const QString &FlagString13);
    void setFlagString14(const QString &FlagString14);
    void setFlagString15(const QString &FlagString15);
    void setFlagString16(const QString &FlagString16);

    //Sensor Strings

    void setSensorString1(const QString &SensorString1);
    void setSensorString2(const QString &SensorString2);
    void setSensorString3(const QString &SensorString3);
    void setSensorString4(const QString &SensorString4);
    void setSensorString5(const QString &SensorString5);
    void setSensorString6(const QString &SensorString6);
    void setSensorString7(const QString &SensorString7);
    void setSensorString8(const QString &SensorString8);

    //Platform String


    void setPlatform(const QString &Platform);


    //Adaptronic extra

    void setMAP(const qreal &MAP);
    void setAUXT(const qreal &AUXT);
    void setAFR(const qreal &AFR);
    void setTPS(const qreal &TPS);
    void setIdleValue(const qreal &IdleValue);
    void setMVSS(const qreal &MVSS);
    void setSVSS(const qreal &SVSS);
    void setInj1(const qreal &Inj1);
    void setInj2(const qreal &Inj2);
    void setInj3(const qreal &Inj3);
    void setInj4(const qreal &Inj4);
    void setIgn1(const qreal &Ign1);
    void setIgn2(const qreal &Ign2);
    void setIgn3(const qreal &Ign3);
    void setIgn4(const qreal &Ign4);
    void setTRIM(const qreal &TRIM);


    qreal Odo() const;

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
    qreal InjDuty() const;
    qreal EngLoad() const;
    qreal MAF1V() const;
    qreal MAF2V() const;
    qreal injms() const;
    qreal Inj() const;
    qreal Ign() const;
    qreal Dwell() const;
    qreal BoostPres() const;
    qreal BoostDuty() const;
    qreal MAFactivity() const;
    qreal O2volt_2() const;

    //Boost
    qreal pim() const;


    //Aux Differential
    qreal auxcalc1() const;
    qreal auxcalc2() const;
    qreal auxcalc3() const;
    qreal auxcalc4() const;

    //Sensor Voltages

    qreal sens1() const;
    qreal sens2() const;
    qreal sens3() const;
    qreal sens4() const;
    qreal sens5() const;
    qreal sens6() const;
    qreal sens7() const;
    qreal sens8() const;


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

    // Flag Strings

    QString FlagString1() const;
    QString FlagString2() const;
    QString FlagString3() const;
    QString FlagString4() const;
    QString FlagString5() const;
    QString FlagString6() const;
    QString FlagString7() const;
    QString FlagString8() const;
    QString FlagString9() const;
    QString FlagString10() const;
    QString FlagString11() const;
    QString FlagString12() const;
    QString FlagString13() const;
    QString FlagString14() const;
    QString FlagString15() const;
    QString FlagString16() const;

    //Sensor Strings

    QString SensorString1() const;
    QString SensorString2() const;
    QString SensorString3() const;
    QString SensorString4() const;
    QString SensorString5() const;
    QString SensorString6() const;
    QString SensorString7() const;
    QString SensorString8() const;

    //Platform String

    QString Platform() const;



    //Adaptronic extra

    qreal MAP() const;
    qreal AUXT() const;
    qreal AFR() const;
    qreal TPS() const;
    qreal IdleValue() const;
    qreal MVSS() const;
    qreal SVSS() const;
    qreal Inj1() const;
    qreal Inj2() const;
    qreal Inj3() const;
    qreal Inj4() const;
    qreal Ign1() const;
    qreal Ign2() const;
    qreal Ign3() const;
    qreal Ign4() const;
    qreal TRIM() const;

signals:

    //Odometer
    void OdoChanged(qreal Odo);


    // Advanced Info
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
    void InjDutyChanged(qreal InjDuty);
    void EngLoadChanged(qreal EngLoad);
    void MAF1VChanged(qreal MAF1V);
    void MAF2VChanged(qreal MAF2V);
    void injmsChanged(qreal injms);
    void InjChanged(qreal Inj);
    void IgnChanged(qreal Ign);
    void DwellChanged(qreal Dwell);
    void BoostPresChanged(qreal BoostPres);
    void BoostDutyChanged(qreal BoostDuty);
    void MAFactivityChanged(qreal MAFactivity);
    void O2volt_2Changed(qreal O2volt_2);


     //Boost
     void pimChanged(qreal pim);

     //Aux Inputs

      void auxcalc1Changed(qreal auxcalc1);
      void auxcalc2Changed(qreal auxcalc2);
      void auxcalc3Changed(qreal auxcalc3);
      void auxcalc4Changed(qreal auxcalc4);

    //Sensor Voltages

     void sens1Changed(qreal sens1);
     void sens2Changed(qreal sens2);
     void sens3Changed(qreal sens3);
     void sens4Changed(qreal sens4);
     void sens5Changed(qreal sens5);
     void sens6Changed(qreal sens6);
     void sens7Changed(qreal sens7);
     void sens8Changed(qreal sens8);


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

    //Flag Strings

    void FlagString1Changed(QString FlagString1);
    void FlagString2Changed(QString FlagString2);
    void FlagString3Changed(QString FlagString3);
    void FlagString4Changed(QString FlagString4);
    void FlagString5Changed(QString FlagString5);
    void FlagString6Changed(QString FlagString6);
    void FlagString7Changed(QString FlagString7);
    void FlagString8Changed(QString FlagString8);
    void FlagString9Changed(QString FlagString9);
    void FlagString10Changed(QString FlagString10);
    void FlagString11Changed(QString FlagString11);
    void FlagString12Changed(QString FlagString12);
    void FlagString13Changed(QString FlagString13);
    void FlagString14Changed(QString FlagString14);
    void FlagString15Changed(QString FlagString15);
    void FlagString16Changed(QString FlagString16);

    //Sensor Strings

    void SensorString1Changed(QString SensorString1);
    void SensorString2Changed(QString SensorString2);
    void SensorString3Changed(QString SensorString3);
    void SensorString4Changed(QString SensorString4);
    void SensorString5Changed(QString SensorString5);
    void SensorString6Changed(QString SensorString6);
    void SensorString7Changed(QString SensorString7);
    void SensorString8Changed(QString SensorString8);

    //Platfrom String
    void PlatformChanged(QString Platform);


    //Adaptronic extra

    void MAPChanged(qreal MAP);
    void AUXTChanged(qreal AUXT);
    void AFRChanged(qreal AFR);
    void TPSChanged(qreal TPS);
    void IdleValueChanged(qreal IdleValue);
    void MVSSChanged(qreal MVSS);
    void SVSSChanged(qreal SVSS);
    void Inj1Changed(qreal Inj1);
    void Inj2Changed(qreal Inj2);
    void Inj3Changed(qreal Inj3);
    void Inj4Changed(qreal Inj4);
    void Ign1Changed(qreal Ign1);
    void Ign2Changed(qreal Ign2);
    void Ign3Changed(qreal Ign3);
    void Ign4Changed(qreal Ign4);
    void TRIMChanged(qreal TRIM);


private:
    // Odometer

    qreal m_Odo;

    // Advanced Info
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
    qreal m_InjDuty;
    qreal m_EngLoad;
    qreal m_MAF1V;
    qreal m_MAF2V;
    qreal m_injms;
    qreal m_Inj;
    qreal m_Ign;
    qreal m_Dwell;
    qreal m_BoostPres;
    qreal m_BoostDuty;
    qreal m_MAFactivity;
    qreal m_O2volt_2;


 //Boost
    qreal m_pim;

    //Aux Inputs
    qreal m_auxcalc1;
    qreal m_auxcalc2;
    qreal m_auxcalc3;
    qreal m_auxcalc4;

  //Sensor Voltage
    qreal m_sens1;
    qreal m_sens2;
    qreal m_sens3;
    qreal m_sens4;
    qreal m_sens5;
    qreal m_sens6;
    qreal m_sens7;
    qreal m_sens8;

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


    //Flag Strings

    QString m_FlagString1;
    QString m_FlagString2;
    QString m_FlagString3;
    QString m_FlagString4;
    QString m_FlagString5;
    QString m_FlagString6;
    QString m_FlagString7;
    QString m_FlagString8;
    QString m_FlagString9;
    QString m_FlagString10;
    QString m_FlagString11;
    QString m_FlagString12;
    QString m_FlagString13;
    QString m_FlagString14;
    QString m_FlagString15;
    QString m_FlagString16;

    //Sensor strings


    QString m_SensorString1;
    QString m_SensorString2;
    QString m_SensorString3;
    QString m_SensorString4;
    QString m_SensorString5;
    QString m_SensorString6;
    QString m_SensorString7;
    QString m_SensorString8;

    //Platform String

    QString m_Platform;


    //Adaptronic extra

    qreal m_MAP;
    qreal m_AUXT;
    qreal m_AFR;
    qreal m_TPS;
    qreal m_IdleValue;
    qreal m_MVSS;
    qreal m_SVSS;
    qreal m_Inj1;
    qreal m_Inj2;
    qreal m_Inj3;
    qreal m_Inj4;
    qreal m_Ign1;
    qreal m_Ign2;
    qreal m_Ign3;
    qreal m_Ign4;
    qreal m_TRIM;

};
