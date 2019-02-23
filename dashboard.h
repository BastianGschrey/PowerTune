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
    Q_PROPERTY(qreal InjDuty2 READ InjDuty2 WRITE setInjDuty2 NOTIFY injDuty2Changed)
    Q_PROPERTY(qreal InjAngle READ InjAngle WRITE setInjAngle NOTIFY InjAngleChanged)

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
    Q_PROPERTY(qreal Flag17 READ Flag17 WRITE setFlag17 NOTIFY flag17Changed)
    Q_PROPERTY(qreal Flag18 READ Flag18 WRITE setFlag18 NOTIFY flag18Changed)
    Q_PROPERTY(qreal Flag19 READ Flag19 WRITE setFlag19 NOTIFY flag19Changed)
    Q_PROPERTY(qreal Flag20 READ Flag20 WRITE setFlag20 NOTIFY flag20Changed)
    Q_PROPERTY(qreal Flag21 READ Flag21 WRITE setFlag21 NOTIFY flag21Changed)
    Q_PROPERTY(qreal Flag22 READ Flag22 WRITE setFlag22 NOTIFY flag22Changed)
    Q_PROPERTY(qreal Flag23 READ Flag23 WRITE setFlag23 NOTIFY flag23Changed)
    Q_PROPERTY(qreal Flag24 READ Flag24 WRITE setFlag24 NOTIFY flag24Changed)
    Q_PROPERTY(qreal Flag25 READ Flag25 WRITE setFlag25 NOTIFY flag25Changed)

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
    Q_PROPERTY(double gpsAltitude READ gpsAltitude WRITE setgpsAltitude NOTIFY gpsAltitudeChanged)
    Q_PROPERTY(double gpsLatitude READ gpsLatitude WRITE setgpsLatitude NOTIFY gpsLatitudeChanged)
    Q_PROPERTY(double gpsLongitude READ gpsLongitude WRITE setgpsLongitude NOTIFY gpsLongitudeChanged)
    Q_PROPERTY(double gpsSpeed READ gpsSpeed WRITE setgpsSpeed NOTIFY gpsSpeedChanged)
    Q_PROPERTY(int gpsVisibleSatelites READ gpsVisibleSatelites WRITE setgpsVisibleSatelites NOTIFY gpsVisibleSatelitesChanged)
    Q_PROPERTY(QString gpsFIXtype READ gpsFIXtype  WRITE setgpsFIXtype  NOTIFY gpsFIXtypeChanged)
    Q_PROPERTY(qreal gpsbaering READ gpsbaering WRITE setgpsbaering NOTIFY gpsbaeringChanged)

    //Units ( metric /imperial select
    Q_PROPERTY(QString units READ units WRITE setunits NOTIFY unitsChanged)
    Q_PROPERTY(QString speedunits READ speedunits WRITE setspeedunits NOTIFY speedunitsChanged)
    Q_PROPERTY(QString pressureunits READ pressureunits WRITE setpressureunits NOTIFY pressureunitsChanged)
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

    Q_PROPERTY(QStringList maindashsetup READ maindashsetup WRITE setmaindashsetup NOTIFY maindashsetupChanged)
    Q_PROPERTY(QStringList dashsetup3 READ dashsetup3 WRITE setdashsetup3 NOTIFY dashsetup3Changed)
    Q_PROPERTY(QStringList dashsetup2 READ dashsetup2 WRITE setdashsetup3 NOTIFY dashsetup2Changed)
    Q_PROPERTY(QStringList dashsetup1 READ dashsetup1 WRITE setdashsetup1 NOTIFY dashsetup1Changed)


    Q_PROPERTY(QStringList dashfiles READ dashfiles WRITE setdashfiles NOTIFY dashfilesChanged)

    Q_PROPERTY(qreal accelpedpos READ accelpedpos WRITE setaccelpedpos NOTIFY accelpedposChanged)
    Q_PROPERTY(qreal airtempensor2 READ airtempensor2 WRITE setairtempensor2 NOTIFY airtempensor2Changed)
    Q_PROPERTY(qreal antilaglauchswitch READ antilaglauchswitch WRITE setantilaglauchswitch NOTIFY antilaglauchswitchChanged)
    Q_PROPERTY(qreal antilaglaunchon READ antilaglaunchon WRITE setantilaglaunchon NOTIFY antilaglaunchonChanged)
    Q_PROPERTY(qreal auxrevlimitswitch READ auxrevlimitswitch WRITE setauxrevlimitswitch NOTIFY auxrevlimitswitchChanged)
    Q_PROPERTY(qreal avfueleconomy READ avfueleconomy WRITE setavfueleconomy NOTIFY avfueleconomyChanged)
    Q_PROPERTY(qreal battlight READ battlight WRITE setbattlight NOTIFY battlightChanged)
    Q_PROPERTY(qreal boostcontrol READ boostcontrol WRITE setboostcontrol NOTIFY boostcontrolChanged)
    Q_PROPERTY(qreal brakepress READ brakepress WRITE setbrakepress NOTIFY brakepressChanged)
    Q_PROPERTY(qreal clutchswitchstate READ clutchswitchstate WRITE setclutchswitchstate NOTIFY clutchswitchstateChanged)
    Q_PROPERTY(qreal coolantpress READ coolantpress WRITE setcoolantpress NOTIFY coolantpressChanged)
    Q_PROPERTY(qreal decelcut READ decelcut WRITE setdecelcut NOTIFY decelcutChanged)
    Q_PROPERTY(qreal diffoiltemp READ diffoiltemp WRITE setdiffoiltemp NOTIFY diffoiltempChanged)
    Q_PROPERTY(qreal distancetoempty READ distancetoempty WRITE setdistancetoempty NOTIFY distancetoemptyChanged)
    Q_PROPERTY(qreal egt1 READ egt1 WRITE setegt1 NOTIFY egt1Changed)
    Q_PROPERTY(qreal egt2 READ egt2 WRITE setegt2 NOTIFY egt2Changed)
    Q_PROPERTY(qreal egt3 READ egt3 WRITE setegt3 NOTIFY egt3Changed)
    Q_PROPERTY(qreal egt4 READ egt4 WRITE setegt4 NOTIFY egt4Changed)
    Q_PROPERTY(qreal egt5 READ egt5 WRITE setegt5 NOTIFY egt5Changed)
    Q_PROPERTY(qreal egt6 READ egt6 WRITE setegt6 NOTIFY egt6Changed)
    Q_PROPERTY(qreal egt7 READ egt7 WRITE setegt7 NOTIFY egt7Changed)
    Q_PROPERTY(qreal egt8 READ egt8 WRITE setegt8 NOTIFY egt8Changed)
    Q_PROPERTY(qreal egt9 READ egt9 WRITE setegt9 NOTIFY egt9Changed)
    Q_PROPERTY(qreal egt10 READ egt10 WRITE setegt10 NOTIFY egt10Changed)
    Q_PROPERTY(qreal egt11 READ egt11 WRITE setegt11 NOTIFY egt11Changed)
    Q_PROPERTY(qreal egt12 READ egt12 WRITE setegt12 NOTIFY egt12Changed)
    Q_PROPERTY(qreal excamangle1 READ excamangle1 WRITE setexcamangle1 NOTIFY excamangle1Changed)
    Q_PROPERTY(qreal excamangle2 READ excamangle2 WRITE setexcamangle2 NOTIFY excamangle2Changed)
    Q_PROPERTY(qreal flatshiftstate READ flatshiftstate WRITE setflatshiftstate NOTIFY flatshiftstateChanged)
    Q_PROPERTY(qreal fuelclevel READ fuelclevel WRITE setfuelclevel NOTIFY fuelclevelChanged)
    Q_PROPERTY(qreal fuelcomposition READ fuelcomposition WRITE setfuelcomposition NOTIFY fuelcompositionChanged)
    Q_PROPERTY(qreal fuelconsrate READ fuelconsrate WRITE setfuelconsrate NOTIFY fuelconsrateChanged)
    Q_PROPERTY(qreal fuelcutperc READ fuelcutperc WRITE setfuelcutperc NOTIFY fuelcutpercChanged)

    Q_PROPERTY(qreal fuelflow READ fuelflow WRITE setfuelflow NOTIFY fuelflowChanged)
    Q_PROPERTY(qreal fuelflowdiff READ fuelflowdiff WRITE setfuelflowdiff NOTIFY fuelflowdiffChanged)
    Q_PROPERTY(qreal fuelflowret READ fuelflowret WRITE setfuelflowret NOTIFY fuelflowretChanged)
    Q_PROPERTY(qreal fueltrimlongtbank1 READ fueltrimlongtbank1 WRITE setfueltrimlongtbank1 NOTIFY fueltrimlongtbank1Changed)
    Q_PROPERTY(qreal fueltrimlongtbank2 READ fueltrimlongtbank2 WRITE setfueltrimlongtbank2 NOTIFY fueltrimlongtbank2Changed)
    Q_PROPERTY(qreal fueltrimshorttbank1 READ fueltrimshorttbank1 WRITE setfueltrimshorttbank1 NOTIFY fueltrimshorttbank1Changed)
    Q_PROPERTY(qreal fueltrimshorttbank2 READ fueltrimshorttbank2 WRITE setfueltrimshorttbank2 NOTIFY fueltrimshorttbank2Changed)
    Q_PROPERTY(qreal gearswitch READ gearswitch WRITE setgearswitch NOTIFY gearswitchChanged)
    Q_PROPERTY(qreal handbrake READ handbrake WRITE sethandbrake NOTIFY handbrakeChanged)
    Q_PROPERTY(qreal highbeam READ highbeam WRITE sethighbeam NOTIFY highbeamChanged)
    Q_PROPERTY(qreal homeccounter READ homeccounter WRITE sethomeccounter NOTIFY homeccounterChanged)
    Q_PROPERTY(qreal incamangle1 READ incamangle1 WRITE setincamangle1 NOTIFY incamangle1Changed)
    Q_PROPERTY(qreal incamangle2 READ incamangle2 WRITE setincamangle2 NOTIFY incamangle2Changed)
    Q_PROPERTY(qreal knocklevlogged1 READ knocklevlogged1 WRITE setknocklevlogged1 NOTIFY knocklevlogged1Changed)
    Q_PROPERTY(qreal knocklevlogged2 READ knocklevlogged2 WRITE setknocklevlogged2 NOTIFY knocklevlogged2Changed)
    Q_PROPERTY(qreal knockretardbank1 READ knockretardbank1 WRITE setknockretardbank1 NOTIFY knockretardbank1Changed)
    Q_PROPERTY(qreal knockretardbank2 READ knockretardbank2 WRITE setknockretardbank2 NOTIFY knockretardbank2Changed)
    Q_PROPERTY(qreal lambda2 READ lambda2 WRITE setlambda2 NOTIFY lambda2Changed)
    Q_PROPERTY(qreal lambda3 READ lambda3 WRITE setlambda3 NOTIFY lambda3Changed)
    Q_PROPERTY(qreal lambda4 READ lambda4 WRITE setlambda4 NOTIFY lambda4Changed)
    Q_PROPERTY(qreal launchcontolfuelenrich READ launchcontolfuelenrich WRITE setlaunchcontolfuelenrich NOTIFY launchcontolfuelenrichChanged)
    Q_PROPERTY(qreal launchctrolignretard READ launchctrolignretard WRITE setlaunchctrolignretard NOTIFY launchctrolignretardChanged)
    Q_PROPERTY(qreal leftindicator READ leftindicator WRITE setleftindicator NOTIFY leftindicatorChanged)
    Q_PROPERTY(qreal limpmode READ limpmode WRITE setlimpmode NOTIFY limpmodeChanged)
    Q_PROPERTY(qreal mil READ mil WRITE setmil NOTIFY milChanged)
    Q_PROPERTY(qreal missccount READ missccount WRITE setmissccount NOTIFY missccountChanged)
    Q_PROPERTY(qreal nosactive READ nosactive WRITE setnosactive NOTIFY nosactiveChanged)
    Q_PROPERTY(qreal nospress READ nospress WRITE setnospress NOTIFY nospressChanged)
    Q_PROPERTY(qreal nosswitch READ nosswitch WRITE setnosswitch NOTIFY nosswitchChanged)
    Q_PROPERTY(qreal oilpres READ oilpres WRITE setoilpres NOTIFY oilpresChanged)
    Q_PROPERTY(qreal oiltemp READ oiltemp WRITE setoiltemp NOTIFY oiltempChanged)
    Q_PROPERTY(qreal rallyantilagswitch READ rallyantilagswitch WRITE setrallyantilagswitch NOTIFY rallyantilagswitchChanged)
    Q_PROPERTY(qreal rightindicator READ rightindicator WRITE setrightindicator NOTIFY rightindicatorChanged)
    Q_PROPERTY(qreal targetbstlelkpa READ targetbstlelkpa WRITE settargetbstlelkpa NOTIFY targetbstlelkpaChanged)
    Q_PROPERTY(qreal timeddutyout1 READ timeddutyout1 WRITE settimeddutyout1 NOTIFY timeddutyout1Changed)
    Q_PROPERTY(qreal timeddutyout2 READ timeddutyout2 WRITE settimeddutyout2 NOTIFY timeddutyout2Changed)
    Q_PROPERTY(qreal timeddutyoutputactive READ timeddutyoutputactive WRITE settimeddutyoutputactive NOTIFY timeddutyoutputactiveChanged)
    Q_PROPERTY(qreal torqueredcutactive READ torqueredcutactive WRITE settorqueredcutactive NOTIFY torqueredcutactiveChanged)
    Q_PROPERTY(qreal torqueredlevelactive READ torqueredlevelactive WRITE settorqueredlevelactive NOTIFY torqueredlevelactiveChanged)
    Q_PROPERTY(qreal transientthroactive READ transientthroactive WRITE settransientthroactive NOTIFY transientthroactiveChanged)
    Q_PROPERTY(qreal transoiltemp READ transoiltemp WRITE settransoiltemp NOTIFY transoiltempChanged)
    Q_PROPERTY(qreal triggerccounter READ triggerccounter WRITE settriggerccounter NOTIFY triggerccounterChanged)
    Q_PROPERTY(qreal triggersrsinceasthome READ triggersrsinceasthome WRITE settriggersrsinceasthome NOTIFY triggersrsinceasthomeChanged)
    Q_PROPERTY(qreal turborpm READ turborpm WRITE setturborpm NOTIFY turborpmChanged)
    Q_PROPERTY(qreal wastegatepress READ wastegatepress WRITE setwastegatepress NOTIFY wastegatepressChanged)
    Q_PROPERTY(qreal wheeldiff READ wheeldiff WRITE setwheeldiff NOTIFY wheeldiffChanged)
    Q_PROPERTY(qreal wheelslip READ wheelslip WRITE setwheelslip NOTIFY wheelslipChanged)
    Q_PROPERTY(qreal wheelspdftleft READ wheelspdftleft WRITE setwheelspdftleft NOTIFY wheelspdftleftChanged)
    Q_PROPERTY(qreal wheelspdftright READ wheelspdftright WRITE setwheelspdftright NOTIFY wheelspdftrightChanged)
    Q_PROPERTY(qreal wheelspdrearleft READ wheelspdrearleft WRITE setwheelspdrearleft NOTIFY wheelspdrearleftChanged)
    Q_PROPERTY(qreal wheelspdrearright READ wheelspdrearright WRITE setwheelspdrearright NOTIFY wheelspdrearrightChanged)
    //Path for musicfiles
    Q_PROPERTY(QString musicpath READ musicpath WRITE setmusicpath NOTIFY musicpathChanged)

    Q_PROPERTY(int supportedReg READ supportedReg WRITE setsupportedReg NOTIFY supportedRegChanged)
    Q_PROPERTY(qreal speedpercent READ speedpercent WRITE setspeedpercent NOTIFY speedpercentChanged)

    Q_PROPERTY(int maxRPM READ maxRPM WRITE setmaxRPM NOTIFY maxRPMChanged)
    Q_PROPERTY(int rpmStage1 READ rpmStage1 WRITE setrpmStage1 NOTIFY rpmStage1Changed)
    Q_PROPERTY(int rpmStage2 READ rpmStage2 WRITE setrpmStage2 NOTIFY rpmStage2Changed)
    Q_PROPERTY(int rpmStage3 READ rpmStage3 WRITE setrpmStage3 NOTIFY rpmStage3Changed)
    Q_PROPERTY(int rpmStage4 READ rpmStage4 WRITE setrpmStage4 NOTIFY rpmStage4Changed)

    Q_PROPERTY(int waterwarn READ waterwarn WRITE setwaterwarn NOTIFY waterwarnChanged)
    Q_PROPERTY(int rpmwarn READ rpmwarn WRITE setrpmwarn NOTIFY rpmwarnChanged)
    Q_PROPERTY(int knockwarn READ knockwarn WRITE setknockwarn NOTIFY knockwarnChanged)
    Q_PROPERTY(qreal boostwarn READ boostwarn WRITE setboostwarn NOTIFY boostwarnChanged)
    Q_PROPERTY(int smoothrpm READ smoothrpm WRITE setsmoothrpm NOTIFY smoothrpmChanged)
    Q_PROPERTY(int smoothspeed READ smoothspeed WRITE setsmoothspeed NOTIFY smoothspeedChanged)

    Q_PROPERTY(int gearcalc1 READ gearcalc1 WRITE setgearcalc1 NOTIFY gearcalc1Changed)
    Q_PROPERTY(int gearcalc2 READ gearcalc2 WRITE setgearcalc2 NOTIFY gearcalc2Changed)
    Q_PROPERTY(int gearcalc3 READ gearcalc3 WRITE setgearcalc3 NOTIFY gearcalc3Changed)
    Q_PROPERTY(int gearcalc4 READ gearcalc4 WRITE setgearcalc4 NOTIFY gearcalc4Changed)
    Q_PROPERTY(int gearcalc5 READ gearcalc5 WRITE setgearcalc5 NOTIFY gearcalc5Changed)
    Q_PROPERTY(int gearcalc6 READ gearcalc6 WRITE setgearcalc6 NOTIFY gearcalc6Changed)
    Q_PROPERTY(int gearcalcactivation READ gearcalcactivation WRITE setgearcalcactivation NOTIFY gearcalcactivationChanged)

    Q_PROPERTY(int ecu READ ecu WRITE setecu NOTIFY ecuChanged)

    Q_PROPERTY(int rpmstyle1 READ rpmstyle1 WRITE setrpmstyle1 NOTIFY rpmstyle1Changed)
    Q_PROPERTY(int rpmstyle2 READ rpmstyle2 WRITE setrpmstyle2 NOTIFY rpmstyle2Changed)
    Q_PROPERTY(int rpmstyle3 READ rpmstyle3 WRITE setrpmstyle3 NOTIFY rpmstyle3Changed)

    Q_PROPERTY(QString Error READ Error WRITE setError NOTIFY ErrorChanged)

    Q_PROPERTY(int ExternalSpeed READ ExternalSpeed WRITE setExternalSpeed NOTIFY ExternalSpeedChanged)


    //Q_PROPERTY(qreal supportedReg READ supportedReg WRITE setsupportedReg NOTIFY supportedRegChanged)
