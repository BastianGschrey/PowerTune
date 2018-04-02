#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QStringList>
#include <QObject>

class DashBoard : public QObject
{
    Q_OBJECT

    // Odometer
    Q_PROPERTY(qreal Odo READ Odo WRITE setOdo NOTIFY odoChanged)

    //Tripmeter
    Q_PROPERTY(qreal Trip READ Trip WRITE setTrip NOTIFY tripChanged)
    // Advanced Info
    Q_PROPERTY(qreal rpm READ rpm WRITE setrpm NOTIFY rpmChanged)
    Q_PROPERTY(qreal Intakepress READ Intakepress WRITE setIntakepress NOTIFY intakepressChanged)
    Q_PROPERTY(qreal PressureV READ PressureV WRITE setPressureV NOTIFY pressureVChanged)
    Q_PROPERTY(qreal ThrottleV READ ThrottleV WRITE setThrottleV NOTIFY throttleVChanged)
    Q_PROPERTY(qreal Primaryinp READ Primaryinp WRITE setPrimaryinp NOTIFY primaryinpChanged)
    Q_PROPERTY(qreal Fuelc READ Fuelc WRITE setFuelc NOTIFY fuelcChanged)
    Q_PROPERTY(qreal Leadingign READ Leadingign WRITE setLeadingign NOTIFY leadingignChanged)
    Q_PROPERTY(qreal Trailingign READ Trailingign WRITE setTrailingign NOTIFY trailingignChanged)
    Q_PROPERTY(qreal Fueltemp READ Fueltemp WRITE setFueltemp NOTIFY fueltempChanged)
    Q_PROPERTY(qreal Moilp READ Moilp WRITE setMoilp NOTIFY moilpChanged)
    Q_PROPERTY(qreal Boosttp READ Boosttp WRITE setBoosttp NOTIFY boosttpChanged)
    Q_PROPERTY(qreal Boostwg READ Boostwg WRITE setBoostwg NOTIFY boostwgChanged)
    Q_PROPERTY(qreal Watertemp READ Watertemp WRITE setWatertemp NOTIFY watertempChanged)
    Q_PROPERTY(qreal Intaketemp READ Intaketemp WRITE setIntaketemp NOTIFY intaketempChanged)
    Q_PROPERTY(qreal Knock READ Knock WRITE setKnock NOTIFY knockChanged)
    Q_PROPERTY(qreal BatteryV READ BatteryV WRITE setBatteryV NOTIFY batteryVChanged)
    Q_PROPERTY(qreal speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(qreal Iscvduty READ Iscvduty WRITE setIscvduty NOTIFY iscvdutyChanged)
    Q_PROPERTY(qreal O2volt READ O2volt WRITE setO2volt NOTIFY o2voltChanged)
    Q_PROPERTY(qreal na1 READ na1 WRITE setna1 NOTIFY na1Changed)
    Q_PROPERTY(qreal Secinjpulse READ Secinjpulse WRITE setSecinjpulse NOTIFY secinjpulseChanged)
    Q_PROPERTY(qreal na2 READ na2 WRITE setna2 NOTIFY na2Changed)
    Q_PROPERTY(qreal InjDuty READ InjDuty WRITE setInjDuty NOTIFY injDutyChanged)
    Q_PROPERTY(qreal pim READ pim WRITE setpim NOTIFY pimChanged)

    Q_PROPERTY(qreal EngLoad READ EngLoad WRITE setEngLoad NOTIFY engLoadChanged)
    Q_PROPERTY(qreal MAF1V READ MAF1V WRITE setMAF1V NOTIFY mAF1VChanged)
    Q_PROPERTY(qreal MAF2V READ MAF2V WRITE setMAF2V NOTIFY mAF2VChanged)
    Q_PROPERTY(qreal injms READ injms WRITE setinjms NOTIFY injmsChanged)
    Q_PROPERTY(qreal Inj READ Inj WRITE setInj NOTIFY injChanged)
    Q_PROPERTY(qreal Ign READ Ign WRITE setIgn NOTIFY ignChanged)
    Q_PROPERTY(qreal Dwell READ Dwell WRITE setDwell NOTIFY dwellChanged)
    Q_PROPERTY(qreal BoostPres READ BoostPres WRITE setBoostPres NOTIFY boostPresChanged)
    Q_PROPERTY(qreal BoostDuty READ BoostDuty WRITE setBoostDuty NOTIFY boostDutyChanged)
    Q_PROPERTY(qreal MAFactivity READ MAFactivity WRITE setMAFactivity NOTIFY mAFactivityChanged)
    Q_PROPERTY(qreal O2volt_2 READ O2volt_2 WRITE setO2volt_2 NOTIFY o2volt_2Changed)

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

    Q_PROPERTY(qreal Flag1 READ Flag1 WRITE setFlag1 NOTIFY flag1Changed)
    Q_PROPERTY(qreal Flag2 READ Flag2 WRITE setFlag2 NOTIFY flag2Changed)
    Q_PROPERTY(qreal Flag3 READ Flag3 WRITE setFlag3 NOTIFY flag3Changed)
    Q_PROPERTY(qreal Flag4 READ Flag4 WRITE setFlag4 NOTIFY flag4Changed)
    Q_PROPERTY(qreal Flag5 READ Flag5 WRITE setFlag5 NOTIFY flag5Changed)
    Q_PROPERTY(qreal Flag6 READ Flag6 WRITE setFlag6 NOTIFY flag6Changed)
    Q_PROPERTY(qreal Flag7 READ Flag7 WRITE setFlag7 NOTIFY flag7Changed)
    Q_PROPERTY(qreal Flag8 READ Flag8 WRITE setFlag8 NOTIFY flag8Changed)
    Q_PROPERTY(qreal Flag9 READ Flag9 WRITE setFlag9 NOTIFY flag9Changed)
    Q_PROPERTY(qreal Flag10 READ Flag10 WRITE setFlag10 NOTIFY flag10Changed)
    Q_PROPERTY(qreal Flag11 READ Flag11 WRITE setFlag11 NOTIFY flag11Changed)
    Q_PROPERTY(qreal Flag12 READ Flag12 WRITE setFlag12 NOTIFY flag12Changed)
    Q_PROPERTY(qreal Flag13 READ Flag13 WRITE setFlag13 NOTIFY flag13Changed)
    Q_PROPERTY(qreal Flag14 READ Flag14 WRITE setFlag14 NOTIFY flag14Changed)
    Q_PROPERTY(qreal Flag15 READ Flag15 WRITE setFlag15 NOTIFY flag15Changed)
    Q_PROPERTY(qreal Flag16 READ Flag16 WRITE setFlag16 NOTIFY flag16Changed)

    //Flag Strings
    Q_PROPERTY(QString FlagString1 READ FlagString1 WRITE setFlagString1 NOTIFY flagString1Changed)
    Q_PROPERTY(QString FlagString2 READ FlagString2 WRITE setFlagString2 NOTIFY flagString2Changed)
    Q_PROPERTY(QString FlagString3 READ FlagString3 WRITE setFlagString3 NOTIFY flagString3Changed)
    Q_PROPERTY(QString FlagString4 READ FlagString4 WRITE setFlagString4 NOTIFY flagString4Changed)
    Q_PROPERTY(QString FlagString5 READ FlagString5 WRITE setFlagString5 NOTIFY flagString5Changed)
    Q_PROPERTY(QString FlagString6 READ FlagString6 WRITE setFlagString6 NOTIFY flagString6Changed)
    Q_PROPERTY(QString FlagString7 READ FlagString7 WRITE setFlagString7 NOTIFY flagString7Changed)
    Q_PROPERTY(QString FlagString8 READ FlagString8 WRITE setFlagString8 NOTIFY flagString8Changed)
    Q_PROPERTY(QString FlagString9 READ FlagString9 WRITE setFlagString9 NOTIFY flagString9Changed)
    Q_PROPERTY(QString FlagString10 READ FlagString10 WRITE setFlagString10 NOTIFY flagString10Changed)
    Q_PROPERTY(QString FlagString11 READ FlagString11 WRITE setFlagString11 NOTIFY flagString11Changed)
    Q_PROPERTY(QString FlagString12 READ FlagString12 WRITE setFlagString12 NOTIFY flagString12Changed)
    Q_PROPERTY(QString FlagString13 READ FlagString13 WRITE setFlagString13 NOTIFY flagString13Changed)
    Q_PROPERTY(QString FlagString14 READ FlagString14 WRITE setFlagString14 NOTIFY flagString14Changed)
    Q_PROPERTY(QString FlagString15 READ FlagString15 WRITE setFlagString15 NOTIFY flagString15Changed)
    Q_PROPERTY(QString FlagString16 READ FlagString16 WRITE setFlagString16 NOTIFY flagString16Changed)


    // Sensor Strings

    Q_PROPERTY(QString SensorString1 READ SensorString1 WRITE setSensorString1 NOTIFY sensorString1Changed)
    Q_PROPERTY(QString SensorString2 READ SensorString2 WRITE setSensorString2 NOTIFY sensorString2Changed)
    Q_PROPERTY(QString SensorString3 READ SensorString3 WRITE setSensorString3 NOTIFY sensorString3Changed)
    Q_PROPERTY(QString SensorString4 READ SensorString4 WRITE setSensorString4 NOTIFY sensorString4Changed)
    Q_PROPERTY(QString SensorString5 READ SensorString5 WRITE setSensorString5 NOTIFY sensorString5Changed)
    Q_PROPERTY(QString SensorString6 READ SensorString6 WRITE setSensorString6 NOTIFY sensorString6Changed)
    Q_PROPERTY(QString SensorString7 READ SensorString7 WRITE setSensorString7 NOTIFY sensorString7Changed)
    Q_PROPERTY(QString SensorString8 READ SensorString8 WRITE setSensorString8 NOTIFY sensorString8Changed)

    Q_PROPERTY(QString Platform READ Platform WRITE setPlatform NOTIFY platformChanged)

    Q_PROPERTY(QString SerialStat READ SerialStat WRITE setSerialStat NOTIFY serialStatChanged)
    Q_PROPERTY(QString RecvData READ RecvData WRITE setRecvData NOTIFY recvDataChanged)
    Q_PROPERTY(QString TimeoutStat READ TimeoutStat WRITE setTimeoutStat NOTIFY timeoutStatChanged)
    Q_PROPERTY(QString RunStat READ RunStat WRITE setRunStat NOTIFY runStatChanged)


    //Adaptronic extra

    Q_PROPERTY(qreal MAP READ MAP WRITE setMAP NOTIFY mAPChanged)
    Q_PROPERTY(qreal AUXT READ AUXT WRITE setAUXT NOTIFY aUXTChanged)
    Q_PROPERTY(qreal AFR READ AFR WRITE setAFR NOTIFY aFRChanged)
    Q_PROPERTY(qreal TPS READ TPS WRITE setTPS NOTIFY tPSChanged)
    Q_PROPERTY(qreal IdleValue READ IdleValue WRITE setIdleValue NOTIFY idleValueChanged)
    Q_PROPERTY(qreal MVSS READ MVSS WRITE setMVSS NOTIFY mVSSChanged)
    Q_PROPERTY(qreal SVSS READ SVSS WRITE setSVSS NOTIFY sVSSChanged)
    Q_PROPERTY(qreal Inj1 READ Inj1 WRITE setInj1 NOTIFY inj1Changed)
    Q_PROPERTY(qreal Inj2 READ Inj2 WRITE setInj2 NOTIFY inj2Changed)
    Q_PROPERTY(qreal Inj3 READ Inj3 WRITE setInj3 NOTIFY inj3Changed)
    Q_PROPERTY(qreal Inj4 READ Inj4 WRITE setInj4 NOTIFY inj4Changed)
    Q_PROPERTY(qreal Ign1 READ Ign1 WRITE setIgn1 NOTIFY ign1Changed)
    Q_PROPERTY(qreal Ign2 READ Ign2 WRITE setIgn2 NOTIFY ign2Changed)
    Q_PROPERTY(qreal Ign3 READ Ign3 WRITE setIgn3 NOTIFY ign3Changed)
    Q_PROPERTY(qreal Ign4 READ Ign4 WRITE setIgn4 NOTIFY ign4Changed)
    Q_PROPERTY(qreal TRIM READ TRIM WRITE setTRIM NOTIFY tRIMChanged)
    Q_PROPERTY(qreal LAMBDA READ LAMBDA WRITE setLAMBDA NOTIFY lAMBDAChanged)
    Q_PROPERTY(qreal LAMBDATarget READ LAMBDATarget WRITE setLAMBDATarget NOTIFY lAMBDATargetChanged)
    Q_PROPERTY(qreal FuelPress READ FuelPress WRITE setFuelPress NOTIFY fuelPressChanged)

    //GPS Strings


    Q_PROPERTY(QString gpsTime READ gpsTime WRITE setgpsTime NOTIFY gpsTimeChanged)
    Q_PROPERTY(QString gpsAltitude READ gpsAltitude WRITE setgpsAltitude NOTIFY gpsAltitudeChanged)
    Q_PROPERTY(QString gpsLatitude READ gpsLatitude WRITE setgpsLatitude NOTIFY gpsLatitudeChanged)
    Q_PROPERTY(QString gpsLongitude READ gpsLongitude WRITE setgpsLongitude NOTIFY gpsLongitudeChanged)
    Q_PROPERTY(QString gpsSpeed READ gpsSpeed WRITE setgpsSpeed NOTIFY gpsSpeedChanged)
    Q_PROPERTY(QString gpsVisibleSatelites READ gpsVisibleSatelites WRITE setgpsVisibleSatelites NOTIFY gpsVisibleSatelitesChanged)

    //Units ( metric /imperial select
    Q_PROPERTY(QString units READ units WRITE setunits NOTIFY unitsChanged)

    //Qsensors
    Q_PROPERTY(qreal accelx READ accelx WRITE setaccelx NOTIFY accelxChanged)
    Q_PROPERTY(qreal accely READ accely WRITE setaccely NOTIFY accelyChanged)
    Q_PROPERTY(qreal accelz READ accelz WRITE setaccelz NOTIFY accelzChanged)
    Q_PROPERTY(qreal gyrox READ gyrox WRITE setgyrox NOTIFY gyroxChanged)
    Q_PROPERTY(qreal gyroy READ gyroy WRITE setgyroy NOTIFY gyroyChanged)
    Q_PROPERTY(qreal gyroz READ gyroz WRITE setgyroz NOTIFY gyrozChanged)
    Q_PROPERTY(qreal compass READ compass WRITE setcompass NOTIFY compassChanged)
    Q_PROPERTY(qreal ambitemp READ ambitemp WRITE setambitemp NOTIFY ambitempChanged)
    Q_PROPERTY(qreal ambipress READ ambipress WRITE setambipress NOTIFY ambipressChanged)

    //Calculations
    Q_PROPERTY(qreal Gear READ Gear WRITE setGear NOTIFY gearChanged)
    Q_PROPERTY(qreal Power READ Power WRITE setPower NOTIFY powerChanged)
    Q_PROPERTY(qreal Torque READ Torque WRITE setTorque NOTIFY torqueChanged)
    Q_PROPERTY(qreal AccelTimer READ AccelTimer WRITE setAccelTimer NOTIFY accelTimerChanged)
    Q_PROPERTY(qreal Weight READ Weight WRITE setWeight NOTIFY weightChanged)

    //Official Pi screen present screen
    Q_PROPERTY(bool screen READ screen WRITE setscreen NOTIFY screenChanged)

    //User Dashboard Stringlist dashsetup

    Q_PROPERTY(QStringList dashsetup READ dashsetup WRITE setdashsetup NOTIFY dashsetupChanged)



public:
    DashBoard(QObject *parent = 0);

    // Odometer
    void setOdo(const qreal &Odo);
    //Tripmeter
    void setTrip(const qreal &Trip);
    // Advanced Info
    void setrpm(const qreal &rpm);
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

    void setSerialStat(const QString &SerialStat);
    void setRecvData(const QString &RecvData);
    void setTimeoutStat(const QString &TimeoutStat);
    void setRunStat(const QString &RunStat);

    // GPS

    void setgpsTime(const QString &gpsTime);
    void setgpsAltitude(const QString &gpsAltitude);
    void setgpsLatitude(const QString &gpsLatitude);
    void setgpsLongitude(const QString &gpsLongitude);
    void setgpsSpeed(const QString &gpsSpeed);
    void setgpsVisibleSatelites(const QString &gpsVisibleSatelites);
    // Units
    void setunits(const QString &units);






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
    void setLAMBDA(const qreal &LAMBDA);
    void setLAMBDATarget(const qreal &LAMBDATarget);
    void setFuelPress(const qreal &FuelPress);


//qsensors
    void setaccelx(const qreal &accelx);
    void setaccely(const qreal &accely);
    void setaccelz(const qreal &accelz);
    void setgyrox(const qreal &gyrox);
    void setgyroy(const qreal &gyroy);
    void setgyroz(const qreal &gyroz);
    void setcompass(const qreal &compass);
    void setambitemp(const qreal &ambitemp);
    void setambipress(const qreal &ambipress);

// calculations
    void setGear(const qreal &Gear);
    void setPower(const qreal &Power);
    void setTorque(const qreal &Torque);
    void setAccelTimer(const qreal &AccelTimer);
    void setWeight(const qreal &Weight);

//Official Pi screen present screen
    void setscreen(const bool &screen);

 //User Dashboard Stringlist dashsetup

    void setdashsetup(const QStringList &dashsetup);

    qreal Odo() const;

    //Tripmeter

    qreal Trip() const;

    // Advanced Info FD3S
    qreal rpm() const;
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

    QString SerialStat() const;
    QString RecvData() const;
    QString TimeoutStat() const;
    QString RunStat() const;

    // GPS

    QString gpsTime() const;
    QString gpsAltitude() const;
    QString gpsLatitude() const;
    QString gpsLongitude() const;
    QString gpsSpeed() const;
    QString gpsVisibleSatelites() const;
//units
    QString units() const;


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
    qreal LAMBDA() const;
    qreal LAMBDATarget() const;
    qreal FuelPress() const;

    //qsensors

    qreal accelx() const;
    qreal accely() const;
    qreal accelz() const;
    qreal gyrox() const;
    qreal gyroy() const;
    qreal gyroz() const;
    qreal compass() const;
    qreal ambitemp() const;
    qreal ambipress() const;

    //calculations
    qreal Gear() const;
    qreal Power() const;
    qreal Torque() const;
    qreal AccelTimer() const;
    qreal Weight() const;


    //Official Pi screen present screen
     bool screen() const;

     //User Dashboard Stringlist

     QStringList dashsetup() const;

signals:

    //Odometer
    void odoChanged(qreal Odo);
    //Tripmeter
    void tripChanged(qreal Trip);
    // Advanced Info
    void rpmChanged(qreal rpm);
    void intakepressChanged(qreal Intakepress);
    void pressureVChanged(qreal PressureV);
    void throttleVChanged(qreal ThrottleV);
    void primaryinpChanged(qreal Primaryinp);
    void fuelcChanged(qreal Fuelc);
    void leadingignChanged(qreal Leadingign);
    void trailingignChanged(qreal Trailingign);
    void fueltempChanged(qreal Fueltemp);
    void moilpChanged(qreal Moilp);
    void boosttpChanged(qreal Boosttp);
    void boostwgChanged(qreal Boostwg);
    void watertempChanged(qreal Watertemp);
    void intaketempChanged(qreal Intaketemp);
    void knockChanged(qreal Knock);
    void speedChanged(qreal speed);
    void batteryVChanged(qreal BatteryV);
    void iscvdutyChanged(qreal Iscvduty);
    void o2voltChanged(qreal O2volt);
    void na1Changed(qreal na1);
    void secinjpulseChanged(qreal Secinjpulse);
    void na2Changed(qreal na2);
    void injDutyChanged(qreal InjDuty);
    void engLoadChanged(qreal EngLoad);
    void mAF1VChanged(qreal MAF1V);
    void mAF2VChanged(qreal MAF2V);
    void injmsChanged(qreal injms);
    void injChanged(qreal Inj);
    void ignChanged(qreal Ign);
    void dwellChanged(qreal Dwell);
    void boostPresChanged(qreal BoostPres);
    void boostDutyChanged(qreal BoostDuty);
    void mAFactivityChanged(qreal MAFactivity);
    void o2volt_2Changed(qreal O2volt_2);


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

    void flag1Changed(qreal Flag1);
    void flag2Changed(qreal Flag2);
    void flag3Changed(qreal Flag3);
    void flag4Changed(qreal Flag4);
    void flag5Changed(qreal Flag5);
    void flag6Changed(qreal Flag6);
    void flag7Changed(qreal Flag7);
    void flag8Changed(qreal Flag8);
    void flag9Changed(qreal Flag9);
    void flag10Changed(qreal Flag10);
    void flag11Changed(qreal Flag11);
    void flag12Changed(qreal Flag12);
    void flag13Changed(qreal Flag13);
    void flag14Changed(qreal Flag14);
    void flag15Changed(qreal Flag15);
    void flag16Changed(qreal Flag16);

    //Flag Strings

    void flagString1Changed(QString FlagString1);
    void flagString2Changed(QString FlagString2);
    void flagString3Changed(QString FlagString3);
    void flagString4Changed(QString FlagString4);
    void flagString5Changed(QString FlagString5);
    void flagString6Changed(QString FlagString6);
    void flagString7Changed(QString FlagString7);
    void flagString8Changed(QString FlagString8);
    void flagString9Changed(QString FlagString9);
    void flagString10Changed(QString FlagString10);
    void flagString11Changed(QString FlagString11);
    void flagString12Changed(QString FlagString12);
    void flagString13Changed(QString FlagString13);
    void flagString14Changed(QString FlagString14);
    void flagString15Changed(QString FlagString15);
    void flagString16Changed(QString FlagString16);

    //Sensor Strings

    void sensorString1Changed(QString SensorString1);
    void sensorString2Changed(QString SensorString2);
    void sensorString3Changed(QString SensorString3);
    void sensorString4Changed(QString SensorString4);
    void sensorString5Changed(QString SensorString5);
    void sensorString6Changed(QString SensorString6);
    void sensorString7Changed(QString SensorString7);
    void sensorString8Changed(QString SensorString8);

    //Platfrom String
    void platformChanged(QString Platform);

    void serialStatChanged(QString SerialStat);
    void recvDataChanged(QString RecvData);
    void timeoutStatChanged(QString TimeoutStat);
    void runStatChanged(QString RunStat);

    // GPS

    void gpsTimeChanged(QString gpsTime);
    void gpsAltitudeChanged(QString gpsAltitude);
    void gpsLatitudeChanged(QString gpsLatitude);
    void gpsLongitudeChanged(QString gpsLongitude);
    void gpsSpeedChanged(QString gpsSpeed);
    void gpsVisibleSatelitesChanged(QString gpsVisibleSatelites);

    // units

    void unitsChanged(QString units);

    //Adaptronic extra

    void mAPChanged(qreal MAP);
    void aUXTChanged(qreal AUXT);
    void aFRChanged(qreal AFR);
    void tPSChanged(qreal TPS);
    void idleValueChanged(qreal IdleValue);
    void mVSSChanged(qreal MVSS);
    void sVSSChanged(qreal SVSS);
    void inj1Changed(qreal Inj1);
    void inj2Changed(qreal Inj2);
    void inj3Changed(qreal Inj3);
    void inj4Changed(qreal Inj4);
    void ign1Changed(qreal Ign1);
    void ign2Changed(qreal Ign2);
    void ign3Changed(qreal Ign3);
    void ign4Changed(qreal Ign4);
    void tRIMChanged(qreal TRIM);
    void lAMBDAChanged(qreal LAMBDA);
    void lAMBDATargetChanged(qreal LAMBDATarget);
    void fuelPressChanged(qreal FuelPress);

    void accelxChanged(qreal accelx);
    void accelyChanged(qreal accely);
    void accelzChanged(qreal accelz);
    void gyroxChanged(qreal gyrox);
    void gyroyChanged(qreal gyroy);
    void gyrozChanged(qreal gyroz);
    void compassChanged(qreal compass);
    void ambitempChanged(qreal ambitemp);
    void ambipressChanged(qreal ambipress);

    // calculations
    void gearChanged(qreal Gear);
    void powerChanged(qreal Power);
    void torqueChanged(qreal Torque);
    void accelTimerChanged(qreal AccelTimer);
    void weightChanged(qreal Weight);

    //Official Pi screen present screen
    void screenChanged(bool screen);


    //User Dashboard Stringlist

    void dashsetupChanged(QStringList dashsetup);

private:
    // Odometer

    qreal m_Odo;

    // Tripmeter

    qreal m_Trip;

    // Advanced Info
    qreal m_rpm;
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
    qreal m_BatteryV;
    qreal m_speed;
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


    //Platform String

    QString m_Platform;

    QString m_SerialStat;
    QString m_RecvData;
    QString m_TimeoutStat;
    QString m_RunStat;


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
    qreal m_LAMBDA;
    qreal m_LAMBDATarget;
    qreal m_FuelPress;

    // GPS

    QString m_gpsTime;
    QString m_gpsAltitude;
    QString m_gpsLatitude;
    QString m_gpsLongitude;
    QString m_gpsSpeed;
    QString m_gpsVisibleSatelites;

    //Units

    QString m_units;

    //qsensors

    qreal m_accelx;
    qreal m_accely;
    qreal m_accelz;
    qreal m_gyrox;
    qreal m_gyroy;
    qreal m_gyroz;
    qreal m_compass;
    qreal m_ambitemp;
    qreal m_ambipress;

    //calculations

    qreal m_Gear;
    qreal m_Power;
    qreal m_Torque;
    qreal m_AccelTimer;
    qreal m_Weight;

    //Official Pi screen present screen
    bool m_screen;
    //User Dashboard Stringlist  dashsetup

    QStringList m_dashsetup;


};

#endif // DASHBOARD_H