public:
    DashBoard(QObject *parent = 0);

    // Odometer
    void setOdo(const qreal &Odo);
    //Tripmeter
    Q_INVOKABLE void setTrip(const qreal &Trip);
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
    void setInjDuty2(const qreal &InjDuty2);
    void setInjAngle(const qreal &InjAngle);

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
    void setFlag17(const qreal &Flag17);
    void setFlag18(const qreal &Flag18);
    void setFlag19(const qreal &Flag19);
    void setFlag20(const qreal &Flag20);
    void setFlag21(const qreal &Flag21);
    void setFlag22(const qreal &Flag22);
    void setFlag23(const qreal &Flag23);
    void setFlag24(const qreal &Flag24);
    void setFlag25(const qreal &Flag25);

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
    void setgpsAltitude(const double &gpsAltitude);
    void setgpsLatitude(const double &gpsLatitude);
    void setgpsLongitude(const double &gpsLongitude);
    void setgpsSpeed(const double &gpsSpeed);
    void setgpsVisibleSatelites(const int &gpsVisibleSatelites);
    void setgpsFIXtype(const QString &gpsFIXtype);
    void setgpsbaering(const qreal &gpsbaering);

    // Units
    void setunits(const QString &units);
    void setspeedunits(const QString &speedunits);
    void setpressureunits(const QString &pressureunits);






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

    void setmaindashsetup(const QStringList &maindashsetup);
    void setdashsetup3(const QStringList &dashsetup3);
    void setdashsetup2(const QStringList &dashsetup2);
    void setdashsetup1(const QStringList &dashsetup1);

    void setdashfiles(const QStringList &dashfiles);


    void setaccelpedpos(const qreal &accelpedpos);
    void setairtempensor2(const qreal &airtempensor2);
    void setantilaglauchswitch(const qreal &antilaglauchswitch);
    void setantilaglaunchon(const qreal &antilaglaunchon);
    void setauxrevlimitswitch(const qreal &auxrevlimitswitch);
    void setavfueleconomy(const qreal &avfueleconomy);
    void setbattlight(const qreal &battlight);
    void setboostcontrol(const qreal &boostcontrol);
    void setbrakepress(const qreal &brakepress);
    void setclutchswitchstate(const qreal &clutchswitchstate);
    void setcoolantpress(const qreal &coolantpress);
    void setdecelcut(const qreal &decelcut);
    void setdiffoiltemp(const qreal &diffoiltemp);
    void setdistancetoempty(const qreal &distancetoempty);
    void setegt1(const qreal &egt1);
    void setegt2(const qreal &egt2);
    void setegt3(const qreal &egt3);
    void setegt4(const qreal &egt4);
    void setegt5(const qreal &egt5);
    void setegt6(const qreal &egt6);
    void setegt7(const qreal &egt7);
    void setegt8(const qreal &egt8);
    void setegt9(const qreal &egt9);
    void setegt10(const qreal &egt10);
    void setegt11(const qreal &egt11);
    void setegt12(const qreal &egt12);
    void setexcamangle1(const qreal &excamangle1);
    void setexcamangle2(const qreal &excamangle2);
    void setflatshiftstate(const qreal &flatshiftstate);
    void setfuelclevel(const qreal &fuelclevel);
    void setfuelcomposition(const qreal &fuelcomposition);
    void setfuelconsrate(const qreal &fuelconsrate);
    void setfuelcutperc(const qreal &fuelcutperc);
    void setfuelflow(const qreal &fuelflow);
    void setfuelflowdiff(const qreal &fuelflowdiff);
    void setfuelflowret(const qreal &fuelflowret);
    void setfueltrimlongtbank1(const qreal &fueltrimlongtbank1);
    void setfueltrimlongtbank2(const qreal &fueltrimlongtbank2);
    void setfueltrimshorttbank1(const qreal &fueltrimshorttbank1);
    void setfueltrimshorttbank2(const qreal &fueltrimshorttbank2);
    void setgearswitch(const qreal &gearswitch);
    void sethandbrake(const qreal &handbrake);
    void sethighbeam(const qreal &highbeam);
    void sethomeccounter(const qreal &homeccounter);
    void setincamangle1(const qreal &incamangle1);
    void setincamangle2(const qreal &incamangle2);
    void setknocklevlogged1(const qreal &knocklevlogged1);
    void setknocklevlogged2(const qreal &knocklevlogged2);
    void setknockretardbank1(const qreal &knockretardbank1);
    void setknockretardbank2(const qreal &knockretardbank2);
    void setlambda2(const qreal &lambda2);
    void setlambda3(const qreal &lambda3);
    void setlambda4(const qreal &lambda4);
    void setlaunchcontolfuelenrich(const qreal &launchcontolfuelenrich);
    void setlaunchctrolignretard(const qreal &launchctrolignretard);
    void setleftindicator(const qreal &leftindicator);
    void setlimpmode(const qreal &limpmode);
    void setmil(const qreal &mil);
    void setmissccount(const qreal &missccount);
    void setnosactive(const qreal &nosactive);
    void setnospress(const qreal &nospress);
    void setnosswitch(const qreal &nosswitch);
    void setoilpres(const qreal &oilpres);
    void setoiltemp(const qreal &oiltemp);
    void setrallyantilagswitch(const qreal &rallyantilagswitch);
    void setrightindicator(const qreal &rightindicator);
    void settargetbstlelkpa(const qreal &targetbstlelkpa);
    void settimeddutyout1(const qreal &timeddutyout1);
    void settimeddutyout2(const qreal &timeddutyout2);
    void settimeddutyoutputactive(const qreal &timeddutyoutputactive);
    void settorqueredcutactive(const qreal &torqueredcutactive);
    void settorqueredlevelactive(const qreal &torqueredlevelactive);
    void settransientthroactive(const qreal &transientthroactive);
    void settransoiltemp(const qreal &transoiltemp);
    void settriggerccounter(const qreal &triggerccounter);
    void settriggersrsinceasthome(const qreal &triggersrsinceasthome);
    void setturborpm(const qreal &turborpm);
    void setwastegatepress(const qreal &wastegatepress);
    void setwheeldiff(const qreal &wheeldiff);
    void setwheelslip(const qreal &wheelslip);
    void setwheelspdftleft(const qreal &wheelspdftleft);
    void setwheelspdftright(const qreal &wheelspdftright);
    void setwheelspdrearleft(const qreal &wheelspdrearleft);
    void setwheelspdrearright(const qreal &wheelspdrearright);
    void setmusicpath(const QString &musicpath);

    void setsupportedReg(const int &supportedReg);
    Q_INVOKABLE void setecu(const int &ecu);

    void setrpmstyle1(const int &rpmstyle1);
    void setrpmstyle2(const int &rpmstyle2);
    void setrpmstyle3(const int &rpmstyle3);
    void setError(const QString &Error);
    Q_INVOKABLE void setExternalSpeed(const int &ExternalSpeed);
    Q_INVOKABLE void setspeedpercent(const qreal &speedpercent);

    Q_INVOKABLE void setmaxRPM(const int &maxRPM);
    Q_INVOKABLE void setrpmStage1(const int &rpmStage1);
    Q_INVOKABLE void setrpmStage2(const int &rpmStage2);
    Q_INVOKABLE void setrpmStage3(const int &rpmStage3);
    Q_INVOKABLE void setrpmStage4(const int &rpmStage4);
    Q_INVOKABLE void setwaterwarn(const int &waterwarn);
    Q_INVOKABLE void setrpmwarn(const int &rpmwarn);
    Q_INVOKABLE void setknockwarn(const int &knockwarn);
    Q_INVOKABLE void setboostwarn(const qreal &boostwarn);
    Q_INVOKABLE void setsmoothrpm(const int &smoothrpm);
    Q_INVOKABLE void setsmoothspeed(const int &smoothspeed);

    Q_INVOKABLE void setgearcalc1(const int &gearcalc1);
    Q_INVOKABLE void setgearcalc2(const int &gearcalc2);
    Q_INVOKABLE void setgearcalc3(const int &gearcalc3);
    Q_INVOKABLE void setgearcalc4(const int &gearcalc4);
    Q_INVOKABLE void setgearcalc5(const int &gearcalc5);
    Q_INVOKABLE void setgearcalc6(const int &gearcalc6);

   Q_INVOKABLE void setgearcalcactivation(const int &gearcalcactivation);



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
    qreal InjDuty2() const;
    qreal InjAngle() const;
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
    qreal Flag17() const;
    qreal Flag18() const;
    qreal Flag19() const;
    qreal Flag20() const;
    qreal Flag21() const;
    qreal Flag22() const;
    qreal Flag23() const;
    qreal Flag24() const;
    qreal Flag25() const;

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
    double gpsAltitude() const;
    double gpsLatitude() const;
    double gpsLongitude() const;
    double gpsSpeed() const;
    int gpsVisibleSatelites() const;
    QString gpsFIXtype() const;
    qreal gpsbaering() const;

    //units
    QString units() const;
    QString speedunits()const;
    QString pressureunits() const;



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
    QStringList maindashsetup() const;
    QStringList dashsetup3() const;
    QStringList dashsetup2() const;
    QStringList dashsetup1() const;

    QStringList dashfiles() const;

    qreal accelpedpos() const;
    qreal airtempensor2() const;
    qreal antilaglauchswitch() const;
    qreal antilaglaunchon() const;
    qreal auxrevlimitswitch() const;
    qreal avfueleconomy() const;
    qreal battlight() const;
    qreal boostcontrol() const;
    qreal brakepress() const;
    qreal clutchswitchstate() const;
    qreal coolantpress() const;
    qreal decelcut() const;
    qreal diffoiltemp() const;
    qreal distancetoempty() const;
    qreal egt1() const;
    qreal egt2() const;
    qreal egt3() const;
    qreal egt4() const;
    qreal egt5() const;
    qreal egt6() const;
    qreal egt7() const;
    qreal egt8() const;
    qreal egt9() const;
    qreal egt10() const;
    qreal egt11() const;
    qreal egt12() const;
    qreal excamangle1() const;
    qreal excamangle2() const;
    qreal flatshiftstate() const;
    qreal fuelclevel() const;
    qreal fuelcomposition() const;
    qreal fuelconsrate() const;
    qreal fuelcutperc() const;
    qreal fuelflow() const;
    qreal fuelflowdiff() const;
    qreal fuelflowret() const;
    qreal fueltrimlongtbank1() const;
    qreal fueltrimlongtbank2() const;
    qreal fueltrimshorttbank1() const;
    qreal fueltrimshorttbank2() const;
    qreal gearswitch() const;
    qreal handbrake() const;
    qreal highbeam() const;
    qreal homeccounter() const;
    qreal incamangle1() const;
    qreal incamangle2() const;
    qreal knocklevlogged1() const;
    qreal knocklevlogged2() const;
    qreal knockretardbank1() const;
    qreal knockretardbank2() const;
    qreal lambda2() const;
    qreal lambda3() const;
    qreal lambda4() const;
    qreal launchcontolfuelenrich() const;
    qreal launchctrolignretard() const;
    qreal leftindicator() const;
    qreal limpmode() const;
    qreal mil() const;
    qreal missccount() const;
    qreal nosactive() const;
    qreal nospress() const;
    qreal nosswitch() const;
    qreal oilpres() const;
    qreal oiltemp() const;
    qreal rallyantilagswitch() const;
    qreal rightindicator() const;
    qreal targetbstlelkpa() const;
    qreal timeddutyout1() const;
    qreal timeddutyout2() const;
    qreal timeddutyoutputactive() const;
    qreal torqueredcutactive() const;
    qreal torqueredlevelactive() const;
    qreal transientthroactive() const;
    qreal transoiltemp() const;
    qreal triggerccounter() const;
    qreal triggersrsinceasthome() const;
    qreal turborpm() const;
    qreal wastegatepress() const;
    qreal wheeldiff() const;
    qreal wheelslip() const;
    qreal wheelspdftleft() const;
    qreal wheelspdftright() const;
    qreal wheelspdrearleft() const;
    qreal wheelspdrearright() const;
    QString musicpath() const;

    int supportedReg() const;
    qreal speedpercent() const;

    int maxRPM() const;
    int rpmStage1() const;
    int rpmStage2() const;
    int rpmStage3() const;
    int rpmStage4() const;

    int waterwarn() const;
    int rpmwarn() const;
    int knockwarn() const;
    qreal boostwarn() const;
    int smoothrpm() const;
    int smoothspeed() const;

    int gearcalc1() const;
    int gearcalc2() const;
    int gearcalc3() const;
    int gearcalc4() const;
    int gearcalc5() const;
    int gearcalc6() const;
    int gearcalcactivation() const;
    int ecu() const;
    int rpmstyle1() const;
    int rpmstyle2() const;
    int rpmstyle3() const;
    QString Error() const;
    int ExternalSpeed() const;

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
    void injDuty2Changed(qreal InjDuty2);
    void InjAngleChanged(qreal InjAngle);
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
    void flag17Changed(qreal Flag17);
    void flag18Changed(qreal Flag18);
    void flag19Changed(qreal Flag19);
    void flag20Changed(qreal Flag20);
    void flag21Changed(qreal Flag21);
    void flag22Changed(qreal Flag22);
    void flag23Changed(qreal Flag23);
    void flag24Changed(qreal Flag24);
    void flag25Changed(qreal Flag25);
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
    void gpsAltitudeChanged(double gpsAltitude);
    void gpsLatitudeChanged(double gpsLatitude);
    void gpsLongitudeChanged(double gpsLongitude);
    void gpsSpeedChanged(double gpsSpeed);
    void gpsVisibleSatelitesChanged(int gpsVisibleSatelites);
    void gpsFIXtypeChanged(QString gpsFIXtype);
    void gpsbaeringChanged(qreal gpsbaering);

    // units

    void unitsChanged(QString units);
    void speedunitsChanged(QString speedunits);
    void pressureunitsChanged(QString pressureunits);

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

    void maindashsetupChanged(QStringList maindashsetup);
    void dashsetup3Changed(QStringList dashsetup3);
    void dashsetup2Changed(QStringList dashsetup2);
    void dashsetup1Changed(QStringList dashsetup1);
    void dashfilesChanged(QStringList dashfiles);



    void accelpedposChanged(qreal accelpedpos);
    void airtempensor2Changed(qreal airtempensor2);
    void antilaglauchswitchChanged(qreal antilaglauchswitch);
    void antilaglaunchonChanged(qreal antilaglaunchon);
    void auxrevlimitswitchChanged(qreal auxrevlimitswitch);
    void avfueleconomyChanged(qreal avfueleconomy);
    void battlightChanged(qreal battlight);
    void boostcontrolChanged(qreal boostcontrol);
    void brakepressChanged(qreal brakepress);
    void clutchswitchstateChanged(qreal clutchswitchstate);
    void coolantpressChanged(qreal coolantpress);
    void decelcutChanged(qreal decelcut);
    void diffoiltempChanged(qreal diffoiltemp);
    void distancetoemptyChanged(qreal distancetoempty);
    void egt1Changed(qreal egt1);
    void egt2Changed(qreal egt2);
    void egt3Changed(qreal egt3);
    void egt4Changed(qreal egt4);
    void egt5Changed(qreal egt5);
    void egt6Changed(qreal egt6);
    void egt7Changed(qreal egt7);
    void egt8Changed(qreal egt8);
    void egt9Changed(qreal egt9);
    void egt10Changed(qreal egt10);
    void egt11Changed(qreal egt11);
    void egt12Changed(qreal egt12);
    void excamangle1Changed(qreal excamangle1);
    void excamangle2Changed(qreal excamangle2);
    void flatshiftstateChanged(qreal flatshiftstate);
    void fuelclevelChanged(qreal fuelclevel);
    void fuelcompositionChanged(qreal fuelcomposition);
    void fuelconsrateChanged(qreal fuelconsrate);
    void fuelcutpercChanged(qreal fuelcutperc);
    void fuelflowChanged(qreal fuelflow);
    void fuelflowdiffChanged(qreal fuelflowdiff);
    void fuelflowretChanged(qreal fuelflowret);
    void fueltrimlongtbank1Changed(qreal fueltrimlongtbank1);
    void fueltrimlongtbank2Changed(qreal fueltrimlongtbank2);
    void fueltrimshorttbank1Changed(qreal fueltrimshorttbank1);
    void fueltrimshorttbank2Changed(qreal fueltrimshorttbank2);
    void gearswitchChanged(qreal gearswitch);
    void handbrakeChanged(qreal handbrake);
    void highbeamChanged(qreal highbeam);
    void homeccounterChanged(qreal homeccounter);
    void incamangle1Changed(qreal incamangle1);
    void incamangle2Changed(qreal incamangle2);
    void knocklevlogged1Changed(qreal knocklevlogged1);
    void knocklevlogged2Changed(qreal knocklevlogged2);
    void knockretardbank1Changed(qreal knockretardbank1);
    void knockretardbank2Changed(qreal knockretardbank2);
    void lambda2Changed(qreal lambda2);
    void lambda3Changed(qreal lambda3);
    void lambda4Changed(qreal lambda4);
    void launchcontolfuelenrichChanged(qreal launchcontolfuelenrich);
    void launchctrolignretardChanged(qreal launchctrolignretard);
    void leftindicatorChanged(qreal leftindicator);
    void limpmodeChanged(qreal limpmode);
    void milChanged(qreal mil);
    void missccountChanged(qreal missccount);
    void nosactiveChanged(qreal nosactive);
    void nospressChanged(qreal nospress);
    void nosswitchChanged(qreal nosswitch);
    void oilpresChanged(qreal oilpres);
    void oiltempChanged(qreal oiltemp);
    void rallyantilagswitchChanged(qreal rallyantilagswitch);
    void rightindicatorChanged(qreal rightindicator);
    void targetbstlelkpaChanged(qreal targetbstlelkpa);
    void timeddutyout1Changed(qreal timeddutyout1);
    void timeddutyout2Changed(qreal timeddutyout2);
    void timeddutyoutputactiveChanged(qreal timeddutyoutputactive);
    void torqueredcutactiveChanged(qreal torqueredcutactive);
    void torqueredlevelactiveChanged(qreal torqueredlevelactive);
    void transientthroactiveChanged(qreal transientthroactive);
    void transoiltempChanged(qreal transoiltemp);
    void triggerccounterChanged(qreal triggerccounter);
    void triggersrsinceasthomeChanged(qreal triggersrsinceasthome);
    void turborpmChanged(qreal turborpm);
    void wastegatepressChanged(qreal wastegatepress);
    void wheeldiffChanged(qreal wheeldiff);
    void wheelslipChanged(qreal wheelslip);
    void wheelspdftleftChanged(qreal wheelspdftleft);
    void wheelspdftrightChanged(qreal wheelspdftright);
    void wheelspdrearleftChanged(qreal wheelspdrearleft);
    void wheelspdrearrightChanged(qreal wheelspdrearright);
    void musicpathChanged(QString musicpath);
    void supportedRegChanged(int supportedReg);
    void speedpercentChanged(qreal speedpercent);
    void maxRPMChanged (int maxRPM);
    void rpmStage1Changed(int rpmStage1);
    void rpmStage2Changed(int rpmStage2);
    void rpmStage3Changed(int rpmStage3);
    void rpmStage4Changed(int rpmStage4);
    void waterwarnChanged (int waterwarn);
    void rpmwarnChanged (int rpmwarn);
    void knockwarnChanged (int knockwarn);
    void boostwarnChanged(qreal boostwarn);
    void smoothrpmChanged (int smoothrpm);
    void smoothspeedChanged (int smoothspeed);
    void gearcalc1Changed (int gearcalc1);
    void gearcalc2Changed (int gearcalc2);
    void gearcalc3Changed (int gearcalc3);
    void gearcalc4Changed (int gearcalc4);
    void gearcalc5Changed (int gearcalc5);
    void gearcalc6Changed (int gearcalc6);
    void gearcalcactivationChanged (int gearcalcactivation);
    void ecuChanged(int ecu);
    void rpmstyle1Changed(int rpmstyle1);
    void rpmstyle2Changed(int rpmstyle2);
    void rpmstyle3Changed(int rpmstyle3);
    void ErrorChanged(QString Error);
    void ExternalSpeedChanged(int ExternalSpeed);


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
    qreal m_InjDuty2;
    qreal m_InjAngle;
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
    qreal m_Flag17;
    qreal m_Flag18;
    qreal m_Flag19;
    qreal m_Flag20;
    qreal m_Flag21;
    qreal m_Flag22;
    qreal m_Flag23;
    qreal m_Flag24;
    qreal m_Flag25;

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
    double m_gpsAltitude;
    double m_gpsLatitude;
    double m_gpsLongitude;
    double m_gpsSpeed;
    int m_gpsVisibleSatelites;
    QString m_gpsFIXtype;
    qreal m_gpsbaering;

    //Units

    QString m_units;
    QString m_speedunits;
    QString m_pressureunits;

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
    QStringList m_maindashsetup;
    QStringList m_dashsetup3;
    QStringList m_dashsetup2;
    QStringList m_dashsetup1;

    QStringList m_dashfiles;

    qreal m_accelpedpos;
    qreal m_airtempensor2;
    qreal m_antilaglauchswitch;
    qreal m_antilaglaunchon;
    qreal m_auxrevlimitswitch;
    qreal m_avfueleconomy;
    qreal m_battlight;
    qreal m_boostcontrol;
    qreal m_brakepress;
    qreal m_clutchswitchstate;
    qreal m_coolantpress;
    qreal m_decelcut;
    qreal m_diffoiltemp;
    qreal m_distancetoempty;
    qreal m_egt1;
    qreal m_egt2;
    qreal m_egt3;
    qreal m_egt4;
    qreal m_egt5;
    qreal m_egt6;
    qreal m_egt7;
    qreal m_egt8;
    qreal m_egt9;
    qreal m_egt10;
    qreal m_egt11;
    qreal m_egt12;
    qreal m_excamangle1;
    qreal m_excamangle2;
    qreal m_flatshiftstate;
    qreal m_fuelclevel;
    qreal m_fuelcomposition;
    qreal m_fuelconsrate;
    qreal m_fuelcutperc;
    qreal m_fuelflowdiff;
    qreal m_fuelflowret;
    qreal m_fueltrimlongtbank1;
    qreal m_fuelflow;
    qreal m_fueltrimlongtbank2;
    qreal m_fueltrimshorttbank1;
    qreal m_fueltrimshorttbank2;
    qreal m_gearswitch;
    qreal m_handbrake;
    qreal m_highbeam;
    qreal m_homeccounter;
    qreal m_incamangle1;
    qreal m_incamangle2;
    qreal m_knocklevlogged1;
    qreal m_knocklevlogged2;
    qreal m_knockretardbank1;
    qreal m_knockretardbank2;
    qreal m_lambda2;
    qreal m_lambda3;
    qreal m_lambda4;
    qreal m_launchcontolfuelenrich;
    qreal m_launchctrolignretard;
    qreal m_leftindicator;
    qreal m_limpmode;
    qreal m_mil;
    qreal m_missccount;
    qreal m_nosactive;
    qreal m_nospress;
    qreal m_nosswitch;
    qreal m_oilpres;
    qreal m_oiltemp;
    qreal m_rallyantilagswitch;
    qreal m_rightindicator;
    qreal m_targetbstlelkpa;
    qreal m_timeddutyout1;
    qreal m_timeddutyout2;
    qreal m_timeddutyoutputactive;
    qreal m_torqueredcutactive;
    qreal m_torqueredlevelactive;
    qreal m_transientthroactive;
    qreal m_transoiltemp;
    qreal m_triggerccounter;
    qreal m_triggersrsinceasthome;
    qreal m_turborpm;
    qreal m_wastegatepress;
    qreal m_wheeldiff;
    qreal m_wheelslip;
    qreal m_wheelspdftleft;
    qreal m_wheelspdftright;
    qreal m_wheelspdrearleft;
    qreal m_wheelspdrearright;

    QString m_musicpath;
    int m_supportedReg;
    qreal m_speedpercent;

    int m_maxRPM;
    int m_rpmStage1;
    int m_rpmStage2;
    int m_rpmStage3;
    int m_rpmStage4;

    int m_waterwarn;
    int m_rpmwarn;
    int m_knockwarn;
    qreal m_boostwarn;
    int m_smoothrpm;
    int m_smoothspeed;
    int m_gearcalc1;
    int m_gearcalc2;
    int m_gearcalc3;
    int m_gearcalc4;
    int m_gearcalc5;
    int m_gearcalc6;
    int m_gearcalcactivation;

    int m_ecu;
    int m_rpmstyle1;
    int m_rpmstyle2;
    int m_rpmstyle3;
    QString m_Error;
    int m_ExternalSpeed;
};

#endif // DASHBOARD_H
