#include <dashboard.h>
#include <QStringList>
#include <QDebug>
#include <QVector>
#include "math.h"

////



QVector<int>averageSpeed(0);
QVector<int>averageRPM(0);
QVector<qreal>averageexanaloginput7(0);
int avgspeed;
int avgrpm;
qreal avgexanaloginput7;
qreal R2 = 1430; // R2 is always Fixed ( Two resistors in line 1100 + 330 Ohms
qreal R3 = 100;     // R2 is always Fixed ( Two resistors in line 1100 + 330 Ohms
qreal R4 = 1000; // R2 is always Fixed ( Two resistors in line 1100 + 330 Ohms
qreal AN0R3 = 0;
qreal AN1R3 = 0;
qreal AN2R3 = 0;
qreal AN0R4 = 0;
qreal AN1R4 = 0;
qreal AN2R4 = 0;
qreal Rtotalexan0; // Resistance of all internal Resistors of the EX Board for AN0
qreal Rtotalexan1; // Resistance of all internal Resistors of the EX Board for AN1
qreal Rtotalexan2; // Resistance of all internal Resistors of the EX Board for AN2
qreal AN00;
qreal AN05;
qreal AN10;
qreal AN15;
qreal AN20;
qreal AN25;
qreal AN30;
qreal AN35;
qreal AN40;
qreal AN45;
qreal AN50;
qreal AN55;
qreal AN60;
qreal AN65;
qreal AN70;
qreal AN75;
qreal AN80;
qreal AN85;
qreal AN90;
qreal AN95;
qreal AN100;
qreal AN105;
// Ex Board Analog
qreal EXAN00;
qreal EXAN05;
qreal EXAN10;
qreal EXAN15;
qreal EXAN20;
qreal EXAN25;
qreal EXAN30;
qreal EXAN35;
qreal EXAN40;
qreal EXAN45;
qreal EXAN50;
qreal EXAN55;
qreal EXAN60;
qreal EXAN65;
qreal EXAN70;
qreal EXAN75;
qreal ResistanceEXAN0;
qreal ResistanceEXAN1;
qreal ResistanceEXAN2;
int EXsteinhart0; //Flag to use Steinhart/hart for Analog input 0
int EXsteinhart1; //Flag to use Steinhart/hart for Analog input 1
int EXsteinhart2; //Flag to use Steinhart/hart for Analog input 2


qreal lamdamultiplicator = 1;
int brightness;




DashBoard::DashBoard(QObject *parent)
    : QObject(parent)

    , m_Odo(0)
    , m_Trip(0)
    , m_rpm(0)
    , m_Intakepress(0)
    , m_PressureV(0)
    , m_ThrottleV(0)
    , m_Primaryinp(0)
    , m_Fuelc(0)
    , m_Leadingign(0)
    , m_Trailingign(0)
    , m_Fueltemp(0)
    , m_Moilp(0)
    , m_Boosttp(0)
    , m_Boostwg(0)
    , m_Watertemp(0)
    , m_Intaketemp(0)
    , m_Knock(0)
    , m_BatteryV(0)
    , m_speed(0)
    , m_Iscvduty(0)
    , m_O2volt(0)
    , m_na1(0)
    , m_Secinjpulse(0)
    , m_na2(0)
    , m_InjDuty(0)
    , m_InjDuty2(0)
    , m_InjAngle(0)
    , m_EngLoad(0)
    , m_MAF1V(0)
    , m_MAF2V(0)
    , m_injms(0)
    , m_Inj(0)
    , m_Ign(0)
    , m_Dwell(0)
    , m_BoostPres(0)
    , m_BoostPreskpa(0)
    , m_BoostDuty(0)
    , m_MAFactivity(0)
    , m_O2volt_2(0)
    , m_Cyl1_O2_Corr(0)
    , m_Cyl2_O2_Corr(0)
    , m_Cyl3_O2_Corr(0)
    , m_Cyl4_O2_Corr(0)
    , m_Cyl5_O2_Corr(0)
    , m_Cyl6_O2_Corr(0)
    , m_Cyl7_O2_Corr(0)
    , m_Cyl8_O2_Corr(0)

    //Boost


    , m_pim(0)

    //Aux Inputs
    , m_auxcalc1(0.00)
    , m_auxcalc2(0.00)
    , m_auxcalc3(0.00)
    , m_auxcalc4(0.00)

    // Sensor Info FD3S
    , m_sens1(0.00)
    , m_sens2(0.00)
    , m_sens3(0.00)
    , m_sens4(0.00)
    , m_sens5(0.00)
    , m_sens6(0.00)
    , m_sens7(0.00)
    , m_sens8(0.00)

    //Flag Strings

    , m_FlagString1 ("F-1")
    , m_FlagString2 ("F-2")
    , m_FlagString3 ("F-3")
    , m_FlagString4 ("F-4")
    , m_FlagString5 ("F-5")
    , m_FlagString6 ("F-6")
    , m_FlagString7 ("F-7")
    , m_FlagString8 ("F-8")
    , m_FlagString9 ("F-9")
    , m_FlagString10 ("F10")
    , m_FlagString11 ("F11")
    , m_FlagString12 ("F12")
    , m_FlagString13 ("F13")
    , m_FlagString14 ("F14")
    , m_FlagString15 ("F15")
    , m_FlagString16 ("F16")

    //Sensor Srings

    , m_SensorString1 ("SEN1")
    , m_SensorString2 ("SEN2")
    , m_SensorString3 ("SEN3")
    , m_SensorString4 ("SEN4")
    , m_SensorString5 ("SEN5")
    , m_SensorString6 ("SEN6")
    , m_SensorString7 ("SEN7")
    , m_SensorString8 ("SEN8")



    //Bit Flags for Sensors
    , m_Flag1(0)
    , m_Flag2(0)
    , m_Flag3(0)
    , m_Flag4(0)
    , m_Flag5(0)
    , m_Flag6(0)
    , m_Flag7(0)
    , m_Flag8(0)
    , m_Flag9(0)
    , m_Flag10(0)
    , m_Flag11(0)
    , m_Flag12(0)
    , m_Flag13(0)
    , m_Flag14(0)
    , m_Flag15(0)
    , m_Flag16(0)
    , m_Flag17(0)
    , m_Flag18(0)
    , m_Flag19(0)
    , m_Flag20(0)
    , m_Flag21(0)
    , m_Flag22(0)
    , m_Flag23(0)
    , m_Flag24(0)
    , m_Flag25(0)


    //Adaptronic extra
    , m_MAP(0)
    , m_MAP2(0)
    , m_PANVAC(0)
    , m_AUXT(0)
    , m_AFR(0)
    , m_AFRLEFTBANKTARGET(0)
    , m_AFRRIGHTBANKTARGET(0)
    //

    , m_AFRLEFTBANKACTUAL(0)
    , m_AFRRIGHTBANKACTUAL(0)
    , m_BOOSTOFFSET(0)
    , m_REVLIM3STEP(0)
    , m_REVLIM2STEP(0)
    , m_REVLIMGIGHSIDE(0)
    , m_REVLIMBOURNOUT(0)
    , m_LEFTBANKO2CORR(0)
    , m_RIGHTBANKO2CORR(0)
    , m_TRACTIONCTRLOFFSET(0)
    , m_DRIVESHAFTOFFSET(0)
    , m_TCCOMMAND(0)
    , m_FSLCOMMAND(0)
    , m_FSLINDEX(0)
    , m_AFRcyl1(0)
    , m_AFRcyl2(0)
    , m_AFRcyl3(0)
    , m_AFRcyl4(0)
    , m_AFRcyl5(0)
    , m_AFRcyl6(0)
    , m_AFRcyl7(0)
    , m_AFRcyl8(0)
    , m_TPS(0)
    , m_IdleValue(0)
    , m_MVSS(0)
    , m_SVSS(0)
    , m_Inj1(0)
    , m_Inj2(0)
    , m_Inj3(0)
    , m_Inj4(0)
    , m_Ign1(0)
    , m_Ign2(0)
    , m_Ign3(0)
    , m_Ign4(0)
    , m_TRIM(0)
    , m_LAMBDA(0)
    , m_LAMBDATarget(0)
    , m_FuelPress(0)
    , m_GearOilPress(0)

    //GPS Strings
    , m_gpsTime ("0")
    , m_gpsAltitude (0)
    , m_gpsLatitude (0)
    , m_gpsLongitude (0)
    , m_gpsSpeed (0)
    , m_gpsVisibleSatelites (0)
    , m_gpsFIXtype ("no connection")
    , m_gpsbaering (0)


    //units
    , m_units("unit")
    , m_speedunits("unit")
    , m_pressureunits("unit")

    //Sensors
    , m_accelx(0)
    , m_accely(0)
    , m_accelz(0)
    , m_gyrox(0)
    , m_gyroy(0)
    , m_gyroz(0)
    , m_compass(0)
    , m_ambitemp(0)
    , m_ambipress(0)

    //   ,m_TimeoutStat("----")
    //   ,m_RecvData("----")
    //calculations
    , m_Gear(0)
    , m_Gearoffset(0)
    , m_GearCalculation(0)
    , m_Power(0)
    , m_Torque(0)
    , m_AccelTimer(0)
    , m_Weight(0)

    //Official Pi screen present screen
    , m_screen(0)

    ,  m_accelpedpos(0)
    ,  m_airtempensor2(0)
    ,  m_antilaglauchswitch(0)
    ,  m_antilaglaunchon(0)
    ,  m_auxrevlimitswitch(0)
    ,  m_avfueleconomy(0)
    ,  m_battlight(0)
    ,  m_boostcontrol(0)
    ,  m_brakepress(0)
    ,  m_clutchswitchstate(0)
    ,  m_coolantpress(0)
    ,  m_decelcut(0)
    ,  m_diffoiltemp(0)
    ,  m_distancetoempty(0)
    ,  m_egt1(0)
    ,  m_egt2(0)
    ,  m_egt3(0)
    ,  m_egt4(0)
    ,  m_egt5(0)
    ,  m_egt6(0)
    ,  m_egt7(0)
    ,  m_egt8(0)
    ,  m_egt9(0)
    ,  m_egt10(0)
    ,  m_egt11(0)
    ,  m_egt12(0)
    ,  m_excamangle1(0)
    ,  m_excamangle2(0)
    ,  m_flatshiftstate(0)
    ,  m_fuelclevel(0)
    ,  m_fuelcomposition(0)
    ,  m_fuelconsrate(0)
    ,  m_fuelcutperc(0)
    ,  m_fuelflowdiff(0)
    ,  m_fuelflowret(0)
    ,  m_fueltrimlongtbank1(0)
    ,  m_fuelflow(0)
    ,  m_fueltrimlongtbank2(0)
    ,  m_fueltrimshorttbank1(0)
    ,  m_fueltrimshorttbank2(0)
    ,  m_gearswitch(0)
    ,  m_handbrake(0)
    ,  m_highbeam(0)
    ,  m_lowBeam(0)
    ,  m_tractionControl(0)
    ,  m_homeccounter(0)
    ,  m_incamangle1(0)
    ,  m_incamangle2(0)
    ,  m_knocklevlogged1(0)
    ,  m_knocklevlogged2(0)
    ,  m_knockretardbank1(0)
    ,  m_knockretardbank2(0)
    ,  m_lambda2(0)
    ,  m_lambda3(0)
    ,  m_lambda4(0)
    ,  m_launchcontolfuelenrich(0)
    ,  m_launchctrolignretard(0)
    ,  m_leftindicator(0)
    ,  m_limpmode(0)
    ,  m_mil(0)
    ,  m_missccount(0)
    ,  m_nosactive(0)
    ,  m_nospress(0)
    ,  m_nosswitch(0)
    ,  m_oilpres(0)
    ,  m_oiltemp(0)
    ,  m_rallyantilagswitch(0)
    ,  m_rightindicator(0)
    ,  m_targetbstlelkpa(0)
    ,  m_timeddutyout1(0)
    ,  m_timeddutyout2(0)
    ,  m_timeddutyoutputactive(0)
    ,  m_torqueredcutactive(0)
    ,  m_torqueredlevelactive(0)
    ,  m_transientthroactive(0)
    ,  m_transoiltemp(0)
    ,  m_triggerccounter(0)
    ,  m_triggersrsinceasthome(0)
    ,  m_turborpm(0)
    ,  m_turborpm2(0)
    ,  m_wastegatepress(0)
    ,  m_wheeldiff(0)
    ,  m_wheelslip(0)
    ,  m_wheelspdftleft(0)
    ,  m_wheelspdftright(0)
    ,  m_wheelspdrearleft(0)
    ,  m_wheelspdrearright(0)
    ,  m_speedpercent(1)
    ,  m_maxRPM(8000)
    ,  m_rpmStage1(3000)
    ,  m_rpmStage2(4000)
    ,  m_rpmStage3(6000)
    ,  m_rpmStage4(7000)
    ,  m_waterwarn(999)
    ,  m_rpmwarn(9999)
    ,  m_knockwarn(999)
    ,  m_boostwarn(999)
    ,  m_smoothrpm(0)
    ,  m_smoothspeed(0)
    ,  m_smoothexAnalogInput7(0)
    ,  m_gearcalc1(0)
    ,  m_gearcalc2(0)
    ,  m_gearcalc3(0)
    ,  m_gearcalc4(0)
    ,  m_gearcalc5(0)
    ,  m_gearcalc6(0)
    ,  m_gearcalcactivation(0)
    ,  m_ecu(0)
    ,  m_Error("")
    ,  m_autogear("")
    ,  m_ExternalSpeed(0)

    //laptimer

    ,  m_currentLap(0)
    ,  m_laptime("00:00.000")
    ,  m_Lastlaptime("00:00.000")
    ,  m_bestlaptime("00:00.000")
    ,  m_draggable(0)
    ,  m_wifi()
    ,  m_Analog0(0)
    ,  m_Analog1(0)
    ,  m_Analog2(0)
    ,  m_Analog3(0)
    ,  m_Analog4(0)
    ,  m_Analog5(0)
    ,  m_Analog6(0)
    ,  m_Analog7(0)
    ,  m_Analog8(0)
    ,  m_Analog9(0)
    ,  m_Analog10(0)
    ,  m_AnalogCalc0()
    ,  m_AnalogCalc1()
    ,  m_AnalogCalc2()
    ,  m_AnalogCalc3()
    ,  m_AnalogCalc4()
    ,  m_AnalogCalc5()
    ,  m_AnalogCalc6()
    ,  m_AnalogCalc7()
    ,  m_AnalogCalc8()
    ,  m_AnalogCalc9()
    ,  m_AnalogCalc10()
    ,  m_EXAnalogCalc0()
    ,  m_EXAnalogCalc1()
    ,  m_EXAnalogCalc2()
    ,  m_EXAnalogCalc3()
    ,  m_EXAnalogCalc4()
    ,  m_EXAnalogCalc5()
    ,  m_EXAnalogCalc6()
    ,  m_EXAnalogCalc7()
    ,  m_Lambdamultiply()
    ,  m_Userchannel1()
    ,  m_Userchannel2()
    ,  m_Userchannel3()
    ,  m_Userchannel4()
    ,  m_Userchannel5()
    ,  m_Userchannel6()
    ,  m_Userchannel7()
    ,  m_Userchannel8()
    ,  m_Userchannel9()
    ,  m_Userchannel10()
    ,  m_Userchannel11()
    ,  m_Userchannel12()
    ,  m_FuelLevel()
    ,  m_SteeringWheelAngle()
    ,  m_Brightness()
    ,  m_Visibledashes(1)
    ,  m_oilpressurelamp()
    ,  m_overtempalarm()
    ,  m_alternatorfail()
    ,  m_AuxTemp1()
//Quartermiletimer

    ,  m_sixtyfoottime()
    ,  m_sixtyfootspeed()
    ,  m_threehundredthirtyfoottime()
    ,  m_threehundredthirtyfootspeed()
    ,  m_eightmiletime()
    ,  m_eightmilespeed()
    ,  m_quartermiletime()
    ,  m_quartermilespeed()
    ,  m_thousandfoottime()
    ,  m_thousandfootspeed()
    ,  m_zerotohundredt()
    ,  m_hundredtotwohundredtime()
    ,  m_twohundredtothreehundredtime()
    ,  m_reactiontime()
    ,  m_IGBTPhaseATemp()
    ,  m_IGBTPhaseBTemp()
    ,  m_IGBTPhaseCTemp()
    ,  m_GateDriverTemp()
    ,  m_ControlBoardTemp()
    ,  m_RtdTemp1()
    ,  m_RtdTemp2()
    ,  m_RtdTemp3()
    ,  m_RtdTemp4()
    ,  m_RtdTemp5()
    ,  m_EMotorTemperature()
    ,  m_TorqueShudder()
    ,  m_DigInput1FowardSw()
    ,  m_DigInput2ReverseSw()
    ,  m_DigInput3BrakeSw()
    ,  m_DigInput4RegenDisableSw()
    ,  m_DigInput5IgnSw()
    ,  m_DigInput6StartSw()
    ,  m_DigInput7Bool()
    ,  m_DigInput8Bool()
    ,  m_EMotorAngle()
    ,  m_EMotorSpeed()
    ,  m_ElectricalOutFreq()
    ,  m_DeltaResolverFiltered()
    ,  m_PhaseACurrent()
    ,  m_PhaseBCurrent()
    ,  m_PhaseCCurrent()
    ,  m_DCBusCurrent()
    ,  m_DCBusVoltage()
    ,  m_OutputVoltage()
    ,  m_VABvdVoltage()
    ,  m_VBCvqVoltage()
    , m_TirepresLF()
    , m_TirepresRF()
    , m_TirepresRR()
    , m_TirepresLR()

    , m_TiretempLF()
    , m_TiretempRF()
    , m_TiretempRR()
    , m_TiretempLR()

    , m_DigitalInput1()
    , m_DigitalInput2()
    , m_DigitalInput3()
    , m_DigitalInput4()
    , m_DigitalInput5()
    , m_DigitalInput6()
    , m_DigitalInput7()

    //

    , m_igncut()
    , m_undrivenavgspeed()
    , m_drivenavgspeed()
    , m_dsettargetslip()
    , m_tractionctlpowerlimit()
    , m_knockallpeak()
    , m_knockcorr()
    , m_knocklastcyl()
    , m_totalfueltrim()
    , m_totaligncomp()
    , m_egthighest()
    , m_cputempecu()
    , m_errorcodecount()
    , m_lostsynccount()
    , m_egtdiff()
    , m_activeboosttable()
    , m_activetunetable()
    , m_genericoutput1()
    , m_CalibrationSelect()
{

}


// Odometer
void DashBoard::setOdo(const qreal &Odo)
{
    if (m_Odo == Odo)
        return;
    m_Odo = Odo;
    emit odoChanged(Odo);
}

// Tripmeter
void DashBoard::setTrip(const qreal &Trip)
{
    if (m_Trip == Trip)
        return;
    m_Trip = Trip;
    emit tripChanged(Trip);
}
void DashBoard::setAnalogVal(const qreal &A00,const qreal &A05,const qreal &A10,const qreal &A15,const qreal &A20,const qreal &A25,const qreal &A30,const qreal &A35,const qreal &A40,const qreal &A45,const qreal &A50,const qreal &A55,const qreal &A60,const qreal &A65,const qreal &A70,const qreal &A75,const qreal &A80,const qreal &A85,const qreal &A90,const qreal &A95,const qreal &A100,const qreal &A105)
{
    AN00 = A00;
    AN05 = A05;
    AN10 = A10;
    AN15 = A15;
    AN20 = A20;
    AN25 = A25;
    AN30 = A30;
    AN35 = A35;
    AN40 = A40;
    AN45 = A45;
    AN50 = A50;
    AN55 = A55;
    AN60 = A60;
    AN65 = A65;
    AN70 = A70;
    AN75 = A75;
    AN80 = A80;
    AN85 = A85;
    AN90 = A90;
    AN95 = A95;
    AN100 = A100;
    AN105 = A105;


    //qDebug()<< "AN75 " <<AN75;
}
void DashBoard::setEXAnalogVal(const qreal &EXA00,const qreal &EXA05,const qreal &EXA10,const qreal &EXA15,const qreal &EXA20,const qreal &EXA25,const qreal &EXA30,const qreal &EXA35,const qreal &EXA40,const qreal &EXA45,const qreal &EXA50,const qreal &EXA55,const qreal &EXA60,const qreal &EXA65,const qreal &EXA70,const qreal &EXA75, const int &steinhartcalc0on, const int &steinhartcalc1on, const int &steinhartcalc2on,const int &AN0R3VAL,const int &AN0R4VAL,const int &AN1R3VAL,const int &AN1R4VAL,const int &AN2R3VAL,const int &AN2R4VAL)
{

    EXAN00 = EXA00;
    EXAN05 = EXA05;
    EXAN10 = EXA10;
    EXAN15 = EXA15;
    EXAN20 = EXA20;
    EXAN25 = EXA25;
    EXAN30 = EXA30;
    EXAN35 = EXA35;
    EXAN40 = EXA40;
    EXAN45 = EXA45;
    EXAN50 = EXA50;
    EXAN55 = EXA55;
    EXAN60 = EXA60;
    EXAN65 = EXA65;
    EXAN70 = EXA70;
    EXAN75 = EXA75;
    EXsteinhart0 = steinhartcalc0on;
    EXsteinhart1 = steinhartcalc1on;
    EXsteinhart2 = steinhartcalc2on;

    // Calculating the Boad internal resistance of the Voltage divider
    // EX Analog 0
    if (AN0R3VAL !=0 && AN0R4VAL !=0)
    {
      Rtotalexan0 = 1/((1/R2)+(1/R3)+(1/R4));
    }
    if (AN0R3VAL ==0 && AN0R4VAL !=0)
    {
      Rtotalexan0 =  (R2*R4)/(R2+R4);
    }
    if (AN0R3VAL !=0 && AN0R4VAL ==0)
    {
      Rtotalexan0 =  (R2*R3)/(R2+R3);
    }
    if (AN0R3VAL ==0 && AN0R4VAL ==0)
    {
      Rtotalexan0 = R2;
    }
    // EX Analog 1
    if (AN1R3VAL !=0 && AN1R4VAL !=0)
    {
      Rtotalexan1 = 1/((1/R2)+(1/R3)+(1/R4));
    }
    if (AN1R3VAL ==0 && AN1R4VAL !=0)
    {
      Rtotalexan1 =  (R2*R4)/(R2+R4);
    }
    if (AN1R3VAL !=0 && AN1R4VAL ==0)
    {
      Rtotalexan1 =  (R2*R3)/(R2+R3);
    }
    if (AN1R3VAL ==0 && AN1R4VAL ==0)
    {
      Rtotalexan1 = R2;
    }
    // EX Analog 2
    if (AN2R3VAL !=0 && AN2R4VAL !=0)
    {
      Rtotalexan2 = 1/((1/R2)+(1/R3)+(1/R4));
    }
    if (AN2R3VAL ==0 && AN2R4VAL !=0)
    {
      Rtotalexan2 =  (R2*R4)/(R2+R4);
    }
    if (AN2R3VAL !=0 && AN2R4VAL ==0)
    {
      Rtotalexan2 =  (R2*R3)/(R2+R3);
    }
    if (AN2R3VAL ==0 && AN2R4VAL ==0)
    {
      Rtotalexan2 = R2;
    }


/*
    qDebug() <<"///////////////////////////////////////////////////////////// :" ;
    qDebug() <<AN0R3VAL<<AN0R4VAL<<AN1R3VAL<<AN1R4VAL<<AN2R3VAL<<AN2R4VAL ;
     qDebug() <<"RTotal AN0 :" <<Rtotalexan0 ;
     qDebug() <<"RTotal AN1 :" <<Rtotalexan1 ;
     qDebug() <<"RTotal AN2 :" <<Rtotalexan2 ;
    qDebug() <<"///////////////////////////////////////////////////////////// :" ;
*/

}

void DashBoard::setSteinhartcalc(const qreal &T01,const qreal &T02,const qreal &T03,const qreal &R01,const qreal &R02,const qreal &R03,const qreal &T11,const qreal &T12,const qreal &T13,const qreal &R11,const qreal &R12,const qreal &R13,const qreal &T21,const qreal &T22,const qreal &T23,const qreal &R21,const qreal &R22,const qreal &R23)
{
    //qDebug() <<"Values :" <<T01 << R01 << T02 <<R02 <<T03 << R03 << T11 << R11 << T12 <<R12 <<T13 << R13 << T21 << R21 << T22 <<R22 <<T23 << R23;
    //EX Analog 0 Calculation
    long double L01 = log(R01); //Logrythm of Resistance 1
    long double L02 = log(R02); //Logrythm of Resistance 2
    long double L03 = log(R03); //Logrythm of Resistance 3

    //Convert Temperature from CELCIUS to Kelvin and get factor
    long double Y01 = 1/(T01+273.15);
    long double Y02 = 1/(T02+273.15);
    long double Y03 = 1/(T03+273.15);

    //Coefficent of L and Y
    long double V02 = (Y02-Y01)/(L02-L01);
    long double V03 = (Y03-Y01)/(L03-L01);

    //Coefficent Calculations
    C0 = ((V03 - V02)/(L03-L02))*(pow((L01+L02+L02),-1));
    B0 = (V03-C0*(pow(L01,2)+L01*L02+pow(L02,2)));
    A0 = Y01 -(B0+pow(L01,2)*C0)*L01;


    //EX Analog 1 Calculation
    long double L11 = log(R11); //Logrythm of Resistance 1
    long double L12 = log(R12); //Logrythm of Resistance 2
    long double L13 = log(R13); //Logrythm of Resistance 3

    //Convert Temperature from CELCIUS to Kelvin and get factor
    long double Y11 = 1/(T11+273.15);
    long double Y12 = 1/(T12+273.15);
    long double Y13 = 1/(T13+273.15);

    //Coefficent of L and Y
    long double V12 = (Y12-Y11)/(L12-L11);
    long double V13 = (Y13-Y11)/(L13-L11);

    //Coefficent Calculations
    C1 = ((V13 - V12)/(L13-L12))*(pow((L11+L12+L12),-1));
    B1 = (V13-C1*(pow(L11,2)+L11*L12+pow(L12,2)));
    A1 = Y11 -(B1+pow(L11,2)*C1)*L11;

    //EX Analog 2 Calculation
    long double L21 = log(R21); //Logrythm of Resistance 1
    long double L22 = log(R22); //Logrythm of Resistance 2
    long double L23 = log(R23); //Logrythm of Resistance 3

    //Convert Temperature from CELCIUS to Kelvin and get factor
    long double Y21 = 1/(T21+273.15);
    long double Y22 = 1/(T22+273.15);
    long double Y23 = 1/(T23+273.15);

    //Coefficent of L and Y
    long double V22 = (Y22-Y21)/(L22-L21);
    long double V23 = (Y23-Y21)/(L23-L21);

    //Coefficent Calculations
    C2 = ((V23 - V22)/(L23-L22))*(pow((L21+L22+L22),-1));
    B2 = (V23-C2*(pow(L21,2)+L22*L22+pow(L22,2)));
    A2 = Y21 -(B2+pow(L21,2)*C2)*L21;
    //

}
// Advanced Info FD3S
void DashBoard::setrpm(const qreal &rpm)
{
    if (m_rpm == rpm)
        return;
    m_rpm = rpm;

    //Smoothing
    if (m_smoothrpm >0)
    {
        averageRPM.removeFirst();
        averageRPM.append(m_rpm);
        avgrpm = 0;
        for (int i = 0; i <= m_smoothrpm-1; i++){avgrpm+= averageRPM[i];}
        m_rpm = avgrpm/m_smoothrpm;
    }
    emit rpmChanged(rpm);
}

void DashBoard::setIntakepress(const qreal &Intakepress)
{
    if (m_Intakepress == Intakepress)
        return;
    if (m_pressureunits == "metric")
    {m_Intakepress = Intakepress;}
    if (m_pressureunits == "imperial")
    {m_Intakepress = Intakepress * 0.145038;}
    emit intakepressChanged(Intakepress);    
    return;
}

void DashBoard::setPressureV(const qreal &PressureV)
{
    if (m_PressureV == PressureV)
        return;
    m_PressureV = PressureV;
    emit pressureVChanged(PressureV);
}

void DashBoard::setThrottleV(const qreal &ThrottleV)
{
    if (m_ThrottleV == ThrottleV)
        return;
    m_ThrottleV= ThrottleV;
    emit throttleVChanged(ThrottleV);
}

void DashBoard::setPrimaryinp(const qreal &Primaryinp)
{
    if (m_Primaryinp == Primaryinp)
        return;
    m_Primaryinp= Primaryinp;
    emit primaryinpChanged(Primaryinp);
}

void DashBoard::setFuelc(const qreal &Fuelc)
{
    if (m_Fuelc == Fuelc)
        return;
    m_Fuelc= Fuelc;
    emit fuelcChanged(Fuelc);
}

void DashBoard::setLeadingign(const qreal &Leadingign)
{
    if (m_Leadingign == Leadingign)
        return;
    m_Leadingign= Leadingign;
    emit leadingignChanged(Leadingign);
}

void DashBoard::setTrailingign(const qreal &Trailingign)
{
    if (m_Trailingign == Trailingign)
        return;
    m_Trailingign= Trailingign;
    emit trailingignChanged(Trailingign);
}

void DashBoard::setFueltemp(const qreal &Fueltemp)
{
    if (m_Fueltemp == Fueltemp)
        return;
    if (m_units == "metric")
    {m_Fueltemp = Fueltemp;}
    if (m_units == "imperial")
    {m_Fueltemp = Fueltemp * 1.8 + 32;}
    emit fueltempChanged(Fueltemp);
}

void DashBoard::setMoilp(const qreal &Moilp)
{
    if (m_Moilp == Moilp)
        return;
    m_Moilp = Moilp;
    emit moilpChanged(Moilp);
}

void DashBoard::setBoosttp(const qreal &Boosttp)
{
    if (m_Boosttp == Boosttp)
        return;
    m_Boosttp = Boosttp;
    emit boosttpChanged(Boosttp);
}

void DashBoard::setBoostwg(const qreal &Boostwg)
{
    if (m_Boostwg == Boostwg)
        return;
    m_Boostwg = Boostwg;
    emit boostwgChanged(Boostwg);
}

void DashBoard::setWatertemp(const qreal &Watertemp)
{
    if (m_Watertemp == Watertemp)
        return;
    if (m_units == "metric")
    {m_Watertemp = Watertemp;}
    if (m_units == "imperial")
    {m_Watertemp = Watertemp * 1.8 + 32;}

    emit watertempChanged(Watertemp);
}

void DashBoard::setIntaketemp(const qreal &Intaketemp)
{
    if (m_units == "metric")
    { m_Intaketemp = Intaketemp;}
    if (m_units == "imperial")
    {m_Intaketemp = Intaketemp * 1.8 + 32;}

    emit intaketempChanged(Intaketemp);
}

void DashBoard::setKnock(const qreal &Knock)
{
    if (m_Knock == Knock)
        return;
    m_Knock = Knock;
    emit knockChanged(Knock);
}

void DashBoard::setBatteryV(const qreal &BatteryV)
{
    if (m_BatteryV == BatteryV)
        return;
    m_BatteryV = BatteryV;
    emit batteryVChanged(BatteryV);
}

void DashBoard::setSpeed(const qreal &speed)
{
    //qDebug()<< "SPEED" << m_speed;
    if (m_speed == speed)
        return;
    if (m_speedunits == "metric")
    {m_speed = qRound(speed * m_speedpercent);}
    if (m_speedunits == "imperial")
    {m_speed = qRound((speed * 0.621371) * m_speedpercent);}
    if (m_smoothspeed != 0)
    {
        averageSpeed.removeFirst();
        averageSpeed.append(m_speed);
        //qDebug() << "Vector Speed " << averageSpeed;
        avgspeed = 0;
        for (int i = 0; i <= m_smoothspeed-1; i++){avgspeed+= averageSpeed[i];}
        m_speed = avgspeed/m_smoothspeed;
        // qDebug() << "Average Speed " << m_speed;
    }
if (m_ExternalSpeed == 0){
    emit speedChanged(m_speed);
}
}

void DashBoard::setIscvduty(const qreal &Iscvduty)
{
    if (m_Iscvduty == Iscvduty)
        return;
    m_Iscvduty = Iscvduty;
    emit iscvdutyChanged(Iscvduty);
}

void DashBoard::setO2volt(const qreal &O2volt)
{
    if (m_O2volt == O2volt)
        return;
    m_O2volt = O2volt;
    emit o2voltChanged(O2volt);
}

void DashBoard::setCyl1_O2_Corr(const qreal &Cyl1_O2_Corr)
{
    if (m_Cyl1_O2_Corr == Cyl1_O2_Corr)
        return;
    m_Cyl1_O2_Corr = Cyl1_O2_Corr;
    emit Cyl1_O2_CorrChanged(Cyl1_O2_Corr);
}
void DashBoard::setCyl2_O2_Corr(const qreal &Cyl2_O2_Corr)
{
    if (m_Cyl2_O2_Corr == Cyl2_O2_Corr)
        return;
    m_Cyl2_O2_Corr = Cyl2_O2_Corr;
    emit Cyl2_O2_CorrChanged(Cyl2_O2_Corr);
}
void DashBoard::setCyl3_O2_Corr(const qreal &Cyl3_O2_Corr)
{
    if (m_Cyl3_O2_Corr == Cyl3_O2_Corr)
        return;
    m_Cyl3_O2_Corr = Cyl3_O2_Corr;
    emit Cyl3_O2_CorrChanged(Cyl3_O2_Corr);
}
void DashBoard::setCyl4_O2_Corr(const qreal &Cyl4_O2_Corr)
{
    if (m_Cyl4_O2_Corr == Cyl4_O2_Corr)
        return;
    m_Cyl4_O2_Corr = Cyl4_O2_Corr;
    emit Cyl4_O2_CorrChanged(Cyl4_O2_Corr);
}
void DashBoard::setCyl5_O2_Corr(const qreal &Cyl5_O2_Corr)
{
    if (m_Cyl5_O2_Corr == Cyl5_O2_Corr)
        return;
    m_Cyl5_O2_Corr = Cyl5_O2_Corr;
    emit Cyl5_O2_CorrChanged(Cyl5_O2_Corr);
}
void DashBoard::setCyl6_O2_Corr(const qreal &Cyl6_O2_Corr)
{
    if (m_Cyl6_O2_Corr == Cyl6_O2_Corr)
        return;
    m_Cyl6_O2_Corr = Cyl6_O2_Corr;
    emit Cyl6_O2_CorrChanged(Cyl6_O2_Corr);
}
void DashBoard::setCyl7_O2_Corr(const qreal &Cyl7_O2_Corr)
{
    if (m_Cyl7_O2_Corr == Cyl7_O2_Corr)
        return;
    m_Cyl7_O2_Corr = Cyl7_O2_Corr;
    emit Cyl7_O2_CorrChanged(Cyl7_O2_Corr);
}
void DashBoard::setCyl8_O2_Corr(const qreal &Cyl8_O2_Corr)
{
    if (m_Cyl8_O2_Corr == Cyl8_O2_Corr)
        return;
    m_Cyl8_O2_Corr = Cyl8_O2_Corr;
    emit Cyl8_O2_CorrChanged(Cyl8_O2_Corr);
}
void DashBoard::setna1(const qreal &na1)
{
    if (m_na1 == na1)
        return;
    m_na1 = na1;
    emit na1Changed(na1);
}

void DashBoard::setSecinjpulse(const qreal &Secinjpulse)
{
    if (m_Secinjpulse == Secinjpulse)
        return;
    m_Secinjpulse = Secinjpulse;
    emit secinjpulseChanged(Secinjpulse);
}

void DashBoard::setna2(const qreal &na2)
{
    if (m_na2 == na2)
        return;
    m_na2 = na2;
    emit na2Changed(na2);
}

void DashBoard::setEngLoad(const qreal &EngLoad)
{
    if (m_EngLoad == EngLoad)
        return;
    m_EngLoad = EngLoad;
    emit engLoadChanged(EngLoad);
}

void DashBoard::setMAF1V(const qreal &MAF1V)
{
    if (m_MAF1V == MAF1V)
        return;
    m_MAF1V = MAF1V;
    emit mAF1VChanged(MAF1V);
}

void DashBoard::setMAF2V(const qreal &MAF2V)
{
    if (m_MAF2V == MAF2V)
        return;
    m_MAF2V = MAF2V;
    emit mAF2VChanged(MAF2V);
}

void DashBoard::setinjms(const qreal &injms)
{
    if (m_injms == injms)
        return;
    m_injms = injms;
    emit injmsChanged(injms);
}

void DashBoard::setIgn(const qreal &Ign)
{
    if (m_Ign == Ign)
        return;
    m_Ign = Ign;
    emit ignChanged(Ign);
}

void DashBoard::setInj(const qreal &Inj)
{
    if (m_Inj == Inj)
        return;
    m_Inj = Inj;
    emit injChanged(Inj);
}
void DashBoard::setDwell(const qreal &Dwell)
{
    if (m_Dwell == Dwell)
        return;
    m_Dwell = Dwell;
    emit dwellChanged(Dwell);
}

void DashBoard::setBoostPres(const qreal &BoostPres)
{
    if (m_BoostPres == BoostPres)
        return;
    if (m_pressureunits == "metric")
    {m_BoostPres = BoostPres;}
    if (m_pressureunits == "imperial")
    {
        if (BoostPres <= 0)
        {m_BoostPres = BoostPres * 0.039370079197446;}
        if (BoostPres > 0)
        {
        qreal temp;
        temp = BoostPres * 142.233;
        m_BoostPres = (temp/10);
        }
    }
    emit BoostPresChanged(BoostPres);


}
void DashBoard::setBoostPreskpa(const qreal &BoostPreskpa)
{
    if (m_BoostPreskpa == BoostPreskpa)
        return;
    if (m_pressureunits == "metric")
    {m_BoostPreskpa = BoostPreskpa;}
    if (m_pressureunits == "imperial")
    {
       m_BoostPreskpa = BoostPreskpa * 0.145038;

    }
    emit BoostPreskpaChanged(BoostPreskpa);


}

void DashBoard::setBoostDuty(const qreal &BoostDuty)
{
    if (m_BoostDuty == BoostDuty)
        return;
    m_BoostDuty = BoostDuty;
    emit boostDutyChanged(BoostDuty);
}

void DashBoard::setMAFactivity(const qreal &MAFactivity)
{
    if (m_MAFactivity == MAFactivity)
        return;
    m_MAFactivity = MAFactivity;
    emit mAFactivityChanged(MAFactivity);
}

void DashBoard::setO2volt_2(const qreal &O2volt_2)
{
    if (m_O2volt_2 == O2volt_2)
        return;
    m_O2volt_2 = O2volt_2;
    emit o2volt_2Changed(O2volt_2);
}


//Boost

void DashBoard::setpim(const qreal &pim)
{
    if (m_pim == pim)
        return;
    m_pim = pim;
    emit pimChanged(pim);
}

//Aux Inputs

void DashBoard::setauxcalc1(const qreal &auxcalc1)
{
    if (m_auxcalc1 == auxcalc1)
        return;
    m_auxcalc1 = auxcalc1;
    emit auxcalc1Changed(auxcalc1);
}

void DashBoard::setauxcalc2(const qreal &auxcalc2)
{
    if (m_auxcalc2 == auxcalc2)
        return;
    m_auxcalc2 = auxcalc2;
    emit auxcalc2Changed(auxcalc2);
}

void DashBoard::setauxcalc3(const qreal &auxcalc3)
{
    if (m_auxcalc3 == auxcalc3)
        return;
    m_auxcalc3 = auxcalc3;
    emit auxcalc3Changed(auxcalc3);
}

void DashBoard::setauxcalc4(const qreal &auxcalc4)
{
    if (m_auxcalc4 == auxcalc4)
        return;
    m_auxcalc4 = auxcalc4;
    emit auxcalc4Changed(auxcalc4);
}


//Sensor info


void DashBoard::setsens1(const qreal &sens1)
{
    if (m_sens1 == sens1)
        return;
    m_sens1 = sens1;
    emit sens1Changed(sens1);
}

void DashBoard::setsens2(const qreal &sens2)
{
    if (m_sens2 == sens2)
        return;
    m_sens2 = sens2;
    emit sens2Changed(sens2);
}

void DashBoard::setsens3(const qreal &sens3)
{
    if (m_sens3 == sens3)
        return;
    m_sens3 = sens3;
    emit sens3Changed(sens3);
}

void DashBoard::setsens4(const qreal &sens4)
{
    if (m_sens4 == sens4)
        return;
    m_sens4 = sens4;
    emit sens4Changed(sens4);
}

void DashBoard::setsens5(const qreal &sens5)
{
    if (m_sens5 == sens5)
        return;
    m_sens5 = sens5;
    emit sens5Changed(sens5);
}

void DashBoard::setsens6(const qreal &sens6)
{
    if (m_sens6 == sens6)
        return;
    m_sens6 = sens6;
    emit sens6Changed(sens6);
}

void DashBoard::setsens7(const qreal &sens7)
{
    if (m_sens7 == sens7)
        return;
    m_sens7 = sens7;
    emit sens7Changed(sens7);
}

void DashBoard::setsens8(const qreal &sens8)
{
    if (m_sens8 == sens8)
        return;
    m_sens8 = sens8;
    emit sens8Changed(sens8);
}

void DashBoard::setInjDuty(const qreal &InjDuty)
{
    if (m_InjDuty == InjDuty)
        return;
    m_InjDuty = InjDuty;
    emit injDutyChanged(InjDuty);
}

void DashBoard::setInjDuty2(const qreal &InjDuty2)
{
    if (m_InjDuty2 == InjDuty2)
        return;
    m_InjDuty2 = InjDuty2;
    emit injDuty2Changed(InjDuty2);
}

void DashBoard::setInjAngle(const qreal &InjAngle)
{
    if (m_InjAngle == InjAngle)
        return;
    m_InjAngle = InjAngle;
    emit InjAngleChanged(InjAngle);
}
//Flags

void DashBoard::setFlag1(const qreal &Flag1)
{
    if (m_Flag1 == Flag1)
        return;
    m_Flag1 = Flag1;
    emit flag1Changed(Flag1);
}

void DashBoard::setFlag2(const qreal &Flag2)
{
    if (m_Flag2 == Flag2)
        return;
    m_Flag2 = Flag2;
    emit flag2Changed(Flag2);
}

void DashBoard::setFlag3(const qreal &Flag3)
{
    if (m_Flag3 == Flag3)
        return;
    m_Flag3 = Flag3;
    emit flag3Changed(Flag3);
}

void DashBoard::setFlag4(const qreal &Flag4)
{
    if (m_Flag4 == Flag4)
        return;
    m_Flag4 = Flag4;
    emit flag4Changed(Flag4);
}

void DashBoard::setFlag5(const qreal &Flag5)
{
    if (m_Flag5 == Flag5)
        return;
    m_Flag5 = Flag5;
    emit flag5Changed(Flag5);
}

void DashBoard::setFlag6(const qreal &Flag6)
{
    if (m_Flag6 == Flag6)
        return;
    m_Flag6 = Flag6;
    emit flag6Changed(Flag6);
}

void DashBoard::setFlag7(const qreal &Flag7)
{
    if (m_Flag7 == Flag7)
        return;
    m_Flag7 = Flag7;
    emit flag7Changed(Flag7);
}

void DashBoard::setFlag8(const qreal &Flag8)
{
    if (m_Flag8 == Flag8)
        return;
    m_Flag8 = Flag8;
    emit flag8Changed(Flag8);
}

void DashBoard::setFlag9(const qreal &Flag9)
{
    if (m_Flag9 == Flag9)
        return;
    m_Flag9 = Flag9;
    emit flag9Changed(Flag9);
}

void DashBoard::setFlag10(const qreal &Flag10)
{
    if (m_Flag10 == Flag10)
        return;
    m_Flag10 = Flag10;
    emit flag10Changed(Flag10);
}

void DashBoard::setFlag11(const qreal &Flag11)
{
    if (m_Flag11 == Flag11)
        return;
    m_Flag11 = Flag11;
    emit flag11Changed(Flag11);
}

void DashBoard::setFlag12(const qreal &Flag12)
{
    if (m_Flag12 == Flag12)
        return;
    m_Flag12 = Flag12;
    emit flag12Changed(Flag12);
}

void DashBoard::setFlag13(const qreal &Flag13)
{
    if (m_Flag13 == Flag13)
        return;
    m_Flag13 = Flag13;
    emit flag13Changed(Flag13);
}

void DashBoard::setFlag14(const qreal &Flag14)
{
    if (m_Flag14 == Flag14)
        return;
    m_Flag14 = Flag14;
    emit flag14Changed(Flag14);
}

void DashBoard::setFlag15(const qreal &Flag15)
{
    if (m_Flag15 == Flag15)
        return;
    m_Flag15 = Flag15;
    emit flag15Changed(Flag15);
}

void DashBoard::setFlag16(const qreal &Flag16)
{
    if (m_Flag16 == Flag16)
        return;
    m_Flag16 = Flag16;
    emit flag16Changed(Flag16);
}
void DashBoard::setFlag17(const qreal &Flag17)
{
    if (m_Flag17 == Flag17)
        return;
    m_Flag17 = Flag17;
    emit flag17Changed(Flag17);
}
void DashBoard::setFlag18(const qreal &Flag18)
{
    if (m_Flag18 == Flag18)
        return;
    m_Flag18 = Flag18;
    emit flag18Changed(Flag18);
}
void DashBoard::setFlag19(const qreal &Flag19)
{
    if (m_Flag19 == Flag19)
        return;
    m_Flag19 = Flag19;
    emit flag19Changed(Flag19);
}
void DashBoard::setFlag20(const qreal &Flag20)
{
    if (m_Flag20 == Flag20)
        return;
    m_Flag20 = Flag20;
    emit flag20Changed(Flag20);
}
void DashBoard::setFlag21(const qreal &Flag21)
{
    if (m_Flag21 == Flag21)
        return;
    m_Flag21 = Flag21;
    emit flag21Changed(Flag21);
}
void DashBoard::setFlag22(const qreal &Flag22)
{
    if (m_Flag22 == Flag22)
        return;
    m_Flag22 = Flag22;
    emit flag22Changed(Flag22);
}
void DashBoard::setFlag23(const qreal &Flag23)
{
    if (m_Flag23 == Flag23)
        return;
    m_Flag23 = Flag23;
    emit flag23Changed(Flag23);
}
void DashBoard::setFlag24(const qreal &Flag24)
{
    if (m_Flag24 == Flag24)
        return;
    m_Flag24 = Flag24;
    emit flag24Changed(Flag24);
}
void DashBoard::setFlag25(const qreal &Flag25)
{
    if (m_Flag25 == Flag25)
        return;
    m_Flag25 = Flag25;
    emit flag25Changed(Flag25);
}
//Flag Strings

void DashBoard::setFlagString1(const QString &FlagString1)
{
    if (m_FlagString1 == FlagString1)
        return;
    m_FlagString1 = FlagString1;
    emit flagString1Changed(FlagString1);
}

void DashBoard::setFlagString2(const QString &FlagString2)
{
    if (m_FlagString2 == FlagString2)
        return;
    m_FlagString2 = FlagString2;
    emit flagString2Changed(FlagString2);
}

void DashBoard::setFlagString3(const QString &FlagString3)
{
    if (m_FlagString3 == FlagString3)
        return;
    m_FlagString3 = FlagString3;
    emit flagString3Changed(FlagString3);
}

void DashBoard::setFlagString4(const QString &FlagString4)
{
    if (m_FlagString4 == FlagString4)
        return;
    m_FlagString4 = FlagString4;
    emit flagString4Changed(FlagString4);
}

void DashBoard::setFlagString5(const QString &FlagString5)
{
    if (m_FlagString5 == FlagString5)
        return;
    m_FlagString5 = FlagString5;
    emit flagString5Changed(FlagString5);
}

void DashBoard::setFlagString6(const QString &FlagString6)
{
    if (m_FlagString6 == FlagString6)
        return;
    m_FlagString6 = FlagString6;
    emit flagString6Changed(FlagString6);
}

void DashBoard::setFlagString7(const QString &FlagString7)
{
    if (m_FlagString7 == FlagString7)
        return;
    m_FlagString7 = FlagString7;
    emit flagString7Changed(FlagString7);
}

void DashBoard::setFlagString8(const QString &FlagString8)
{
    if (m_FlagString8 == FlagString8)
        return;
    m_FlagString8 = FlagString8;
    emit flagString8Changed(FlagString8);
}

void DashBoard::setFlagString9(const QString &FlagString9)
{
    if (m_FlagString9 == FlagString9)
        return;
    m_FlagString9 = FlagString9;
    emit flagString9Changed(FlagString9);
}

void DashBoard::setFlagString10(const QString &FlagString10)
{
    if (m_FlagString10 == FlagString10)
        return;
    m_FlagString10 = FlagString10;
    emit flagString10Changed(FlagString10);
}

void DashBoard::setFlagString11(const QString &FlagString11)
{
    if (m_FlagString11 == FlagString11)
        return;
    m_FlagString11 = FlagString11;
    emit flagString11Changed(FlagString11);
}

void DashBoard::setFlagString12(const QString &FlagString12)
{
    if (m_FlagString12 == FlagString12)
        return;
    m_FlagString12 = FlagString12;
    emit flagString12Changed(FlagString12);
}

void DashBoard::setFlagString13(const QString &FlagString13)
{
    if (m_FlagString13 == FlagString13)
        return;
    m_FlagString13 = FlagString13;
    emit flagString13Changed(FlagString13);
}

void DashBoard::setFlagString14(const QString &FlagString14)
{
    if (m_FlagString14 == FlagString14)
        return;
    m_FlagString14 = FlagString14;
    emit flagString14Changed(FlagString14);
}

void DashBoard::setFlagString15(const QString &FlagString15)
{
    if (m_FlagString15 == FlagString15)
        return;
    m_FlagString15 = FlagString15;
    emit flagString15Changed(FlagString15);
}

void DashBoard::setFlagString16(const QString &FlagString16)
{
    if (m_FlagString16 == FlagString16)
        return;
    m_FlagString16 = FlagString16;
    emit flagString16Changed(FlagString16);
}


void DashBoard::setPlatform(const QString &Platform)
{
    if (m_Platform == Platform)
        return;
    m_Platform = Platform;
    emit platformChanged(Platform);
}

//Sensor Strings

void DashBoard::setSensorString1(const QString &SensorString1)
{
    if (m_SensorString1 == SensorString1)
        return;
    m_SensorString1 = SensorString1;
    emit sensorString1Changed(SensorString1);
}

void DashBoard::setSensorString2(const QString &SensorString2)
{
    if (m_SensorString2 == SensorString2)
        return;
    m_SensorString2 = SensorString2;
    emit sensorString2Changed(SensorString2);
}

void DashBoard::setSensorString3(const QString &SensorString3)
{
    if (m_SensorString3 == SensorString3)
        return;
    m_SensorString3 = SensorString3;
    emit sensorString3Changed(SensorString3);
}

void DashBoard::setSensorString4(const QString &SensorString4)
{
    if (m_SensorString4 == SensorString4)
        return;
    m_SensorString4 = SensorString4;
    emit sensorString4Changed(SensorString4);
}

void DashBoard::setSensorString5(const QString &SensorString5)
{
    if (m_SensorString5 == SensorString5)
        return;
    m_SensorString5 = SensorString5;
    emit sensorString5Changed(SensorString5);
}

void DashBoard::setSensorString6(const QString &SensorString6)
{
    if (m_SensorString6 == SensorString6)
        return;
    m_SensorString6 = SensorString6;
    emit sensorString6Changed(SensorString6);
}

void DashBoard::setSensorString7(const QString &SensorString7)
{
    if (m_SensorString7 == SensorString7)
        return;
    m_SensorString7 = SensorString7;
    emit sensorString7Changed(SensorString7);
}

void DashBoard::setSensorString8(const QString &SensorString8)
{
    if (m_SensorString8 == SensorString8)
        return;
    m_SensorString8 = SensorString8;
    emit sensorString8Changed(SensorString8);
}

void DashBoard::setSerialStat(const QString &SerialStat)
{
    if (m_SerialStat == SerialStat)
        return;
    m_SerialStat = SerialStat;
    emit serialStatChanged(SerialStat);
}

void DashBoard::setRecvData(const QString &RecvData)
{
    if (m_RecvData == RecvData)
        return;
    m_RecvData = RecvData;
    emit recvDataChanged(RecvData);
}

void DashBoard::setTimeoutStat(const QString &TimeoutStat)
{
    if (m_TimeoutStat == TimeoutStat)
        return;
    m_TimeoutStat = TimeoutStat;
    emit timeoutStatChanged(TimeoutStat);
}

void DashBoard::setRunStat(const QString &RunStat)
{
    if (m_RunStat == RunStat)
        return;
    m_RunStat = RunStat;
    emit runStatChanged(RunStat);
}

void DashBoard::setWifiStat(const QString &WifiStat)
{
    if (m_WifiStat == WifiStat)
        return;
    m_WifiStat = WifiStat;
    emit WifiStatChanged(WifiStat);
}
void DashBoard::setEthernetStat(const QString &EthernetStat)
{
    if (m_EthernetStat == EthernetStat)
        return;
    m_EthernetStat = EthernetStat;
    emit EthernetStatChanged(EthernetStat);
}

// GPS


void DashBoard::setgpsTime (const QString &gpsTime)
{
    if (m_gpsTime == gpsTime)
        return;
    m_gpsTime = gpsTime;
    emit gpsTimeChanged(gpsTime);
}

void DashBoard::setgpsAltitude(const qreal &gpsAltitude)
{
    if (m_gpsAltitude == gpsAltitude)
        return;
    m_gpsAltitude = gpsAltitude;
    emit gpsAltitudeChanged(gpsAltitude);
}

void DashBoard::setgpsLatitude(const qreal &gpsLatitude)
{
    if (m_gpsLatitude == gpsLatitude)
        return;
    m_gpsLatitude = gpsLatitude;
    emit gpsLatitudeChanged(gpsLatitude);
}

void DashBoard::setgpsLongitude(const qreal &gpsLongitude)
{
    if (m_gpsLongitude == gpsLongitude)
        return;
    m_gpsLongitude = gpsLongitude;
    emit gpsLongitudeChanged(gpsLongitude);
}

void DashBoard::setgpsSpeed(const double &gpsSpeed)
{
    if (m_gpsSpeed == gpsSpeed)
        return;
    m_gpsSpeed = gpsSpeed;

    if (m_speedunits == "metric")
    {m_speed = qRound(gpsSpeed * m_speedpercent);}
    if (m_speedunits == "imperial")
    {m_speed = qRound((gpsSpeed * 0.621371) * m_speedpercent);}

    emit gpsSpeedChanged(gpsSpeed);

    if (m_ExternalSpeed == 5){
    emit speedChanged(gpsSpeed);
    }
}

void DashBoard::setgpsVisibleSatelites(const int &gpsVisibleSatelites)
{
    if (m_gpsVisibleSatelites == gpsVisibleSatelites)
        return;
    m_gpsVisibleSatelites = gpsVisibleSatelites;
    emit gpsVisibleSatelitesChanged(gpsVisibleSatelites);
}

void DashBoard::setgpsFIXtype(const QString &gpsFIXtype)
{
    if (m_gpsFIXtype == gpsFIXtype)
        return;
    m_gpsFIXtype = gpsFIXtype;
    emit gpsFIXtypeChanged(gpsFIXtype);
}
void DashBoard::setgpsbaering(const qreal &gpsbaering)
{
    if (m_gpsbaering == gpsbaering)
        return;
    m_gpsbaering = gpsbaering;
    emit gpsbaeringChanged(gpsbaering);
}


// Units
void DashBoard::setunits (const QString &units)
{
    if (m_units == units)
        return;
    m_units = units;
    emit unitsChanged(units);
}
void DashBoard::setspeedunits (const QString &speedunits)
{
    if (m_speedunits == speedunits)
        return;
    m_speedunits = speedunits;
    emit speedunitsChanged(speedunits);
}

void DashBoard::setpressureunits (const QString &pressureunits)
{
    if (m_pressureunits == pressureunits)
        return;
    m_pressureunits = pressureunits;
    emit pressureunitsChanged(pressureunits);
}
//Adaptronic extra


void DashBoard::setMAP(const qreal &MAP)
{
    if (m_pressureunits == "metric")
    { m_MAP = MAP;}
    if (m_pressureunits == "imperial")
    {m_MAP = MAP * 0.145038;}
    emit mAPChanged(MAP);
}

void DashBoard::setPANVAC(const qreal &PANVAC)
{
    if (m_pressureunits == "metric")
    { m_PANVAC = PANVAC;}
    if (m_pressureunits == "imperial")
    {m_PANVAC = PANVAC * 0.145038;}
    emit PANVACChanged(PANVAC);
}

void DashBoard::setMAP2(const qreal &MAP2)
{
    if (m_pressureunits == "metric")
    { m_MAP2 = MAP2;}
    if (m_pressureunits == "imperial")
    {m_MAP2 = MAP2 * 0.145038;}
    emit mAP2Changed(MAP2);
}
void DashBoard::setAUXT(const qreal &AUXT)
{
    if (m_AUXT == AUXT)
        return;
    m_AUXT = AUXT;
    emit aUXTChanged(AUXT);
}

void DashBoard::setAFR(const qreal &AFR)
{
    if (m_AFR == AFR)
        return;
    m_AFR = AFR;
    emit aFRChanged(AFR);
}

void DashBoard::setAFRLEFTBANKTARGET(const qreal &AFRLEFTBANKTARGET)
{
    if (m_AFRLEFTBANKTARGET == AFRLEFTBANKTARGET)
        return;
    m_AFRLEFTBANKTARGET = AFRLEFTBANKTARGET;
    emit AFRLEFTBANKTARGETChanged(AFRLEFTBANKTARGET);
}

void DashBoard::setAFRRIGHTBANKTARGET(const qreal &AFRRIGHTBANKTARGET)
{
    if (m_AFRRIGHTBANKTARGET == AFRRIGHTBANKTARGET)
        return;
    m_AFRRIGHTBANKTARGET = AFRRIGHTBANKTARGET;
    emit aFRChanged(AFRRIGHTBANKTARGET);
}

void DashBoard::setAFRLEFTBANKACTUAL(const qreal &AFRLEFTBANKACTUAL)
{
    if (m_AFRLEFTBANKACTUAL == AFRLEFTBANKACTUAL)
        return;
    m_AFRLEFTBANKACTUAL = AFRLEFTBANKACTUAL;
    emit AFRLEFTBANKACTUALChanged(AFRLEFTBANKACTUAL);
}

void DashBoard::setAFRRIGHTBANKACTUAL(const qreal &AFRRIGHTBANKACTUAL)
{
    if (m_AFRRIGHTBANKACTUAL == AFRRIGHTBANKACTUAL)
        return;
    m_AFRRIGHTBANKACTUAL = AFRRIGHTBANKACTUAL;
    emit AFRRIGHTBANKACTUALChanged(AFRRIGHTBANKACTUAL);
}

void DashBoard::setBOOSTOFFSET(const qreal &BOOSTOFFSET)
{
    if (m_BOOSTOFFSET == BOOSTOFFSET)
        return;
    m_BOOSTOFFSET = BOOSTOFFSET;
    emit BOOSTOFFSETChanged(BOOSTOFFSET);
}

void DashBoard::setREVLIM3STEP(const qreal &REVLIM3STEP)
{
    if (m_REVLIM3STEP == REVLIM3STEP)
        return;
    m_REVLIM3STEP = REVLIM3STEP;
    emit REVLIM3STEPChanged(REVLIM3STEP);
}

void DashBoard::setREVLIM2STEP(const qreal &REVLIM2STEP)
{
    if (m_REVLIM2STEP == REVLIM2STEP)
        return;
    m_REVLIM2STEP = REVLIM2STEP;
    emit REVLIM2STEPChanged(REVLIM2STEP);
}

void DashBoard::setREVLIMGIGHSIDE(const qreal &REVLIMGIGHSIDE)
{
    if (m_REVLIMGIGHSIDE == REVLIMGIGHSIDE)
        return;
    m_REVLIMGIGHSIDE = REVLIMGIGHSIDE;
    emit REVLIMGIGHSIDEChanged(REVLIMGIGHSIDE);
}

void DashBoard::setREVLIMBOURNOUT(const qreal &REVLIMBOURNOUT)
{
    if (m_REVLIMBOURNOUT == REVLIMBOURNOUT)
        return;
    m_REVLIMBOURNOUT = REVLIMBOURNOUT;
    emit REVLIMBOURNOUTChanged(REVLIMBOURNOUT);
}

void DashBoard::setLEFTBANKO2CORR(const qreal &LEFTBANKO2CORR)
{
    if (m_LEFTBANKO2CORR == LEFTBANKO2CORR)
        return;
    m_LEFTBANKO2CORR = LEFTBANKO2CORR;
    emit LEFTBANKO2CORRChanged(LEFTBANKO2CORR);
}

void DashBoard::setRIGHTBANKO2CORR(const qreal &RIGHTBANKO2CORR)
{
    if (m_RIGHTBANKO2CORR == RIGHTBANKO2CORR)
        return;
    m_RIGHTBANKO2CORR = RIGHTBANKO2CORR;
    emit RIGHTBANKO2CORRChanged(RIGHTBANKO2CORR);
}

void DashBoard::setTRACTIONCTRLOFFSET(const qreal &TRACTIONCTRLOFFSET)
{
    if (m_TRACTIONCTRLOFFSET == TRACTIONCTRLOFFSET)
        return;
    m_TRACTIONCTRLOFFSET = TRACTIONCTRLOFFSET;
    emit TRACTIONCTRLOFFSETChanged(TRACTIONCTRLOFFSET);
}
void DashBoard::setDRIVESHAFTOFFSET(const qreal &DRIVESHAFTOFFSET)
{
    if (m_DRIVESHAFTOFFSET == DRIVESHAFTOFFSET)
        return;
    m_DRIVESHAFTOFFSET = DRIVESHAFTOFFSET;
    emit DRIVESHAFTOFFSETChanged(DRIVESHAFTOFFSET);
}

void DashBoard::setTCCOMMAND(const qreal &TCCOMMAND)
{
    if (m_TCCOMMAND == TCCOMMAND)
        return;
    m_TCCOMMAND = TCCOMMAND;
    emit TCCOMMANDChanged(TCCOMMAND);
}

void DashBoard::setFSLCOMMAND(const qreal &FSLCOMMAND)
{
    if (m_FSLCOMMAND == FSLCOMMAND)
        return;
    m_FSLCOMMAND = FSLCOMMAND;
    emit FSLCOMMANDChanged(FSLCOMMAND);
}

void DashBoard::setFSLINDEX(const qreal &FSLINDEX)
{
    if (m_FSLINDEX == FSLINDEX)
        return;
    m_FSLINDEX = FSLINDEX;
    emit FSLINDEXChanged(FSLINDEX);
}

void DashBoard::setAFRcyl1(const qreal &AFRcyl1)
{
    if (m_AFRcyl1 == AFRcyl1)
        return;
    m_AFRcyl1 = AFRcyl1;
    emit AFRcyl1Changed(AFRcyl1);
}

void DashBoard::setAFRcyl2(const qreal &AFRcyl2)
{
    if (m_AFRcyl2 == AFRcyl2)
        return;
    m_AFRcyl2 = AFRcyl2;
    emit AFRcyl2Changed(AFRcyl2);
}
void DashBoard::setAFRcyl3(const qreal &AFRcyl3)
{
    if (m_AFRcyl3 == AFRcyl3)
        return;
    m_AFRcyl3 = AFRcyl3;
    emit AFRcyl3Changed(AFRcyl3);
}
void DashBoard::setAFRcyl4(const qreal &AFRcyl4)
{
    if (m_AFRcyl4 == AFRcyl4)
        return;
    m_AFRcyl4 = AFRcyl4;
    emit AFRcyl4Changed(AFRcyl4);
}
void DashBoard::setAFRcyl5(const qreal &AFRcyl5)
{
    if (m_AFRcyl5 == AFRcyl5)
        return;
    m_AFRcyl5 = AFRcyl5;
    emit AFRcyl5Changed(AFRcyl5);
}
void DashBoard::setAFRcyl6(const qreal &AFRcyl6)
{
    if (m_AFRcyl6 == AFRcyl6)
        return;
    m_AFRcyl6 = AFRcyl6;
    emit AFRcyl6Changed(AFRcyl6);
}
void DashBoard::setAFRcyl7(const qreal &AFRcyl7)
{
    if (m_AFRcyl7 == AFRcyl7)
        return;
    m_AFRcyl7 = AFRcyl7;
    emit AFRcyl7Changed(AFRcyl7);
}
void DashBoard::setAFRcyl8(const qreal &AFRcyl8)
{
    if (m_AFRcyl8 == AFRcyl8)
        return;
    m_AFRcyl8 = AFRcyl8;
    emit AFRcyl8Changed(AFRcyl8);
}



void DashBoard::setTPS(const qreal &TPS)
{
    if (m_TPS == TPS)
        return;
    m_TPS = TPS;
    emit tPSChanged(TPS);
}

void DashBoard::setIdleValue(const qreal &IdleValue)
{
    if (m_IdleValue == IdleValue)
        return;
    m_IdleValue = IdleValue;
    emit idleValueChanged(IdleValue);
}

void DashBoard::setMVSS(const qreal &MVSS)
{
    if (m_MVSS == MVSS)
        return;
    if (m_speedunits == "metric")
    { m_MVSS= MVSS;}
    if (m_speedunits == "imperial")
    {m_MVSS = qRound(MVSS * 0.621371);}

    emit mVSSChanged(MVSS);
}

void DashBoard::setSVSS(const qreal &SVSS)
{
    if (m_SVSS == SVSS)
        return;
    if (m_speedunits == "metric")
    { m_SVSS= SVSS;}
    if (m_speedunits == "imperial")
    {m_SVSS = qRound(SVSS * 0.621371);}
    emit sVSSChanged(SVSS);
}

void DashBoard::setInj1(const qreal &Inj1)
{
    if (m_Inj1 == Inj1)
        return;
    m_Inj1 = Inj1;
    emit inj1Changed(Inj1);
}

void DashBoard::setInj2(const qreal &Inj2)
{
    if (m_Inj2 == Inj2)
        return;
    m_Inj2 = Inj2;
    emit inj2Changed(Inj2);
}

void DashBoard::setInj3(const qreal &Inj3)
{
    if (m_Inj3 == Inj3)
        return;
    m_Inj3 = Inj3;
    emit inj3Changed(Inj3);
}

void DashBoard::setInj4(const qreal &Inj4)
{
    if (m_Inj4 == Inj4)
        return;
    m_Inj4 = Inj4;
    emit inj4Changed(Inj4);
}

void DashBoard::setIgn1(const qreal &Ign1)
{
    if (m_Ign1 == Ign1)
        return;
    m_Ign1 = Ign1;
    emit ign1Changed(Ign1);
}

void DashBoard::setIgn2(const qreal &Ign2)
{
    if (m_Ign2 == Ign2)
        return;
    m_Ign2 = Ign2;
    emit ign2Changed(Ign2);
}

void DashBoard::setIgn3(const qreal &Ign3)
{
    if (m_Ign3 == Ign3)
        return;
    m_Ign3 = Ign3;
    emit ign3Changed(Ign3);
}

void DashBoard::setIgn4(const qreal &Ign4)
{
    if (m_Ign4 == Ign4)
        return;
    m_Ign4 = Ign4;
    emit ign4Changed(Ign4);
}

void DashBoard::setTRIM(const qreal &TRIM)
{
    if (m_TRIM == TRIM)
        return;
    m_TRIM = TRIM;
    emit tRIMChanged(TRIM);
}

void DashBoard::setLAMBDA(const qreal &LAMBDA)
{
    if (m_LAMBDA == LAMBDA)
        return;
    m_LAMBDA = LAMBDA* lamdamultiplicator;
    emit lAMBDAChanged(m_LAMBDA);
}

void DashBoard::setLAMBDATarget(const qreal &LAMBDATarget)
{
    if (m_LAMBDATarget == LAMBDATarget)
        return;
    m_LAMBDATarget = LAMBDATarget;
    emit lAMBDATargetChanged(LAMBDATarget);
}

void DashBoard::setFuelPress(const qreal &FuelPress)
{
    if(m_FuelPress == FuelPress)
        return;
    if (m_pressureunits == "metric")
    { m_FuelPress = FuelPress;}
    if (m_pressureunits == "imperial")
    {m_FuelPress = FuelPress * 0.145038;}
    emit fuelPressChanged(FuelPress);
}
void DashBoard::setGearOilPress(const qreal &GearOilPress)
{
    if(m_GearOilPress == GearOilPress)
        return;
    if (m_pressureunits == "metric")
    { m_GearOilPress = GearOilPress;}
    if (m_pressureunits == "imperial")
    {m_GearOilPress = GearOilPress * 0.145038;}
    emit GearOilPressChanged(GearOilPress);
}

//Qsensors
void DashBoard::setaccelx(const qreal &accelx)
{
    if (m_accelx == accelx)
        return;
    m_accelx = accelx;
    emit accelxChanged(accelx);
}
void DashBoard::setaccely(const qreal &accely)
{
    if (m_accely == accely)
        return;
    m_accely = accely;
    emit accelyChanged(accely);
}
void DashBoard::setaccelz(const qreal &accelz)
{
    if (m_accelz == accelz)
        return;
    m_accelz = accelz;
    emit accelzChanged(accelz);
}
void DashBoard::setgyrox(const qreal &gyrox)
{
    if (m_gyrox == gyrox)
        return;
    m_gyrox = gyrox;
    emit gyroxChanged(gyrox);
}
void DashBoard::setgyroy(const qreal &gyroy)
{
    if (m_gyroy == gyroy)
        return;
    m_gyroy = gyroy;
    emit gyroyChanged(gyroy);
}
void DashBoard::setgyroz(const qreal &gyroz)
{
    if (m_gyroz == gyroz)
        return;
    m_gyroz = gyroz;
    emit gyrozChanged(gyroz);
}
void DashBoard::setcompass(const qreal &compass)
{
    if (m_compass == compass)
        return;
    m_compass = compass;
    emit compassChanged(compass);
}
void DashBoard::setambitemp(const qreal &ambitemp)
{
    if (m_ambitemp == ambitemp)
        return;
    if (m_pressureunits == "metric")
    { m_ambitemp = ambitemp;}
    if (m_pressureunits == "imperial")
    {m_ambitemp = ambitemp * 1.8 + 32;}
    emit ambitempChanged(ambitemp);
}
void DashBoard::setambipress(const qreal &ambipress)
{
    if (m_ambipress == ambipress)
        return;
    if (m_pressureunits == "metric")
    { m_ambipress = ambipress;}
    if (m_pressureunits == "imperial")
    {m_ambipress = ambipress * 0.145038;}
    emit ambipressChanged(ambipress);
}

//Calculations

void DashBoard::setGear(const qreal &Gear)
{
    if (m_Gear == Gear)
        return;
    m_Gear = Gear;
    emit GearChanged(Gear);
}

void DashBoard::setGearoffset(const qreal &Gearoffset)
{
    if (m_Gearoffset == Gearoffset)
        return;
    m_Gearoffset = Gearoffset;
    emit GearoffsetChanged(Gearoffset);
}

void DashBoard::setGearCalculation(const qreal &GearCalculation)
{
    if (m_GearCalculation == GearCalculation)
        return;
    m_GearCalculation = GearCalculation;
    emit GearCalculationChanged(GearCalculation);
}

void DashBoard::setPower(const qreal &Power)
{
    if (m_Power == Power)
        return;
    m_Power = Power;
    emit powerChanged(Power);
}
void DashBoard::setTorque(const qreal &Torque)
{
    if (m_Torque == Torque)
        return;
    m_Torque = Torque;
    emit torqueChanged(Torque);
}
void DashBoard::setAccelTimer(const qreal &AccelTimer)
{
    if (m_AccelTimer == AccelTimer)
        return;
    m_AccelTimer = AccelTimer;
    emit accelTimerChanged(AccelTimer);
}
void DashBoard::setWeight(const qreal &Weight)
{
    if (m_Weight == Weight)
        return;
    m_Weight = Weight;
    emit weightChanged(Weight);
}




//Official Pi screen present screen
void DashBoard::setscreen(const bool &screen)
{
    if (m_screen == screen)
        return;
    m_screen = screen;
    emit screenChanged(screen);
}

void DashBoard::setmaindashsetup(const QStringList &maindashsetup)
{
    if (m_maindashsetup == maindashsetup)
        return;
    m_maindashsetup = maindashsetup;
    emit maindashsetupChanged(maindashsetup);
}

void DashBoard::setdashsetup3(const QStringList &dashsetup3)
{
    if (m_dashsetup3 == dashsetup3)
        return;
    m_dashsetup3 = dashsetup3;
    emit dashsetup3Changed(dashsetup3);
}

void DashBoard::setdashsetup2(const QStringList &dashsetup2)
{
    if (m_dashsetup2 == dashsetup2)
        return;
    m_dashsetup2 = dashsetup2;
    emit dashsetup2Changed(dashsetup2);
}
void DashBoard::setdashsetup1(const QStringList &dashsetup1)
{
    if (m_dashsetup1 == dashsetup1)
        return;
    m_dashsetup1 = dashsetup1;
    emit dashsetup1Changed(dashsetup1);
}

void DashBoard::setdashfiles(const QStringList &dashfiles)
{
    if (m_dashfiles == dashfiles)
        return;
    m_dashfiles = dashfiles;
    emit dashfilesChanged(dashfiles);
}

void DashBoard::setbackroundpictures(const QStringList &backroundpictures)
{
    if (m_backroundpictures == backroundpictures)
        return;
    m_backroundpictures = backroundpictures;
    emit backroundpicturesChanged(backroundpictures);
}

void DashBoard::setaccelpedpos(const qreal &accelpedpos)
{
    if (m_accelpedpos == accelpedpos)
        return;
    m_accelpedpos = accelpedpos;
    emit accelpedposChanged(accelpedpos);
}
void DashBoard::setairtempensor2(const qreal &airtempensor2)
{
    if (m_airtempensor2 == airtempensor2)
        return;
    if (m_units == "metric")
    {m_airtempensor2 = airtempensor2;}
    if (m_units == "imperial")
    {m_airtempensor2 = airtempensor2 * 1.8 + 32;}
    emit airtempensor2Changed(airtempensor2);
}
void DashBoard::setantilaglauchswitch(const qreal &antilaglauchswitch)
{
    if (m_antilaglauchswitch == antilaglauchswitch)
        return;
    m_antilaglauchswitch = antilaglauchswitch;
    emit antilaglauchswitchChanged(antilaglauchswitch);
}
void DashBoard::setantilaglaunchon(const qreal &antilaglaunchon)
{
    if (m_antilaglaunchon == antilaglaunchon)
        return;
    m_antilaglaunchon = antilaglaunchon;
    emit antilaglaunchonChanged(antilaglaunchon);
}
void DashBoard::setauxrevlimitswitch(const qreal &auxrevlimitswitch)
{
    if (m_auxrevlimitswitch == auxrevlimitswitch)
        return;
    m_auxrevlimitswitch = auxrevlimitswitch;
    emit auxrevlimitswitchChanged(auxrevlimitswitch);
}
void DashBoard::setavfueleconomy(const qreal &avfueleconomy)
{
    if (m_avfueleconomy == avfueleconomy)
        return;
    m_avfueleconomy = avfueleconomy;
    emit avfueleconomyChanged(avfueleconomy);
}
void DashBoard::setbattlight(const qreal &battlight)
{
    if (m_battlight == battlight)
        return;
    m_battlight = battlight;
    emit battlightChanged(battlight);
}
void DashBoard::setboostcontrol(const qreal &boostcontrol)
{
    if (m_boostcontrol == boostcontrol)
        return;
    m_boostcontrol = boostcontrol;
    emit boostcontrolChanged(boostcontrol);
}
void DashBoard::setbrakepress(const qreal &brakepress)
{
    if (m_brakepress == brakepress)
        return;
    if (m_pressureunits == "metric")
    { m_brakepress = brakepress;}
    if (m_pressureunits == "imperial")
    {m_brakepress = brakepress * 0.145038;}
    emit brakepressChanged(brakepress);
}
void DashBoard::setclutchswitchstate(const qreal &clutchswitchstate)
{
    if (m_clutchswitchstate == clutchswitchstate)
        return;
    m_clutchswitchstate = clutchswitchstate;
    emit clutchswitchstateChanged(clutchswitchstate);
}
void DashBoard::setcoolantpress(const qreal &coolantpress)
{
    if (m_coolantpress == coolantpress)
        return;
    if (m_pressureunits == "metric")
    { m_coolantpress = coolantpress;}
    if (m_pressureunits == "imperial")
    {m_coolantpress = coolantpress * 0.145038;}
    emit coolantpressChanged(coolantpress);
}
void DashBoard::setdecelcut(const qreal &decelcut)
{
    if (m_decelcut == decelcut)
        return;
    m_decelcut = decelcut;
    emit decelcutChanged(decelcut);
}
void DashBoard::setdiffoiltemp(const qreal &diffoiltemp)
{
    if (m_diffoiltemp == diffoiltemp)
        return;
    if (m_units == "metric")
    {m_diffoiltemp = diffoiltemp;}
    if (m_units == "imperial")
    {m_diffoiltemp = diffoiltemp * 1.8 + 32;}
    emit diffoiltempChanged(diffoiltemp);
}
void DashBoard::setdistancetoempty(const qreal &distancetoempty)
{
    if (m_distancetoempty == distancetoempty)
        return;
    m_distancetoempty = distancetoempty;
    emit distancetoemptyChanged(distancetoempty);
}
void DashBoard::setegt1(const qreal &egt1)
{
    if (m_egt1 == egt1)
        return;
    if (m_units == "metric")
    {m_egt1 = egt1;}
    if (m_units == "imperial")
    {m_egt1 = qRound(egt1 * 1.8 + 32);}
    emit egt1Changed(egt1);
}
void DashBoard::setegt2(const qreal &egt2)
{
    if (m_egt2 == egt2)
        return;
    if (m_units == "metric")
    {m_egt2 = egt2;}
    if (m_units == "imperial")
    {m_egt2 = qRound(egt2 * 1.8 + 32);}
    emit egt2Changed(egt2);
}
void DashBoard::setegt3(const qreal &egt3)
{
    if (m_egt3 == egt3)
        return;
    if (m_units == "metric")
    {m_egt3 = egt3;}
    if (m_units == "imperial")
    {m_egt3 = qRound(egt3 * 1.8 + 32);}
    emit egt3Changed(egt3);
}
void DashBoard::setegt4(const qreal &egt4)
{
    if (m_egt4 == egt4)
        return;
    if (m_units == "metric")
    {m_egt4 = egt4;}
    if (m_units == "imperial")
    {m_egt4 = qRound(egt4 * 1.8 + 32);}
    emit egt4Changed(egt4);
}
void DashBoard::setegt5(const qreal &egt5)
{
    if (m_egt5 == egt5)
        return;
    if (m_units == "metric")
    {m_egt5 = egt5;}
    if (m_units == "imperial")
    {m_egt5 = qRound(egt5 * 1.8 + 32);}
    emit egt5Changed(egt5);
}
void DashBoard::setegt6(const qreal &egt6)
{
    if (m_egt6 == egt6)
        return;
    if (m_units == "metric")
    {m_egt6 = egt6;}
    if (m_units == "imperial")
    {m_egt6 = qRound(egt6 * 1.8 + 32);}
    emit egt6Changed(egt6);
}
void DashBoard::setegt7(const qreal &egt7)
{
    if (m_egt7 == egt7)
        return;
    if (m_units == "metric")
    {m_egt7 = egt7;}
    if (m_units == "imperial")
    {m_egt7 = qRound(egt7 * 1.8 + 32);}
    emit egt7Changed(egt7);
}
void DashBoard::setegt8(const qreal &egt8)
{
    if (m_egt8 == egt8)
        return;
    if (m_units == "metric")
    {m_egt8 = egt8;}
    if (m_units == "imperial")
    {m_egt8 = qRound(egt8 * 1.8 + 32);}
    emit egt8Changed(egt8);
}
void DashBoard::setegt9(const qreal &egt9)
{
    if (m_egt9 == egt9)
        return;
    if (m_units == "metric")
    {m_egt9 = egt9;}
    if (m_units == "imperial")
    {m_egt9 = qRound(egt9 * 1.8 + 32);}
    emit egt9Changed(egt9);
}
void DashBoard::setegt10(const qreal &egt10)
{
    if (m_egt10 == egt10)
        return;
    if (m_units == "metric")
    {m_egt10 = egt10;}
    if (m_units == "imperial")
    {m_egt10 = qRound(egt10 * 1.8 + 32);}
    emit egt10Changed(egt10);
}
void DashBoard::setegt11(const qreal &egt11)
{
    if (m_egt11 == egt11)
        return;
    if (m_units == "metric")
    {m_egt11 = egt11;}
    if (m_units == "imperial")
    {m_egt11 = qRound(egt11 * 1.8 + 32);}
    emit egt11Changed(egt11);
}
void DashBoard::setegt12(const qreal &egt12)
{
    if (m_egt12 == egt12)
        return;
    if (m_units == "metric")
    {m_egt12 = egt12;}
    if (m_units == "imperial")
    {m_egt12 = qRound(egt12 * 1.8 + 32);}
    emit egt12Changed(egt12);
}
void DashBoard::setexcamangle1(const qreal &excamangle1)
{
    if (m_excamangle1 == excamangle1)
        return;
    m_excamangle1 = excamangle1;
    emit excamangle1Changed(excamangle1);
}
void DashBoard::setexcamangle2(const qreal &excamangle2)
{
    if (m_excamangle2 == excamangle2)
        return;
    m_excamangle2 = excamangle2;
    emit excamangle2Changed(excamangle2);
}
void DashBoard::setflatshiftstate(const qreal &flatshiftstate)
{
    if (m_flatshiftstate == flatshiftstate)
        return;
    m_flatshiftstate = flatshiftstate;
    emit flatshiftstateChanged(flatshiftstate);
}
void DashBoard::setfuelclevel(const qreal &fuelclevel)
{
    if (m_fuelclevel == fuelclevel)
        return;
    m_fuelclevel = fuelclevel;
    emit fuelclevelChanged(fuelclevel);
}
void DashBoard::setfuelcomposition(const qreal &fuelcomposition)
{
    if (m_fuelcomposition == fuelcomposition)
        return;
    m_fuelcomposition = fuelcomposition;
    emit fuelcompositionChanged(fuelcomposition);
}
void DashBoard::setfuelconsrate(const qreal &fuelconsrate)
{
    if (m_fuelconsrate == fuelconsrate)
        return;
    m_fuelconsrate = fuelconsrate;
    emit fuelconsrateChanged(fuelconsrate);
}
void DashBoard::setfuelcutperc(const qreal &fuelcutperc)
{
    if (m_fuelcutperc == fuelcutperc)
        return;
    m_fuelcutperc = fuelcutperc;
    emit fuelcutpercChanged(fuelcutperc);
}
void DashBoard::setfuelflow(const qreal &fuelflow)
{
    if (m_fuelflow == fuelflow)
        return;
    m_fuelflow = fuelflow;
    emit fuelflowChanged(fuelflow);
}
void DashBoard::setfuelflowdiff(const qreal &fuelflowdiff)
{
    if (m_fuelflowdiff == fuelflowdiff)
        return;
    m_fuelflowdiff = fuelflowdiff;
    emit fuelflowdiffChanged(fuelflowdiff);
}
void DashBoard::setfuelflowret(const qreal &fuelflowret)
{
    if (m_fuelflowret == fuelflowret)
        return;
    m_fuelflowret = fuelflowret;
    emit fuelflowretChanged(fuelflowret);
}
void DashBoard::setfueltrimlongtbank1(const qreal &fueltrimlongtbank1)
{
    if (m_fueltrimlongtbank1 == fueltrimlongtbank1)
        return;
    m_fueltrimlongtbank1 = fueltrimlongtbank1;
    emit fueltrimlongtbank1Changed(fueltrimlongtbank1);
}
void DashBoard::setfueltrimlongtbank2(const qreal &fueltrimlongtbank2)
{
    if (m_fueltrimlongtbank2 == fueltrimlongtbank2)
        return;
    m_fueltrimlongtbank2 = fueltrimlongtbank2;
    emit fueltrimlongtbank2Changed(fueltrimlongtbank2);
}
void DashBoard::setfueltrimshorttbank1(const qreal &fueltrimshorttbank1)
{
    if (m_fueltrimshorttbank1 == fueltrimshorttbank1)
        return;
    m_fueltrimshorttbank1 = fueltrimshorttbank1;
    emit fueltrimshorttbank1Changed(fueltrimshorttbank1);
}
void DashBoard::setfueltrimshorttbank2(const qreal &fueltrimshorttbank2)
{
    if (m_fueltrimshorttbank2 == fueltrimshorttbank2)
        return;
    m_fueltrimshorttbank2 = fueltrimshorttbank2;
    emit fueltrimshorttbank2Changed(fueltrimshorttbank2);
}
void DashBoard::setgearswitch(const qreal &gearswitch)
{
    if (m_gearswitch == gearswitch)
        return;
    m_gearswitch = gearswitch;
    emit gearswitchChanged(gearswitch);
}
void DashBoard::sethandbrake(const qreal &handbrake)
{
    if (m_handbrake == handbrake)
        return;
    m_handbrake = handbrake;
    emit handbrakeChanged(handbrake);
}
void DashBoard::sethighbeam(const qreal &highbeam)
{
    if (m_highbeam == highbeam)
        return;
    m_highbeam = highbeam;
    emit highbeamChanged(highbeam);
}
void DashBoard::setlowBeam(const qreal &lowBeam)
{
    if (m_lowBeam == lowBeam)
        return;
    m_lowBeam = lowBeam;
    emit lowBeamChanged(lowBeam);
}
void DashBoard::settractionControl(const qreal &tractionControl)
{
    if (m_tractionControl == tractionControl)
        return;
    m_tractionControl = tractionControl;
    emit tractionControlChanged(tractionControl);
}

void DashBoard::sethomeccounter(const qreal &homeccounter)
{
    if (m_homeccounter == homeccounter)
        return;
    m_homeccounter = homeccounter;
    emit homeccounterChanged(homeccounter);
}
void DashBoard::setincamangle1(const qreal &incamangle1)
{
    if (m_incamangle1 == incamangle1)
        return;
    m_incamangle1 = incamangle1;
    emit incamangle1Changed(incamangle1);
}
void DashBoard::setincamangle2(const qreal &incamangle2)
{
    if (m_incamangle2 == incamangle2)
        return;
    m_incamangle2 = incamangle2;
    emit incamangle2Changed(incamangle2);
}
void DashBoard::setknocklevlogged1(const qreal &knocklevlogged1)
{
    if (m_knocklevlogged1 == knocklevlogged1)
        return;
    m_knocklevlogged1 = knocklevlogged1;
    emit knocklevlogged1Changed(knocklevlogged1);
}
void DashBoard::setknocklevlogged2(const qreal &knocklevlogged2)
{
    if (m_knocklevlogged2 == knocklevlogged2)
        return;
    m_knocklevlogged2 = knocklevlogged2;
    emit knocklevlogged2Changed(knocklevlogged2);
}
void DashBoard::setknockretardbank1(const qreal &knockretardbank1)
{
    if (m_knockretardbank1 == knockretardbank1)
        return;
    m_knockretardbank1 = knockretardbank1;
    emit knockretardbank1Changed(knockretardbank1);
}
void DashBoard::setknockretardbank2(const qreal &knockretardbank2)
{
    if (m_knockretardbank2 == knockretardbank2)
        return;
    m_knockretardbank2 = knockretardbank2;
    emit knockretardbank2Changed(knockretardbank2);
}
void DashBoard::setlambda2(const qreal &lambda2)
{
    if (m_lambda2 == lambda2)
        return;
    m_lambda2 = lambda2* lamdamultiplicator;
    emit lambda2Changed(m_lambda2);
}
void DashBoard::setlambda3(const qreal &lambda3)
{
    if (m_lambda3 == lambda3)
        return;
    m_lambda3 = lambda3* lamdamultiplicator;
    emit lambda3Changed(m_lambda3);
}
void DashBoard::setlambda4(const qreal &lambda4)
{
    if (m_lambda4 == lambda4)
        return;
    m_lambda4 = lambda4 * lamdamultiplicator;
    emit lambda4Changed(m_lambda4);
}
void DashBoard::setlaunchcontolfuelenrich(const qreal &launchcontolfuelenrich)
{
    if (m_launchcontolfuelenrich == launchcontolfuelenrich)
        return;
    m_launchcontolfuelenrich = launchcontolfuelenrich;
    emit launchcontolfuelenrichChanged(launchcontolfuelenrich);
}
void DashBoard::setlaunchctrolignretard(const qreal &launchctrolignretard)
{
    if (m_launchctrolignretard == launchctrolignretard)
        return;
    m_launchctrolignretard = launchctrolignretard;
    emit launchctrolignretardChanged(launchctrolignretard);
}
void DashBoard::setleftindicator(const qreal &leftindicator)
{
    if (m_leftindicator == leftindicator)
        return;
    m_leftindicator = leftindicator;
    emit leftindicatorChanged(leftindicator);
}
void DashBoard::setlimpmode(const qreal &limpmode)
{
    if (m_limpmode == limpmode)
        return;
    m_limpmode = limpmode;
    emit limpmodeChanged(limpmode);
}
void DashBoard::setmil(const qreal &mil)
{
    if (m_mil == mil)
        return;
    m_mil = mil;
    emit milChanged(mil);
}
void DashBoard::setmissccount(const qreal &missccount)
{
    if (m_missccount == missccount)
        return;
    m_missccount = missccount;
    emit missccountChanged(missccount);
}
void DashBoard::setnosactive(const qreal &nosactive)
{
    if (m_nosactive == nosactive)
        return;
    m_nosactive = nosactive;
    emit nosactiveChanged(nosactive);
}
void DashBoard::setnospress(const qreal &nospress)
{
    if (m_nospress == nospress)
        return;
    if (m_pressureunits == "metric")
    { m_nospress = nospress;}
    if (m_pressureunits == "imperial")
    {m_nospress = nospress * 0.145038;}
    emit nospressChanged(nospress);
}
void DashBoard::setnosswitch(const qreal &nosswitch)
{
    if (m_nosswitch == nosswitch)
        return;
    m_nosswitch = nosswitch;
    emit nosswitchChanged(nosswitch);
}
void DashBoard::setoilpres(const qreal &oilpres)
{
    if (m_oilpres == oilpres)
        return;
    if (m_pressureunits == "metric")
    { m_oilpres = oilpres;}
    if (m_pressureunits == "imperial")
    {m_oilpres = oilpres * 0.145038;}
    emit oilpresChanged(oilpres);
}
void DashBoard::setoiltemp(const qreal &oiltemp)
{
    if (m_oiltemp == oiltemp)
        return;
    if (m_units == "metric")
    {m_oiltemp = oiltemp;}
    if (m_units == "imperial")
    {m_oiltemp = oiltemp * 1.8 + 32;}
    emit oiltempChanged(oiltemp);
}
void DashBoard::setrallyantilagswitch(const qreal &rallyantilagswitch)
{
    if (m_rallyantilagswitch == rallyantilagswitch)
        return;
    m_rallyantilagswitch = rallyantilagswitch;
    emit rallyantilagswitchChanged(rallyantilagswitch);
}
void DashBoard::setrightindicator(const qreal &rightindicator)
{
    if (m_rightindicator == rightindicator)
        return;
    m_rightindicator = rightindicator;
    emit rightindicatorChanged(rightindicator);
}
void DashBoard::settargetbstlelkpa(const qreal &targetbstlelkpa)
{
    if (m_targetbstlelkpa == targetbstlelkpa)
        return;
    m_targetbstlelkpa = targetbstlelkpa;
    emit targetbstlelkpaChanged(targetbstlelkpa);
}
void DashBoard::settimeddutyout1(const qreal &timeddutyout1)
{
    if (m_timeddutyout1 == timeddutyout1)
        return;
    m_timeddutyout1 = timeddutyout1;
    emit timeddutyout1Changed(timeddutyout1);
}
void DashBoard::settimeddutyout2(const qreal &timeddutyout2)
{
    if (m_timeddutyout2 == timeddutyout2)
        return;
    m_timeddutyout2 = timeddutyout2;
    emit timeddutyout2Changed(timeddutyout2);
}
void DashBoard::settimeddutyoutputactive(const qreal &timeddutyoutputactive)
{
    if (m_timeddutyoutputactive == timeddutyoutputactive)
        return;
    m_timeddutyoutputactive = timeddutyoutputactive;
    emit timeddutyoutputactiveChanged(timeddutyoutputactive);
}
void DashBoard::settorqueredcutactive(const qreal &torqueredcutactive)
{
    if (m_torqueredcutactive == torqueredcutactive)
        return;
    m_torqueredcutactive = torqueredcutactive;
    emit torqueredcutactiveChanged(torqueredcutactive);
}
void DashBoard::settorqueredlevelactive(const qreal &torqueredlevelactive)
{
    if (m_torqueredlevelactive == torqueredlevelactive)
        return;
    m_torqueredlevelactive = torqueredlevelactive;
    emit torqueredlevelactiveChanged(torqueredlevelactive);
}
void DashBoard::settransientthroactive(const qreal &transientthroactive)
{
    if (m_transientthroactive == transientthroactive)
        return;
    m_transientthroactive = transientthroactive;
    emit transientthroactiveChanged(transientthroactive);
}
void DashBoard::settransoiltemp(const qreal &transoiltemp)
{
    if (m_transoiltemp == transoiltemp)
        return;
    if (m_units == "metric")
    {m_transoiltemp = transoiltemp;}
    if (m_units == "imperial")
    {m_transoiltemp = transoiltemp * 1.8 + 32;}
    emit transoiltempChanged(transoiltemp);
}
void DashBoard::settriggerccounter(const qreal &triggerccounter)
{
    if (m_triggerccounter == triggerccounter)
        return;
    m_triggerccounter = triggerccounter;
    emit triggerccounterChanged(triggerccounter);
}
void DashBoard::settriggersrsinceasthome(const qreal &triggersrsinceasthome)
{
    if (m_triggersrsinceasthome == triggersrsinceasthome)
        return;
    m_triggersrsinceasthome = triggersrsinceasthome;
    emit triggersrsinceasthomeChanged(triggersrsinceasthome);
}
void DashBoard::setturborpm(const qreal &turborpm)
{
    if (m_turborpm == turborpm)
        return;
    m_turborpm = turborpm;
    emit turborpmChanged(turborpm);
}
void DashBoard::setturborpm2(const qreal &turborpm2)
{
    if (m_turborpm2 == turborpm2)
        return;
    m_turborpm2 = turborpm2;
    emit turborpm2Changed(turborpm2);
}


void DashBoard::setwastegatepress(const qreal &wastegatepress)
{
    if (m_wastegatepress == wastegatepress)
        return;
    if (m_units == "metric")
    { m_wastegatepress = wastegatepress;}
    if (m_units == "imperial")
    {m_wastegatepress = wastegatepress * 0.145038;}
    emit wastegatepressChanged(wastegatepress);
}
void DashBoard::setwheeldiff(const qreal &wheeldiff)
{
    if (m_wheeldiff == wheeldiff)
        return;
    if (m_speedunits == "metric")
    {m_wheeldiff = wheeldiff * m_speedpercent;}
    if (m_speedunits == "imperial")
    {m_wheeldiff = qRound((wheeldiff * 0.621371) * m_speedpercent);}
    emit wheeldiffChanged(wheeldiff);
}
void DashBoard::setwheelslip(const qreal &wheelslip)
{
    if (m_wheelslip == wheelslip)
        return;
    if (m_speedunits == "metric")
    {m_wheelslip = wheelslip * m_speedpercent;}
    if (m_speedunits == "imperial")
    {m_wheelslip = qRound((wheelslip * 0.621371) * m_speedpercent);}
    emit wheelslipChanged(m_wheelslip);
}
void DashBoard::setwheelspdftleft(const qreal &wheelspdftleft)
{
    if (m_wheelspdftleft == wheelspdftleft)
        return;
    m_wheelspdftleft = wheelspdftleft * m_speedpercent;
    if (m_speedunits == "metric")
    {m_wheelspdftleft = wheelspdftleft * m_speedpercent;}
    if (m_speedunits == "imperial")
    {m_wheelspdftleft = qRound((wheelspdftleft * 0.621371) * m_speedpercent);}
    emit wheelspdftleftChanged(m_wheelspdftleft);
    if (m_ExternalSpeed == 1){
    m_speed = m_wheelspdftleft;
    emit speedChanged(m_wheelspdftleft);
    }

}
void DashBoard::setwheelspdftright(const qreal &wheelspdftright)
{
    if (m_wheelspdftright == wheelspdftright)
        return;
    m_wheelspdftright = wheelspdftright * m_speedpercent;
    if (m_speedunits == "metric")
    {m_wheelspdftright = wheelspdftright * m_speedpercent;}
    if (m_speedunits == "imperial")
    {m_wheelspdftright = qRound((wheelspdftright * 0.621371) * m_speedpercent);}
    emit wheelspdftrightChanged(m_wheelspdftright);
    if (m_ExternalSpeed == 2){
        m_speed = m_wheelspdftright;
        emit speedChanged(m_wheelspdftright);
    }
}

void DashBoard::setwheelspdrearleft(const qreal &wheelspdrearleft)
{
    if (m_wheelspdrearleft == wheelspdrearleft)
        return;
    m_wheelspdrearleft = wheelspdrearleft * m_speedpercent;
    if (m_speedunits == "metric")
    {m_wheelspdrearleft = wheelspdrearleft * m_speedpercent;}
    if (m_speedunits == "imperial")
    {m_wheelspdrearleft = qRound((wheelspdrearleft * 0.621371) * m_speedpercent);}
    emit wheelspdrearleftChanged(wheelspdrearleft);
    if (m_ExternalSpeed == 3){
        m_speed = m_wheelspdrearleft;
        emit speedChanged(m_wheelspdrearleft);
    }
}
void DashBoard::setwheelspdrearright(const qreal &wheelspdrearright)
{
    if (m_wheelspdrearright == wheelspdrearright)
        return;
    m_wheelspdrearright = wheelspdrearright* m_speedpercent;
    if (m_speedunits == "metric")
    {m_wheelspdrearright = wheelspdrearright * m_speedpercent;}
    if (m_speedunits == "imperial")
    {m_wheelspdrearright = qRound((wheelspdrearright * 0.621371) * m_speedpercent);}
    emit wheelspdrearrightChanged(m_wheelspdrearright);
    if (m_ExternalSpeed == 4){
        m_speed = m_wheelspdrearright;
        emit speedChanged(m_wheelspdrearright);
    }
}
void DashBoard::setmusicpath(const QString &musicpath)
{
    if (m_musicpath == musicpath)
        return;
    m_musicpath = musicpath;
    emit musicpathChanged(musicpath);
}
void DashBoard::setsupportedReg(const int &supportedReg)
{
    if (m_supportedReg == supportedReg)
        return;
    m_supportedReg = supportedReg;
    emit supportedRegChanged(supportedReg);
}
void DashBoard::setspeedpercent(const qreal &speedpercent)
{
    if (m_speedpercent == speedpercent)
        return;
    m_speedpercent = speedpercent;
    emit speedpercentChanged(speedpercent);
}

//

void DashBoard::setmaxRPM(const int &maxRPM)
{
    if (m_maxRPM == maxRPM)
        return;
    m_maxRPM = maxRPM;
    emit maxRPMChanged(maxRPM);
}

void DashBoard::setrpmStage1(const int &rpmStage1)
{
    if (m_rpmStage1 == rpmStage1)
        return;
    m_rpmStage1 = rpmStage1;
    emit rpmStage1Changed(rpmStage1);
}
void DashBoard::setrpmStage2(const int &rpmStage2)
{
    if (m_rpmStage2 == rpmStage2)
        return;
    m_rpmStage2 = rpmStage2;
    emit rpmStage2Changed(rpmStage2);
}
void DashBoard::setrpmStage3(const int &rpmStage3)
{
    if (m_rpmStage3 == rpmStage3)
        return;
    m_rpmStage3 = rpmStage3;
    emit rpmStage3Changed(rpmStage3);
}
void DashBoard::setrpmStage4(const int &rpmStage4)
{
    if (m_rpmStage4 == rpmStage4)
        return;
    m_rpmStage4 = rpmStage4;
    emit rpmStage4Changed(rpmStage4);
}

//
void DashBoard::setwaterwarn(const int &waterwarn)
{
    if (m_waterwarn == waterwarn)
        return;
    m_waterwarn = waterwarn;
    emit waterwarnChanged(waterwarn);
}
void DashBoard::setrpmwarn(const int &rpmwarn)
{
    if (m_rpmwarn == rpmwarn)
        return;
    m_rpmwarn = rpmwarn;
    emit rpmwarnChanged(rpmwarn);
}
void DashBoard::setknockwarn(const int &knockwarn)
{
    if (m_knockwarn == knockwarn)
        return;
    m_knockwarn = knockwarn;
    emit knockwarnChanged(knockwarn);
}
void DashBoard::setboostwarn(const qreal &boostwarn)
{
    if (m_boostwarn == boostwarn)
        return;
    m_boostwarn = boostwarn;
    emit boostwarnChanged(boostwarn);
}
void DashBoard::setsmoothrpm(const int &smoothrpm)
{
    if (m_smoothrpm == smoothrpm)
        return;
    if (smoothrpm != 0)
    {m_smoothrpm = smoothrpm+1;}
    else {m_smoothrpm = smoothrpm;}
    //qDebug()<<"SmoothRPM" << m_smoothrpm;
    averageRPM.resize(m_smoothrpm);
    emit smoothrpmChanged(smoothrpm);
}
void DashBoard::setsmoothspeed(const int &smoothspeed)
{
    if (m_smoothspeed == smoothspeed)
        return;
    if (smoothspeed != 0)
    {m_smoothspeed = smoothspeed+1;}
    else {m_smoothspeed = smoothspeed;}
    averageSpeed.resize(m_smoothspeed);
    //qDebug()<<"SmoothSpeed" << m_smoothrpm;
    emit smoothspeedChanged(smoothspeed);
}

void DashBoard::setsmootexAnalogInput7(const int &smoothexAnalogInput7)
{
    //qDebug()<<"Smootg" << smoothexAnalogInput7;
    if (m_smoothexAnalogInput7 == smoothexAnalogInput7)
        return;
    if (smoothexAnalogInput7 != 0)
    {m_smoothexAnalogInput7 = smoothexAnalogInput7+1;}
    else {m_smoothexAnalogInput7 = smoothexAnalogInput7;}
    averageexanaloginput7.resize(m_smoothexAnalogInput7);
    //qDebug()<<"SmoothSpeed" << m_smoothrpm;
    emit smootexAnalogInput7Changed(smoothexAnalogInput7);
}

void DashBoard::setgearcalc1(const int &gearcalc1)
{
    if (m_gearcalc1 == gearcalc1)
        return;
    m_gearcalc1 = gearcalc1;
    emit gearcalc1Changed(gearcalc1);
}
void DashBoard::setgearcalc2(const int &gearcalc2)
{
    if (m_gearcalc2 == gearcalc2)
        return;
    m_gearcalc2 = gearcalc2;
    emit gearcalc2Changed(gearcalc2);
}
void DashBoard::setgearcalc3(const int &gearcalc3)
{
    if (m_gearcalc3 == gearcalc3)
        return;
    m_gearcalc3 = gearcalc3;
    emit gearcalc3Changed(gearcalc3);
}
void DashBoard::setgearcalc4(const int &gearcalc4)
{
    if (m_gearcalc4 == gearcalc4)
        return;
    m_gearcalc4 = gearcalc4;
    emit gearcalc4Changed(gearcalc4);
}
void DashBoard::setgearcalc5(const int &gearcalc5)
{
    if (m_gearcalc5 == gearcalc5)
        return;
    m_gearcalc5 = gearcalc5;
    emit gearcalc5Changed(gearcalc5);
}
void DashBoard::setgearcalc6(const int &gearcalc6)
{
    if (m_gearcalc6 == gearcalc6)
        return;
    m_gearcalc6 = gearcalc6;
    emit gearcalc6Changed(gearcalc6);
}
void DashBoard::setgearcalcactivation(const int &gearcalcactivation)
{
    if (m_gearcalcactivation == gearcalcactivation)
        return;
    m_gearcalcactivation = gearcalcactivation;
    emit gearcalcactivationChanged(gearcalcactivation);
}

void DashBoard::setecu(const int &ecu)
{
    if (m_ecu == ecu)
        return;
    m_ecu = ecu;
    emit ecuChanged(ecu);
}
void DashBoard::setrpmstyle1(const int &rpmstyle1)
{
    if (m_rpmstyle1 == rpmstyle1)
        return;
    m_rpmstyle1 = rpmstyle1;
    emit rpmstyle1Changed(rpmstyle1);
}
void DashBoard::setrpmstyle2(const int &rpmstyle2)
{
    if (m_rpmstyle2 == rpmstyle2)
        return;
    m_rpmstyle2 = rpmstyle2;
    emit rpmstyle2Changed(rpmstyle2);
}
void DashBoard::setrpmstyle3(const int &rpmstyle3)
{
    if (m_rpmstyle3 == rpmstyle3)
        return;
    m_rpmstyle3 = rpmstyle3;
    emit rpmstyle3Changed(rpmstyle3);
}

void DashBoard::setRotaryTrimpot1(const int &RotaryTrimpot1)
{
    if (m_RotaryTrimpot1 == RotaryTrimpot1)
        return;
    m_RotaryTrimpot1 = RotaryTrimpot1;
    emit RotaryTrimpot1Changed(RotaryTrimpot1);
}

void DashBoard::setRotaryTrimpot2(const int &RotaryTrimpot2)
{
    if (m_RotaryTrimpot2 == RotaryTrimpot2)
        return;
    m_RotaryTrimpot2 = RotaryTrimpot2;
    emit RotaryTrimpot2Changed(RotaryTrimpot2);
}

void DashBoard::setRotaryTrimpot3(const int &RotaryTrimpot3)
{
    if (m_RotaryTrimpot3 == RotaryTrimpot3)
        return;
    m_RotaryTrimpot3 = RotaryTrimpot3;
    emit RotaryTrimpot3Changed(RotaryTrimpot3);
}

void DashBoard::setCalibrationSelect(const int &CalibrationSelect)
{
    if (m_CalibrationSelect == CalibrationSelect)
        return;
    m_CalibrationSelect = CalibrationSelect;
    emit CalibrationSelectChanged(CalibrationSelect);
}

void DashBoard::setError(const QString &Error)
{
    if (m_ecu == Error)
        return;
    m_Error = Error;
    emit ErrorChanged(Error);
}
void DashBoard::setautogear(const QString &autogear)
{
    if (m_autogear == autogear)
        return;
    m_autogear = autogear;
    emit autogearChanged(autogear);
}

void DashBoard::setExternalSpeed(const int &ExternalSpeed)
{
    if (m_ExternalSpeed == ExternalSpeed)
        return;
    m_ExternalSpeed = ExternalSpeed;
    emit ExternalSpeedChanged(ExternalSpeed);
}

void DashBoard::setcurrentLap(const int &currentLap)
{
    if (m_currentLap == currentLap)
        return;
    m_currentLap = currentLap;
    emit currentLapChanged(currentLap);
}

void DashBoard::setlaptime(const QString &laptime)
{
    if (m_laptime == laptime)
        return;
    m_laptime = laptime;
    emit laptimeChanged(laptime);
}
void DashBoard::setLastlaptime(const QString &Lastlaptime)
{
    if (m_Lastlaptime == Lastlaptime)
        return;
    m_Lastlaptime = Lastlaptime;
    emit LastlaptimeChanged(Lastlaptime);
}
void DashBoard::setbestlaptime(const QString &bestlaptime)
{
    if (m_bestlaptime == bestlaptime)
        return;
    m_bestlaptime = bestlaptime;
    emit bestlaptimeChanged(bestlaptime);
}

void DashBoard::setdraggable(const int &draggable)
{
    if (m_draggable == draggable)
        return;
    m_draggable = draggable;
    emit draggableChanged(draggable);
}
void DashBoard::setwifi(const QStringList &wifi)
{
    if (m_wifi== wifi)
        return;
    m_wifi = wifi;
    emit wifiChanged(wifi);
}
void DashBoard::setAnalog0(const qreal &Analog0)
{
    if (m_Analog0== Analog0)
        return;
    m_Analog0 = Analog0;
    emit Analog0Changed(Analog0);
    setAnalogCalc0(((AN05-AN00)*0.2)*Analog0+AN00);

}
void DashBoard::setAnalog1(const qreal &Analog1)
{
    if (m_Analog1== Analog1)
        return;
    m_Analog1 = Analog1;
    emit Analog1Changed(Analog1);
    setAnalogCalc1(((AN15-AN10)*0.2)*Analog1+AN10);
}
void DashBoard::setAnalog2(const qreal &Analog2)
{
    if (m_Analog2 == Analog2)
        return;
    m_Analog2 = Analog2;
    emit Analog2Changed(Analog2);
    setAnalogCalc2(((AN25-AN20)*0.2)*Analog2+AN20);
}
void DashBoard::setAnalog3(const qreal &Analog3)
{
    if (m_Analog3 == Analog3)
        return;
    m_Analog3 = Analog3;
    emit Analog3Changed(Analog3);
    setAnalogCalc3(((AN35-AN30)*0.2)*Analog3+AN30);
}
void DashBoard::setAnalog4(const qreal &Analog4)
{
    if (m_Analog4 == Analog4)
        return;
    m_Analog4 = Analog4;
    emit Analog4Changed(Analog4);
    setAnalogCalc4(((AN45-AN40)*0.2)*Analog4+AN40);
}
void DashBoard::setAnalog5(const qreal &Analog5)
{
    if (m_Analog5 == Analog5)
        return;
    m_Analog5 = Analog5;
    emit Analog5Changed(Analog5);
    setAnalogCalc5(((AN55-AN50)*0.2)*Analog5+AN50);
}
void DashBoard::setAnalog6(const qreal &Analog6)
{
    if (m_Analog6 == Analog6)
        return;
    m_Analog6 = Analog6;
    emit Analog6Changed(Analog6);
    setAnalogCalc6(((AN65-AN60)*0.2)*Analog6+AN60);
}
void DashBoard::setAnalog7(const qreal &Analog7)
{
    if (m_Analog7 == Analog7)
        return;
    m_Analog7 = Analog7;
    emit Analog7Changed(Analog7);
    setAnalogCalc7(((AN75-AN70)*0.2)*Analog7+AN70);
}
void DashBoard::setAnalog8(const qreal &Analog8)
{
    if (m_Analog8 == Analog8)
        return;
    m_Analog8 = Analog8;
    emit Analog8Changed(Analog8);
    setAnalogCalc8(((AN85-AN80)*0.2)*Analog8+AN80);
}
void DashBoard::setAnalog9(const qreal &Analog9)
{
    if (m_Analog9 == Analog9)
        return;
    m_Analog9 = Analog9;
    emit Analog9Changed(Analog9);
    setAnalogCalc9(((AN95-AN90)*0.2)*Analog9+AN90);
}
void DashBoard::setAnalog10(const qreal &Analog10)
{
    if (m_Analog10 == Analog10)
        return;
    m_Analog10 = Analog10;
    emit Analog10Changed(Analog10);
    setAnalogCalc10(((AN105-AN100)*0.2)*Analog10+AN100);
}
void DashBoard::setAnalogCalc0(const qreal &AnalogCalc0)
{
    if (m_AnalogCalc0 == AnalogCalc0)
        return;
    m_AnalogCalc0 = AnalogCalc0;
    emit AnalogCalc0Changed(AnalogCalc0);
}
void DashBoard::setAnalogCalc1(const qreal &AnalogCalc1)
{
    if (m_AnalogCalc1 == AnalogCalc1)
        return;
    m_AnalogCalc1 = AnalogCalc1;
    emit AnalogCalc1Changed(AnalogCalc1);
}
void DashBoard::setAnalogCalc2(const qreal &AnalogCalc2)
{
    if (m_AnalogCalc2 == AnalogCalc2)
        return;
    m_AnalogCalc2 = AnalogCalc2;
    emit AnalogCalc2Changed(AnalogCalc2);
}
void DashBoard::setAnalogCalc3(const qreal &AnalogCalc3)
{
    if (m_AnalogCalc3 == AnalogCalc3)
        return;
    m_AnalogCalc3 = AnalogCalc3;
    emit AnalogCalc3Changed(AnalogCalc3);
}
void DashBoard::setAnalogCalc4(const qreal &AnalogCalc4)
{
    if (m_AnalogCalc4 == AnalogCalc4)
        return;
    m_AnalogCalc4 = AnalogCalc4;
    emit AnalogCalc4Changed(AnalogCalc4);
}
void DashBoard::setAnalogCalc5(const qreal &AnalogCalc5)
{
    if (m_AnalogCalc5 == AnalogCalc5)
        return;
    m_AnalogCalc5 = AnalogCalc5;
    emit AnalogCalc5Changed(AnalogCalc5);
}
void DashBoard::setAnalogCalc6(const qreal &AnalogCalc6)
{
    if (m_AnalogCalc6 == AnalogCalc6)
        return;
    m_AnalogCalc6 = AnalogCalc6;
    emit AnalogCalc6Changed(AnalogCalc6);
}
void DashBoard::setAnalogCalc7(const qreal &AnalogCalc7)
{
    if (m_AnalogCalc7 == AnalogCalc7)
        return;
    m_AnalogCalc7 = AnalogCalc7;
    emit AnalogCalc7Changed(AnalogCalc7);
}
void DashBoard::setAnalogCalc8(const qreal &AnalogCalc8)
{
    if (m_AnalogCalc8 == AnalogCalc8)
        return;
    m_AnalogCalc8 = AnalogCalc8;
    emit AnalogCalc8Changed(AnalogCalc8);
}
void DashBoard::setAnalogCalc9(const qreal &AnalogCalc9)
{
    if (m_AnalogCalc9 == AnalogCalc9)
        return;
    m_AnalogCalc9 = AnalogCalc9;
    emit AnalogCalc9Changed(AnalogCalc9);
}
void DashBoard::setAnalogCalc10(const qreal &AnalogCalc10)
{
    if (m_AnalogCalc10 == AnalogCalc10)
        return;
    m_AnalogCalc10 = AnalogCalc10;
    emit AnalogCalc10Changed(AnalogCalc10);
}
// EX Board

void DashBoard::setEXAnalogInput0(const qreal &EXAnalogInput0)
{
    if (m_EXAnalogInput0== EXAnalogInput0)
        return;
    m_EXAnalogInput0 = EXAnalogInput0;
    emit EXAnalogInput0Changed(EXAnalogInput0);
    if (EXsteinhart0 == 0)
    {
    setEXAnalogCalc0(((EXAN05-EXAN00)*0.2)*EXAnalogInput0+EXAN00);
    }
    else
    {
 /*
  * Voltage Divider Circuit for Easier understanding
  * Is our Sensor thats connected to 5V and PIN 24
  * R2 is fixed
  * R3 is user Selectable ( 100 /1000 Ohm or no resistor)

                  |  Vin (+5V)
                  |
                 | |
                 | | R1 (Sensor with Variable Resistance)
                 | |
                  |
                  |-----------------------------------------------------------------o Voltage Measuring Point
             ---------------------o EX Analog input 0 (PIN24)
             |         |         |
             |		    /          /
             |		   /  Jumper  / Jumper
             |		   |         |
            | |       | |       | |
    R2	    | |       | |  R3   | |  R4
  1430 Ω	| |		  | | 100 Ω | | 1000 Ω
             |         |         |
             |         |         |
             ---------------------
                  |-----------------------------------------------------------------o Voltage Measuring Point
                  |
                -----   GND
                 ---
                  -

We already know the Values of Rw and R3 as well as Vin , now we need to calculate the Resistance of the sensor R1
*/
    //Calculate the resistance of a potential NTC at the Analog Input Whereby input voltage is 5V
    //Rtotal is the total Value of R2 / R3 / R4 in parallel
    //qreal Rtotal = (EXAnalogInput0 * VoltageDividerR1)/(5 - EXAnalogInput0);
    //R2 and R3 are in parallel
    //ResistanceEXAN0 = R1 (Sensor Resistance)
    //EXAnalogInput0 = Measured Voltage


    ResistanceEXAN0 = (Rtotalexan0 *(5-EXAnalogInput0))/EXAnalogInput0; // Calculating the Resistance of the Sensor R3
    //qDebug() <<"Sensor Ohms   :" << ResistanceEXAN0;
    qreal tempK = 1/(A0+(B0*log(ResistanceEXAN0)) + C0* pow(log(ResistanceEXAN0),3))-273.15; // Determine Temperature based on R3 Value with Steinhart Hart Formula

    if (m_units == "metric")
    { setEXAnalogCalc0(tempK);}
    if (m_units == "imperial")
    {setEXAnalogCalc0(tempK * 1.8 + 32);}
    }

}
void DashBoard::setEXAnalogInput1(const qreal &EXAnalogInput1)
{
    if (m_EXAnalogInput1== EXAnalogInput1)
        return;
    m_EXAnalogInput1 = EXAnalogInput1;
    emit EXAnalogInput1Changed(EXAnalogInput1);
    if (EXsteinhart1 == 0)
    {
    setEXAnalogCalc1(((EXAN15-EXAN10)*0.2)*EXAnalogInput1+EXAN10);
    }
    //Calculate the resistance of a potential NTC at the Analog Input Whereby input voltage is 5V and R1 = 1000 Ohm
    else
    {

    ResistanceEXAN1 = (Rtotalexan1 *(5-EXAnalogInput1))/EXAnalogInput1; // Calculating the Resistance of the Sensor R1
    qreal tempK = 1/(A1+(B1*log(ResistanceEXAN1)) + C1* pow(log(ResistanceEXAN1),3))-273.15;
    if (m_units == "metric")
    { setEXAnalogCalc1(tempK);}
    if (m_units == "imperial")
    {setEXAnalogCalc1(tempK * 1.8 + 32);}
    }
}

void DashBoard::setEXAnalogInput2(const qreal &EXAnalogInput2)
{
    if (m_EXAnalogInput2 == EXAnalogInput2)
        return;
    m_EXAnalogInput2 = EXAnalogInput2;
    emit EXAnalogInput2Changed(EXAnalogInput2);
    if (EXsteinhart2 == 0)
    {
    setEXAnalogCalc2(((EXAN25-AN20)*0.2)*EXAnalogInput2+EXAN20);
    }
    else
    {
    ResistanceEXAN2 = (Rtotalexan2 *(5-EXAnalogInput2))/EXAnalogInput2; // Calculating the Resistance of the Sensor R1
    qreal tempK = 1/(A2+(B2*log(ResistanceEXAN2)) + C2* pow(log(ResistanceEXAN2),3))-273.15;
    if (m_units == "metric")
    { setEXAnalogCalc2(tempK);}
    if (m_units == "imperial")
    {setEXAnalogCalc2(tempK * 1.8 + 32);}
    }
}
void DashBoard::setEXAnalogInput3(const qreal &EXAnalogInput3)
{
    if (m_EXAnalogInput3 == EXAnalogInput3)
        return;
    m_EXAnalogInput3 = EXAnalogInput3;
    emit EXAnalogInput3Changed(EXAnalogInput3);
    setEXAnalogCalc3(((EXAN35-EXAN30)*0.2)*EXAnalogInput3+EXAN30);
}
void DashBoard::setEXAnalogInput4(const qreal &EXAnalogInput4)
{
    if (m_EXAnalogInput4 == EXAnalogInput4)
        return;
    m_EXAnalogInput4 = EXAnalogInput4;
    emit EXAnalogInput4Changed(EXAnalogInput4);
    setEXAnalogCalc4(((EXAN45-EXAN40)*0.2)*EXAnalogInput4+EXAN40);
}
void DashBoard::setEXAnalogInput5(const qreal &EXAnalogInput5)
{
    if (m_EXAnalogInput5 == EXAnalogInput5)
        return;
    m_EXAnalogInput5 = EXAnalogInput5;
    emit EXAnalogInput5Changed(EXAnalogInput5);
    setEXAnalogCalc5(((EXAN55-EXAN50)*0.2)*EXAnalogInput5+EXAN50);
}
void DashBoard::setEXAnalogInput6(const qreal &EXAnalogInput6)
{
    if (m_EXAnalogInput6 == EXAnalogInput6)
        return;
    m_EXAnalogInput6 = EXAnalogInput6;
    emit EXAnalogInput6Changed(EXAnalogInput6);
    setEXAnalogCalc6(((EXAN65-EXAN60)*0.2)*EXAnalogInput6+EXAN60);
}
void DashBoard::setEXAnalogInput7(const qreal &EXAnalogInput7)
{
    if (m_EXAnalogInput7 == EXAnalogInput7)
        return;
    m_EXAnalogInput7 = EXAnalogInput7;
    //qDebug() << "Smooth ? " << m_smoothexAnalogInput7;
    if (m_smoothexAnalogInput7 != 0)
    {
        averageexanaloginput7.removeFirst();
        averageexanaloginput7.append(m_EXAnalogInput7);
        //qDebug() << "averageexanaloginput7 " << averageexanaloginput7;
        avgexanaloginput7 = 0;
        for (int i = 0; i <= m_smoothexAnalogInput7-1; i++){avgexanaloginput7+= averageexanaloginput7[i];}
        m_EXAnalogInput7 = avgexanaloginput7/m_smoothexAnalogInput7;
    }

    emit EXAnalogInput7Changed(m_EXAnalogInput7);
    setEXAnalogCalc7(((EXAN75-EXAN70)*0.2)*m_EXAnalogInput7+EXAN70);


}
void DashBoard::setEXAnalogCalc0(const qreal &EXAnalogCalc0)
{
    if (m_EXAnalogCalc0 == EXAnalogCalc0)
        return;
    m_EXAnalogCalc0 = EXAnalogCalc0;
    emit EXAnalogCalc0Changed(EXAnalogCalc0);
}
void DashBoard::setEXAnalogCalc1(const qreal &EXAnalogCalc1)
{
    if (m_EXAnalogCalc1 == EXAnalogCalc1)
        return;
    m_EXAnalogCalc1 = EXAnalogCalc1;
    emit EXAnalogCalc1Changed(EXAnalogCalc1);
}
void DashBoard::setEXAnalogCalc2(const qreal &EXAnalogCalc2)
{
    if (m_EXAnalogCalc2 == EXAnalogCalc2)
        return;
    m_EXAnalogCalc2 = EXAnalogCalc2;
    emit EXAnalogCalc2Changed(EXAnalogCalc2);
}
void DashBoard::setEXAnalogCalc3(const qreal &EXAnalogCalc3)
{
    if (m_EXAnalogCalc3 == EXAnalogCalc3)
        return;
    m_EXAnalogCalc3 = EXAnalogCalc3;
    emit EXAnalogCalc3Changed(EXAnalogCalc3);
}
void DashBoard::setEXAnalogCalc4(const qreal &EXAnalogCalc4)
{
    if (m_EXAnalogCalc4 == EXAnalogCalc4)
        return;
    m_EXAnalogCalc4 = EXAnalogCalc4;
    emit EXAnalogCalc4Changed(EXAnalogCalc4);
}
void DashBoard::setEXAnalogCalc5(const qreal &EXAnalogCalc5)
{
    if (m_EXAnalogCalc5 == EXAnalogCalc5)
        return;
    m_EXAnalogCalc5 = EXAnalogCalc5;
    emit EXAnalogCalc5Changed(EXAnalogCalc5);
}
void DashBoard::setEXAnalogCalc6(const qreal &EXAnalogCalc6)
{
    if (m_EXAnalogCalc6 == EXAnalogCalc6)
        return;
    m_EXAnalogCalc6 = EXAnalogCalc6;
    emit EXAnalogCalc6Changed(EXAnalogCalc6);
}
void DashBoard::setEXAnalogCalc7(const qreal &EXAnalogCalc7)
{
    if (m_EXAnalogCalc7 == EXAnalogCalc7)
        return;
    m_EXAnalogCalc7 = EXAnalogCalc7;
    emit EXAnalogCalc7Changed(EXAnalogCalc7);
}

void DashBoard::setLambdamultiply(const qreal &Lambdamultiply)
{
    if (m_Lambdamultiply == Lambdamultiply)
        return;
    m_Lambdamultiply = Lambdamultiply;
    lamdamultiplicator = Lambdamultiply;
    emit LambdamultiplyChanged(Lambdamultiply);
}
void DashBoard::setUserchannel1(const qreal &Userchannel1)
{
    if (m_Userchannel1 == Userchannel1)
        return;
    m_Userchannel1 = Userchannel1;
    emit Userchannel1Changed(Userchannel1);
}
void DashBoard::setUserchannel2(const qreal &Userchannel2)
{
    if (m_Userchannel2 == Userchannel2)
        return;
    m_Userchannel2 = Userchannel2;
    emit Userchannel2Changed(Userchannel2);
}
void DashBoard::setUserchannel3(const qreal &Userchannel3)
{
    if (m_Userchannel3 == Userchannel3)
        return;
    m_Userchannel3 = Userchannel3;
    emit Userchannel3Changed(Userchannel3);
}
void DashBoard::setUserchannel4(const qreal &Userchannel4)
{
    if (m_Userchannel4 == Userchannel4)
        return;
    m_Userchannel4 = Userchannel4;
    emit Userchannel4Changed(Userchannel4);
}
void DashBoard::setUserchannel5(const qreal &Userchannel5)
{
    if (m_Userchannel5 == Userchannel5)
        return;
    m_Userchannel5 = Userchannel5;
    emit Userchannel5Changed(Userchannel5);
}
void DashBoard::setUserchannel6(const qreal &Userchannel6)
{
    if (m_Userchannel6 == Userchannel6)
        return;
    m_Userchannel6 = Userchannel6;
    emit Userchannel6Changed(Userchannel6);
}
void DashBoard::setUserchannel7(const qreal &Userchannel7)
{
    if (m_Userchannel7 == Userchannel7)
        return;
    m_Userchannel7 = Userchannel7;
    emit Userchannel7Changed(Userchannel7);
}
void DashBoard::setUserchannel8(const qreal &Userchannel8)
{
    if (m_Userchannel8 == Userchannel8)
        return;
    m_Userchannel8 = Userchannel8;
    emit Userchannel8Changed(Userchannel8);
}
void DashBoard::setUserchannel9(const qreal &Userchannel9)
{
    if (m_Userchannel9 == Userchannel9)
        return;
    m_Userchannel9 = Userchannel9;
    emit Userchannel9Changed(Userchannel9);
}
void DashBoard::setUserchannel10(const qreal &Userchannel10)
{
    if (m_Userchannel10 == Userchannel10)
        return;
    m_Userchannel10 = Userchannel10;
    emit Userchannel10Changed(Userchannel10);
}

void DashBoard::setUserchannel11(const qreal &Userchannel11)
{
    if (m_Userchannel11 == Userchannel11)
        return;
    m_Userchannel11 = Userchannel11;
    emit Userchannel11Changed(Userchannel11);
}
void DashBoard::setUserchannel12(const qreal &Userchannel12)
{
    if (m_Userchannel12 == Userchannel12)
        return;
    m_Userchannel12 = Userchannel12;
    emit Userchannel12Changed(Userchannel12);
}
void DashBoard::setFuelLevel(const qreal &FuelLevel)
{
    if (m_FuelLevel == FuelLevel)
        return;
    m_FuelLevel = FuelLevel;
    emit FuelLevelChanged(FuelLevel);
}
void DashBoard::setSteeringWheelAngle(const qreal &SteeringWheelAngle)
{
    if (m_SteeringWheelAngle == SteeringWheelAngle)
        return;
    m_SteeringWheelAngle = SteeringWheelAngle;
    emit SteeringWheelAngleChanged(SteeringWheelAngle);
}
void DashBoard::setBrightness(const int &Brightness)
{
    if (m_Brightness == Brightness)
        return;
    m_Brightness = Brightness;
    emit BrightnessChanged(Brightness);
}
void DashBoard::setVisibledashes(const int &Visibledashes)
{
    if (m_Visibledashes == Visibledashes)
        return;
    m_Visibledashes = Visibledashes;
    emit VisibledashesChanged(Visibledashes);
}

void DashBoard::setoilpressurelamp(const int &oilpressurelamp)
{
    if (m_oilpressurelamp == oilpressurelamp)
        return;
    m_oilpressurelamp = oilpressurelamp;
    emit oilpressurelampChanged(oilpressurelamp);
}
void DashBoard::setovertempalarm(const int &overtempalarm)
{
    if (m_overtempalarm == overtempalarm)
        return;
    m_overtempalarm = overtempalarm;
    emit overtempalarmChanged(overtempalarm);
}
void DashBoard::setalternatorfail(const int &alternatorfail)
{
    if (m_alternatorfail == alternatorfail)
        return;
    m_alternatorfail = alternatorfail;
    emit alternatorfailChanged(alternatorfail);
}

void DashBoard::setAuxTemp1(const int &AuxTemp1)
{
    if (m_AuxTemp1 == AuxTemp1)
        return;
    m_AuxTemp1 = AuxTemp1;
    emit AuxTemp1Changed(AuxTemp1);
}
void DashBoard::setsixtyfoottime(const qreal &sixtyfoottime)
{
    if (m_sixtyfoottime == sixtyfoottime)
        return;
    m_sixtyfoottime = sixtyfoottime;
    emit sixtyfoottimeChanged(sixtyfoottime);
}
void DashBoard::setsixtyfootspeed(const qreal &sixtyfootspeed)
{
    if (m_sixtyfootspeed == sixtyfootspeed)
        return;
    m_sixtyfootspeed = sixtyfootspeed;
    emit sixtyfootspeedChanged(sixtyfootspeed);
}
void DashBoard::setthreehundredthirtyfoottime(const qreal &threehundredthirtyfoottime)
{
    if (m_threehundredthirtyfoottime == threehundredthirtyfoottime)
        return;
    m_threehundredthirtyfoottime = threehundredthirtyfoottime;
    emit threehundredthirtyfoottimeChanged(threehundredthirtyfoottime);
}
void DashBoard::setthreehundredthirtyfootspeed(const qreal &threehundredthirtyfootspeed)
{
    if (m_threehundredthirtyfootspeed == threehundredthirtyfootspeed)
        return;
    m_threehundredthirtyfootspeed = threehundredthirtyfootspeed;
    emit threehundredthirtyfootspeedChanged(threehundredthirtyfootspeed);
}
void DashBoard::seteightmiletime(const qreal &eightmiletime)
{
    if (m_eightmiletime == eightmiletime)
        return;
    m_eightmiletime = eightmiletime;
    emit eightmiletimeChanged(eightmiletime);
}
void DashBoard::seteightmilespeed(const qreal &eightmilespeed)
{
    if (m_eightmilespeed == eightmilespeed)
        return;
    m_eightmilespeed = eightmilespeed;
    emit eightmilespeedChanged(eightmilespeed);
}
void DashBoard::setquartermiletime(const qreal &quartermiletime)
{
    if (m_quartermiletime == quartermiletime)
        return;
    m_quartermiletime = quartermiletime;
    emit quartermiletimeChanged(quartermiletime);
}
void DashBoard::setquartermilespeed(const qreal &quartermilespeed)
{
    if (m_quartermilespeed == quartermilespeed)
        return;
    m_quartermilespeed = quartermilespeed;
    emit quartermilespeedChanged(quartermilespeed);
}
void DashBoard::setthousandfoottime(const qreal &thousandfoottime)
{
    if (m_thousandfoottime == thousandfoottime)
        return;
    m_thousandfoottime = thousandfoottime;
    emit thousandfoottimeChanged(thousandfoottime);
}
void DashBoard::setthousandfootspeed(const qreal &thousandfootspeed)
{
    if (m_thousandfootspeed == thousandfootspeed)
        return;
    m_thousandfootspeed = thousandfootspeed;
    emit thousandfootspeedChanged(thousandfootspeed);
}
void DashBoard::setzerotohundredt(const qreal &zerotohundredt)
{
    if (m_zerotohundredt == zerotohundredt)
        return;
    m_zerotohundredt = zerotohundredt;
    emit zerotohundredtChanged(zerotohundredt);
}
void DashBoard::sethundredtotwohundredtime(const qreal &hundredtotwohundredtime)
{
    if (m_hundredtotwohundredtime == hundredtotwohundredtime)
        return;
    m_hundredtotwohundredtime = hundredtotwohundredtime;
    emit hundredtotwohundredtimeChanged(hundredtotwohundredtime);
}

void DashBoard::settwohundredtothreehundredtime(const qreal &twohundredtothreehundredtime)
{
    if (m_twohundredtothreehundredtime == twohundredtothreehundredtime)
        return;
    m_twohundredtothreehundredtime = twohundredtothreehundredtime;
    emit twohundredtothreehundredtimeChanged(twohundredtothreehundredtime);
}

void DashBoard::setreactiontime(const qreal &reactiontime)
{
    if (m_reactiontime == reactiontime)
        return;
    m_reactiontime = reactiontime;
    emit reactiontimeChanged(reactiontime);
}



//________________________________________________________
void DashBoard::setIGBTPhaseATemp(const qreal &IGBTPhaseATemp)
{
    if (m_IGBTPhaseATemp == IGBTPhaseATemp)
        return;
    if (m_units == "metric")
    {m_IGBTPhaseATemp = IGBTPhaseATemp;}
    if (m_units == "imperial")
    {m_IGBTPhaseATemp = IGBTPhaseATemp * 1.8 + 32;}
    emit IGBTPhaseATempChanged(IGBTPhaseATemp);
}

void DashBoard::setIGBTPhaseBTemp(const qreal &IGBTPhaseBTemp)
{
    if (m_IGBTPhaseBTemp == IGBTPhaseBTemp)
        return;
    if (m_units == "metric")
    {m_IGBTPhaseBTemp = IGBTPhaseBTemp;}
    if (m_units == "imperial")
    {m_IGBTPhaseBTemp = IGBTPhaseBTemp * 1.8 + 32;}
    emit IGBTPhaseBTempChanged(IGBTPhaseBTemp);
}
void DashBoard::setIGBTPhaseCTemp(const qreal &IGBTPhaseCTemp)
{
    if (m_IGBTPhaseCTemp == IGBTPhaseCTemp)
        return;
    if (m_units == "metric")
    {m_IGBTPhaseCTemp = IGBTPhaseCTemp;}
    if (m_units == "imperial")
    {m_IGBTPhaseCTemp = IGBTPhaseCTemp * 1.8 + 32;}
    emit IGBTPhaseCTempChanged(IGBTPhaseCTemp);
}
void DashBoard::setGateDriverTemp(const qreal &GateDriverTemp)
{
    if (m_GateDriverTemp == GateDriverTemp)
        return;
    if (m_units == "metric")
    {m_GateDriverTemp = GateDriverTemp;}
    if (m_units == "imperial")
    {m_GateDriverTemp = GateDriverTemp * 1.8 + 32;}
    emit GateDriverTempChanged(GateDriverTemp);
}
void DashBoard::setControlBoardTemp(const qreal &ControlBoardTemp)
{
    if (m_ControlBoardTemp== ControlBoardTemp)
        return;
    if (m_units == "metric")
    {m_ControlBoardTemp = ControlBoardTemp;}
    if (m_units == "imperial")
    {m_ControlBoardTemp = ControlBoardTemp * 1.8 + 32;}
    emit ControlBoardTempChanged(ControlBoardTemp);
}
void DashBoard::setRtdTemp1(const qreal &RtdTemp1)
{
    if (m_RtdTemp1 == RtdTemp1)
        return;
    if (m_units == "metric")
    {m_RtdTemp1 = RtdTemp1;}
    if (m_units == "imperial")
    {m_RtdTemp1 = RtdTemp1 * 1.8 + 32;}
    emit RtdTemp1Changed(RtdTemp1);
}
void DashBoard::setRtdTemp2(const qreal &RtdTemp2)
{
    if (m_RtdTemp2 == RtdTemp2)
        return;
    if (m_units == "metric")
    {m_RtdTemp2 = RtdTemp2;}
    if (m_units == "imperial")
    {m_RtdTemp2 = RtdTemp2 * 1.8 + 32;}
    emit RtdTemp2Changed(RtdTemp2);
}
void DashBoard::setRtdTemp3(const qreal &RtdTemp3)
{
    if (m_RtdTemp3 == RtdTemp3)
        return;
    if (m_units == "metric")
    {m_RtdTemp3 = RtdTemp3;}
    if (m_units == "imperial")
    {m_RtdTemp3 = RtdTemp3 * 1.8 + 32;}
    emit RtdTemp3Changed(RtdTemp3);
}
void DashBoard::setRtdTemp4(const qreal &RtdTemp4)
{
    if (m_RtdTemp4 == RtdTemp4)
        return;
    if (m_units == "metric")
    {m_RtdTemp4 = RtdTemp4;}
    if (m_units == "imperial")
    {m_RtdTemp4 = RtdTemp4 * 1.8 + 32;}
    emit RtdTemp4Changed(RtdTemp4);
}
void DashBoard::setRtdTemp5(const qreal &RtdTemp5)
{
    if (m_RtdTemp5 == RtdTemp5)
        return;
    if (m_units == "metric")
    {m_RtdTemp5 = RtdTemp5;}
    if (m_units == "imperial")
    {m_RtdTemp5 = RtdTemp5 * 1.8 + 32;}
    emit RtdTemp5Changed(RtdTemp5);
}
void DashBoard::setEMotorTemperature(const qreal &EMotorTemperature)
{
    if (m_EMotorTemperature == EMotorTemperature)
        return;
    if (m_units == "metric")
    {m_EMotorTemperature = EMotorTemperature;}
    if (m_units == "imperial")
    {m_EMotorTemperature = EMotorTemperature * 1.8 + 32;}
    emit EMotorTemperatureChanged(EMotorTemperature);
}
void DashBoard::setTorqueShudder(const qreal &TorqueShudder)
{
    if (m_TorqueShudder == TorqueShudder)
        return;
    if (m_units == "metric")
    {m_TorqueShudder = TorqueShudder;}
    if (m_units == "imperial")
    {m_TorqueShudder = TorqueShudder * 1.8 + 32;}
    emit TorqueShudderChanged(TorqueShudder);
}
void DashBoard::setDigInput1FowardSw(const qreal &DigInput1FowardSw)
{
    if (m_DigInput1FowardSw == DigInput1FowardSw)
        return;
    m_DigInput1FowardSw = DigInput1FowardSw;
    emit DigInput1FowardSwChanged(DigInput1FowardSw);
}
void DashBoard::setDigInput2ReverseSw(const qreal &DigInput2ReverseSw)
{
    if (m_DigInput2ReverseSw == DigInput2ReverseSw)
        return;
    m_DigInput2ReverseSw = DigInput2ReverseSw;
    emit DigInput2ReverseSwChanged(DigInput2ReverseSw);
}
void DashBoard::setDigInput3BrakeSw(const qreal &DigInput3BrakeSw)
{
    if (m_DigInput3BrakeSw == DigInput3BrakeSw)
        return;
    m_DigInput3BrakeSw = DigInput3BrakeSw;
    emit DigInput3BrakeSwChanged(DigInput3BrakeSw);
}
void DashBoard::setDigInput4RegenDisableSw(const qreal &DigInput4RegenDisableSw)
{
    if (m_DigInput4RegenDisableSw == DigInput4RegenDisableSw)
        return;
    m_DigInput4RegenDisableSw = DigInput4RegenDisableSw;
    emit DigInput4RegenDisableSwChanged(DigInput4RegenDisableSw);
}
void DashBoard::setDigInput5IgnSw(const qreal &DigInput5IgnSw)
{
    if (m_DigInput5IgnSw == DigInput5IgnSw)
        return;
    m_DigInput5IgnSw = DigInput5IgnSw;
    emit DigInput5IgnSwChanged(DigInput5IgnSw);
}
void DashBoard::setDigInput6StartSw(const qreal &DigInput6StartSw)
{
    if (m_DigInput6StartSw == DigInput6StartSw)
        return;
    m_DigInput6StartSw = DigInput6StartSw;
    emit DigInput6StartSwChanged(DigInput6StartSw);
}
void DashBoard::setDigInput7Bool(const qreal &DigInput7Bool)
{
    if (m_DigInput7Bool == DigInput7Bool)
        return;
    m_DigInput7Bool = DigInput7Bool;
    emit DigInput7BoolChanged(DigInput7Bool);
}
void DashBoard::setDigInput8Bool(const qreal &DigInput8Bool)
{
    if (m_DigInput8Bool == DigInput8Bool)
        return;
    m_DigInput8Bool = DigInput8Bool;
    emit DigInput8BoolChanged(DigInput8Bool);
}
void DashBoard::setEMotorAngle(const qreal &EMotorAngle)
{
    if (m_EMotorAngle == EMotorAngle)
        return;
    m_EMotorAngle = EMotorAngle;
    emit EMotorAngleChanged(EMotorAngle);
}
void DashBoard::setEMotorSpeed(const qreal &EMotorSpeed)
{
    if (m_EMotorSpeed == EMotorSpeed)
        return;
    m_EMotorSpeed = EMotorSpeed;
    emit EMotorSpeedChanged(EMotorSpeed);
}
void DashBoard::setElectricalOutFreq(const qreal &ElectricalOutFreq)
{
    if (m_ElectricalOutFreq == ElectricalOutFreq)
        return;
    m_ElectricalOutFreq= ElectricalOutFreq;
    emit ElectricalOutFreqChanged(ElectricalOutFreq);
}
void DashBoard::setDeltaResolverFiltered(const qreal &DeltaResolverFiltered)
{
    if (m_DeltaResolverFiltered == DeltaResolverFiltered)
        return;
    m_DeltaResolverFiltered = DeltaResolverFiltered;
    emit DeltaResolverFilteredChanged(DeltaResolverFiltered);
}
void DashBoard::setPhaseACurrent(const qreal &PhaseACurrent)
{
    if (m_PhaseACurrent == PhaseACurrent)
        return;
    m_PhaseACurrent = PhaseACurrent;
    emit PhaseACurrentChanged(PhaseACurrent);
}
void DashBoard::setPhaseBCurrent(const qreal &PhaseBCurrent)
{
    if (m_PhaseBCurrent == PhaseBCurrent)
        return;
    m_PhaseBCurrent = PhaseBCurrent;
    emit PhaseBCurrentChanged(PhaseBCurrent);
}
void DashBoard::setPhaseCCurrent(const qreal &PhaseCCurrent)
{
    if (m_PhaseCCurrent == PhaseCCurrent)
        return;
    m_PhaseCCurrent = PhaseCCurrent;
    emit PhaseCCurrentChanged(PhaseCCurrent);
}
void DashBoard::setDCBusCurrent(const qreal &DCBusCurrent)
{
    if (m_DCBusCurrent == DCBusCurrent)
        return;
    m_DCBusCurrent = DCBusCurrent;
    emit DCBusCurrentChanged(DCBusCurrent);
}
void DashBoard::setDCBusVoltage(const qreal &DCBusVoltage)
{
    if (m_DCBusVoltage == DCBusVoltage)
        return;
    m_DCBusVoltage = DCBusVoltage;
    emit DCBusVoltageChanged(DCBusVoltage);
}
void DashBoard::setOutputVoltage(const qreal &OutputVoltage)
{
    if (m_OutputVoltage == OutputVoltage)
        return;
    m_OutputVoltage = OutputVoltage;
    emit OutputVoltageChanged(OutputVoltage);
}
void DashBoard::setVABvdVoltage(const qreal &VABvdVoltage)
{
    if (m_VABvdVoltage == VABvdVoltage)
        return;
    m_VABvdVoltage = VABvdVoltage;
    emit VABvdVoltageChanged(VABvdVoltage);
}
void DashBoard::setVBCvqVoltage(const qreal &VBCvqVoltage)
{
    if (m_VBCvqVoltage == VBCvqVoltage)
        return;
    m_VBCvqVoltage = VBCvqVoltage;
    emit VBCvqVoltageChanged(VBCvqVoltage);
}


void DashBoard::setTiretempLF(const qreal &TiretempLF)
{
if (m_TiretempLF == TiretempLF)
    return;
if (m_units == "metric")
{m_TiretempLF = TiretempLF;}
if (m_units == "imperial")
{m_TiretempLF = qRound(TiretempLF * 1.8 + 32);}
emit TiretempLFChanged(TiretempLF);
}
void DashBoard::setTiretempRF(const qreal &TiretempRF)
{
if (m_TiretempRF == TiretempRF)
    return;
if (m_units == "metric")
{m_TiretempRF = TiretempRF;}
if (m_units == "imperial")
{m_TiretempRF = qRound(TiretempRF * 1.8 + 32);}
emit TiretempRFChanged(TiretempRF);
}
void DashBoard::setTiretempRR(const qreal &TiretempRR)
{
if (m_TiretempRR == TiretempRR)
    return;
if (m_units == "metric")
{m_TiretempRR = TiretempRR;}
if (m_units == "imperial")
{m_TiretempRR = qRound(TiretempRR * 1.8 + 32);}
emit TiretempRRChanged(TiretempRR);
}
void DashBoard::setTiretempLR(const qreal &TiretempLR)
{
if (m_TiretempLR == TiretempLR)
    return;
if (m_units == "metric")
{m_TiretempLR = TiretempLR;}
if (m_units == "imperial")
{m_TiretempLR = qRound(TiretempLR * 1.8 + 32);}
emit TiretempLRChanged(TiretempLR);
}

void DashBoard::setTirepresLF(const qreal &TirepresLF)
{
    if(m_TirepresLF == TirepresLF)
        return;
    if (m_pressureunits == "metric")
    { m_TirepresLF = TirepresLF;}
    if (m_pressureunits == "imperial")
    {m_TirepresLF = TirepresLF * 0.145038;}
    emit TirepresLFChanged(TirepresLF);
}
void DashBoard::setTirepresRF(const qreal &TirepresRF)
{
    if(m_TirepresRF == TirepresRF)
        return;
    if (m_pressureunits == "metric")
    { m_TirepresRF = TirepresRF;}
    if (m_pressureunits == "imperial")
    {m_TirepresRF = TirepresRF * 0.145038;}
    emit TirepresRFChanged(TirepresRF);
}
void DashBoard::setTirepresRR(const qreal &TirepresRR)
{
    if(m_TirepresRR == TirepresRR)
        return;
    if (m_pressureunits == "metric")
    { m_TirepresRR = TirepresRR;}
    if (m_pressureunits == "imperial")
    {m_TirepresRR = TirepresRR * 0.145038;}
    emit TirepresRRChanged(TirepresRR);
}
void DashBoard::setTirepresLR(const qreal &TirepresLR)
{
    if(m_TirepresLR == TirepresLR)
        return;
    if (m_pressureunits == "metric")
    { m_TirepresLR = TirepresLR;}
    if (m_pressureunits == "imperial")
    {m_TirepresLR = TirepresLR * 0.145038;}
    emit TirepresLRChanged(TirepresLR);
}

void DashBoard::setDigitalInput1(const qreal &DigitalInput1)
{
    if(m_DigitalInput1 == DigitalInput1)
        return;
    m_DigitalInput1 = DigitalInput1;
    emit DigitalInput1Changed(DigitalInput1);
}
void DashBoard::setDigitalInput2(const qreal &DigitalInput2)
{
    if(m_DigitalInput2 == DigitalInput2)
        return;
    m_DigitalInput2 = DigitalInput2;
    emit DigitalInput2Changed(DigitalInput2);
}
void DashBoard::setDigitalInput3(const qreal &DigitalInput3)
{
    if(m_DigitalInput3 == DigitalInput3)
        return;
    m_DigitalInput3 = DigitalInput3;
    emit DigitalInput3Changed(DigitalInput3);
}
void DashBoard::setDigitalInput4(const qreal &DigitalInput4)
{
    if(m_DigitalInput4 == DigitalInput4)
        return;
    m_DigitalInput4 = DigitalInput4;
    emit DigitalInput4Changed(DigitalInput4);
}
void DashBoard::setDigitalInput5(const qreal &DigitalInput5)
{
    if(m_DigitalInput5 == DigitalInput5)
        return;
    m_DigitalInput5 = DigitalInput5;
    emit DigitalInput5Changed(DigitalInput5);
}
void DashBoard::setDigitalInput6(const qreal &DigitalInput6)
{
    if(m_DigitalInput6 == DigitalInput6)
        return;
    m_DigitalInput6 = DigitalInput6;
    emit DigitalInput6Changed(DigitalInput6);
}
void DashBoard::setDigitalInput7(const qreal &DigitalInput7)
{
    if(m_DigitalInput7 == DigitalInput7)
        return;
    m_DigitalInput7 = DigitalInput7;
    emit DigitalInput7Changed(DigitalInput7);
}

//EX Board

void DashBoard::setEXDigitalInput1(const qreal &EXDigitalInput1)
{
    if(m_EXDigitalInput1 == EXDigitalInput1)
        return;
    m_EXDigitalInput1 = EXDigitalInput1;
    emit EXDigitalInput1Changed(EXDigitalInput1);
}
void DashBoard::setEXDigitalInput2(const qreal &EXDigitalInput2)
{
    if(m_EXDigitalInput2 == EXDigitalInput2)
        return;
    m_EXDigitalInput2 = EXDigitalInput2;
    emit EXDigitalInput2Changed(EXDigitalInput2);
}
void DashBoard::setEXDigitalInput3(const qreal &EXDigitalInput3)
{
    if(m_EXDigitalInput3 == EXDigitalInput3)
        return;
    m_EXDigitalInput3 = EXDigitalInput3;
    emit EXDigitalInput3Changed(EXDigitalInput3);
}
void DashBoard::setEXDigitalInput4(const qreal &EXDigitalInput4)
{
    if(m_EXDigitalInput4 == EXDigitalInput4)
        return;
    m_EXDigitalInput4 = EXDigitalInput4;
    emit EXDigitalInput4Changed(EXDigitalInput4);
}
void DashBoard::setEXDigitalInput5(const qreal &EXDigitalInput5)
{
    if(m_EXDigitalInput5 == EXDigitalInput5)
        return;
    m_EXDigitalInput5 = EXDigitalInput5;
    emit EXDigitalInput5Changed(EXDigitalInput5);
}
void DashBoard::setEXDigitalInput6(const qreal &EXDigitalInput6)
{
    if(m_EXDigitalInput6 == EXDigitalInput6)
        return;
    m_EXDigitalInput6 = EXDigitalInput6;
    emit EXDigitalInput6Changed(EXDigitalInput6);
}
void DashBoard::setEXDigitalInput7(const qreal &EXDigitalInput7)
{
    if(m_EXDigitalInput7 == EXDigitalInput7)
        return;
    m_EXDigitalInput7 = EXDigitalInput7;
    emit EXDigitalInput7Changed(EXDigitalInput7);
}
void DashBoard::setEXDigitalInput8(const qreal &EXDigitalInput8)
{
    if(m_EXDigitalInput8 == EXDigitalInput8)
        return;
    m_EXDigitalInput8 = EXDigitalInput8;
    emit EXDigitalInput8Changed(EXDigitalInput8);
}

void DashBoard::setigncut(const qreal &igncut)
{
    if(m_igncut == igncut)
        return;
    m_igncut = igncut;
    emit igncutChanged(igncut);
}
void DashBoard::setundrivenavgspeed(const qreal &undrivenavgspeed)
{
    if(m_undrivenavgspeed == undrivenavgspeed)
        return;
    m_undrivenavgspeed = undrivenavgspeed;
    emit undrivenavgspeedChanged(undrivenavgspeed);
}
void DashBoard::setdrivenavgspeed(const qreal &drivenavgspeed)
{
    if(m_drivenavgspeed == drivenavgspeed)
        return;
    m_drivenavgspeed = drivenavgspeed;
    emit drivenavgspeedChanged(drivenavgspeed);
}
void DashBoard::setdsettargetslip(const qreal &dsettargetslip)
{
    if(m_dsettargetslip == dsettargetslip)
        return;
    m_dsettargetslip = dsettargetslip;
    emit dsettargetslipChanged(dsettargetslip);
}
void DashBoard::settractionctlpowerlimit(const qreal &tractionctlpowerlimit)
{
    if(m_tractionctlpowerlimit == tractionctlpowerlimit)
        return;
    m_tractionctlpowerlimit = tractionctlpowerlimit;
    emit tractionctlpowerlimitChanged(tractionctlpowerlimit);
}
void DashBoard::setknockallpeak(const qreal &knockallpeak)
{
    if(m_knockallpeak == knockallpeak)
        return;
    m_knockallpeak = knockallpeak;
    emit knockallpeakChanged(knockallpeak);
}
void DashBoard::setknockcorr(const qreal &knockcorr)
{
    if(m_knockcorr == knockcorr)
        return;
    m_knockcorr = knockcorr;
    emit knockcorrChanged(knockcorr);
}
void DashBoard::setknocklastcyl(const qreal &knocklastcyl)
{
    if(m_knocklastcyl == knocklastcyl)
        return;
    m_knocklastcyl = knocklastcyl;
    emit knocklastcylChanged(knocklastcyl);
}
void DashBoard::settotalfueltrim(const qreal &totalfueltrim)
{
    if(m_totalfueltrim == totalfueltrim)
        return;
    m_totalfueltrim = totalfueltrim;
    emit totalfueltrimChanged(totalfueltrim);
}
void DashBoard::settotaligncomp(const qreal &totaligncomp)
{
    if(m_totaligncomp == totaligncomp)
        return;
    m_totaligncomp = totaligncomp;
    emit totaligncompChanged(totaligncomp);
}
void DashBoard::setegthighest(const qreal &egthighest)
{
    if(m_egthighest == egthighest)
        return;
    m_egthighest = egthighest;
    emit egthighestChanged(egthighest);
}
void DashBoard::setcputempecu(const qreal &cputempecu)
{
    if(m_cputempecu == cputempecu)
        return;
    m_cputempecu = cputempecu;
    emit cputempecuChanged(cputempecu);
}
void DashBoard::seterrorcodecount(const qreal &errorcodecount)
{
    if(m_errorcodecount == errorcodecount)
        return;
    m_errorcodecount = errorcodecount;
    emit errorcodecountChanged(errorcodecount);
}
void DashBoard::setlostsynccount(const qreal &lostsynccount)
{
    if(m_lostsynccount == lostsynccount)
        return;
    m_lostsynccount = lostsynccount;
    emit lostsynccountChanged(lostsynccount);
}
    void DashBoard::setegtdiff(const qreal &egtdiff)
    {
        if(m_egtdiff == egtdiff)
            return;
        m_egtdiff = egtdiff;
        emit egtdiffChanged(egtdiff);
    }
    void DashBoard::setactiveboosttable(const qreal &activeboosttable)
    {
        if(m_activeboosttable == activeboosttable)
            return;
        m_activeboosttable = activeboosttable;
        emit activeboosttableChanged(activeboosttable);
    }
    void DashBoard::setactivetunetable(const qreal &activetunetable)
    {
        if(m_activetunetable == activetunetable)
            return;
        m_activetunetable = activetunetable;
        emit activetunetableChanged(activetunetable);
    }
    void DashBoard::setgenericoutput1(const qreal &genericoutput1)
    {
        if(m_genericoutput1 == genericoutput1)
            return;
        m_genericoutput1 = genericoutput1;
        emit genericoutput1Changed(genericoutput1);
    }


// Odometer
qreal DashBoard::Odo() const { return m_Odo; }

// Tripmeter
qreal DashBoard::Trip() const { return m_Trip; }

// Advanced Info
qreal DashBoard::rpm() const { return m_rpm; }
qreal DashBoard::Intakepress() const { return m_Intakepress; }
qreal DashBoard::PressureV() const { return m_PressureV; }
qreal DashBoard::ThrottleV() const { return m_ThrottleV; }
qreal DashBoard::Primaryinp() const { return m_Primaryinp; }
qreal DashBoard::Fuelc() const { return m_Fuelc; }
qreal DashBoard::Leadingign() const { return m_Leadingign; }
qreal DashBoard::Trailingign() const { return m_Trailingign; }
qreal DashBoard::Fueltemp() const { return m_Fueltemp; }
qreal DashBoard::Moilp() const { return m_Moilp; }
qreal DashBoard::Boosttp() const { return m_Boosttp; }
qreal DashBoard::Boostwg() const { return m_Boostwg; }
qreal DashBoard::Watertemp() const { return m_Watertemp; }
qreal DashBoard::Intaketemp() const { return m_Intaketemp; }
qreal DashBoard::Knock() const { return m_Knock; }
qreal DashBoard::BatteryV() const { return m_BatteryV; }
qreal DashBoard::speed() const { return m_speed; }
qreal DashBoard::Iscvduty() const { return m_Iscvduty; }
qreal DashBoard::O2volt() const { return m_O2volt; }
qreal DashBoard::Cyl1_O2_Corr() const { return m_Cyl1_O2_Corr; }
qreal DashBoard::Cyl2_O2_Corr() const { return m_Cyl2_O2_Corr; }
qreal DashBoard::Cyl3_O2_Corr() const { return m_Cyl3_O2_Corr; }
qreal DashBoard::Cyl4_O2_Corr() const { return m_Cyl4_O2_Corr; }
qreal DashBoard::Cyl5_O2_Corr() const { return m_Cyl5_O2_Corr; }
qreal DashBoard::Cyl6_O2_Corr() const { return m_Cyl6_O2_Corr; }
qreal DashBoard::Cyl7_O2_Corr() const { return m_Cyl7_O2_Corr; }
qreal DashBoard::Cyl8_O2_Corr() const { return m_Cyl8_O2_Corr; }
qreal DashBoard::na1() const { return m_na1; }
qreal DashBoard::Secinjpulse() const { return m_Secinjpulse; }
qreal DashBoard::na2() const { return m_na2; }
qreal DashBoard::InjDuty() const { return m_InjDuty; }
qreal DashBoard::InjDuty2() const { return m_InjDuty2; }
qreal DashBoard::InjAngle() const { return m_InjAngle; }
qreal DashBoard::EngLoad() const { return m_EngLoad; }
qreal DashBoard::MAF1V() const { return m_MAF1V; }
qreal DashBoard::MAF2V() const { return m_MAF2V; }
qreal DashBoard::injms() const { return m_injms; }
qreal DashBoard::Inj() const { return m_Inj; }
qreal DashBoard::Ign() const { return m_Ign; }
qreal DashBoard::Dwell() const { return m_Dwell; }
qreal DashBoard::BoostPres() const { return m_BoostPres; }
qreal DashBoard::BoostPreskpa() const { return m_BoostPreskpa; }
qreal DashBoard::BoostDuty() const { return m_BoostDuty; }
qreal DashBoard::MAFactivity() const { return m_MAFactivity; }
qreal DashBoard::O2volt_2() const { return m_O2volt_2; }


//Boost

qreal DashBoard::pim() const { return m_pim; }

//Aux Inputs
qreal DashBoard::auxcalc1() const { return m_auxcalc1; }
qreal DashBoard::auxcalc2() const { return m_auxcalc2; }
qreal DashBoard::auxcalc3() const { return m_auxcalc3; }
qreal DashBoard::auxcalc4() const { return m_auxcalc4; }

//Sensor info
qreal DashBoard::sens1() const { return m_sens1; }
qreal DashBoard::sens2() const { return m_sens2; }
qreal DashBoard::sens3() const { return m_sens3; }
qreal DashBoard::sens4() const { return m_sens4; }
qreal DashBoard::sens5() const { return m_sens5; }
qreal DashBoard::sens6() const { return m_sens6; }
qreal DashBoard::sens7() const { return m_sens7; }
qreal DashBoard::sens8() const { return m_sens8; }

//Flags

qreal DashBoard::Flag1() const { return m_Flag1; }
qreal DashBoard::Flag2() const { return m_Flag2; }
qreal DashBoard::Flag3() const { return m_Flag3; }
qreal DashBoard::Flag4() const { return m_Flag4; }
qreal DashBoard::Flag5() const { return m_Flag5; }
qreal DashBoard::Flag6() const { return m_Flag6; }
qreal DashBoard::Flag7() const { return m_Flag7; }
qreal DashBoard::Flag8() const { return m_Flag8; }
qreal DashBoard::Flag9() const { return m_Flag9; }
qreal DashBoard::Flag10() const { return m_Flag10; }
qreal DashBoard::Flag11() const { return m_Flag11; }
qreal DashBoard::Flag12() const { return m_Flag12; }
qreal DashBoard::Flag13() const { return m_Flag13; }
qreal DashBoard::Flag14() const { return m_Flag14; }
qreal DashBoard::Flag15() const { return m_Flag15; }
qreal DashBoard::Flag16() const { return m_Flag16; }
qreal DashBoard::Flag17() const { return m_Flag17; }
qreal DashBoard::Flag18() const { return m_Flag18; }
qreal DashBoard::Flag19() const { return m_Flag19; }
qreal DashBoard::Flag20() const { return m_Flag20; }
qreal DashBoard::Flag21() const { return m_Flag21; }
qreal DashBoard::Flag22() const { return m_Flag22; }
qreal DashBoard::Flag23() const { return m_Flag23; }
qreal DashBoard::Flag24() const { return m_Flag24; }
qreal DashBoard::Flag25() const { return m_Flag25; }
//Flag Strings

QString DashBoard::FlagString1() const { return m_FlagString1; }
QString DashBoard::FlagString2() const { return m_FlagString2; }
QString DashBoard::FlagString3() const { return m_FlagString3; }
QString DashBoard::FlagString4() const { return m_FlagString4; }
QString DashBoard::FlagString5() const { return m_FlagString5; }
QString DashBoard::FlagString6() const { return m_FlagString6; }
QString DashBoard::FlagString7() const { return m_FlagString7; }
QString DashBoard::FlagString8() const { return m_FlagString8; }
QString DashBoard::FlagString9() const { return m_FlagString9; }
QString DashBoard::FlagString10() const { return m_FlagString10; }
QString DashBoard::FlagString11() const { return m_FlagString11; }
QString DashBoard::FlagString12() const { return m_FlagString12; }
QString DashBoard::FlagString13() const { return m_FlagString13; }
QString DashBoard::FlagString14() const { return m_FlagString14; }
QString DashBoard::FlagString15() const { return m_FlagString15; }
QString DashBoard::FlagString16() const { return m_FlagString16; }
// Sensor Strings

QString DashBoard::SensorString1() const { return m_SensorString1; }
QString DashBoard::SensorString2() const { return m_SensorString2; }
QString DashBoard::SensorString3() const { return m_SensorString3; }
QString DashBoard::SensorString4() const { return m_SensorString4; }
QString DashBoard::SensorString5() const { return m_SensorString5; }
QString DashBoard::SensorString6() const { return m_SensorString6; }
QString DashBoard::SensorString7() const { return m_SensorString7; }
QString DashBoard::SensorString8() const { return m_SensorString8; }
//Platfrom String
QString DashBoard::Platform() const { return m_Platform; }

QString DashBoard::SerialStat() const { return m_SerialStat; }
QString DashBoard::RecvData() const { return m_RecvData; }
QString DashBoard::TimeoutStat() const { return m_TimeoutStat; }
QString DashBoard::RunStat() const { return m_RunStat; }
QString DashBoard::WifiStat() const { return m_WifiStat; }
QString DashBoard::EthernetStat() const { return m_EthernetStat; }




//GPS

QString DashBoard::gpsTime() const { return m_gpsTime; }
qreal DashBoard::gpsAltitude() const { return m_gpsAltitude; }
qreal DashBoard::gpsLatitude() const { return m_gpsLatitude; }
qreal DashBoard::gpsLongitude () const { return m_gpsLongitude; }
double DashBoard::gpsSpeed() const { return m_gpsSpeed; }
int DashBoard::gpsVisibleSatelites () const { return m_gpsVisibleSatelites; }
QString DashBoard::gpsFIXtype () const { return m_gpsFIXtype; }
qreal DashBoard::gpsbaering() const { return m_gpsbaering; }



//units
QString DashBoard::units() const { return m_units; }
QString DashBoard::speedunits() const { return m_speedunits; }
QString DashBoard::pressureunits() const { return m_pressureunits; }



//Adaptronic extra


qreal DashBoard::MAP() const { return m_MAP; }
qreal DashBoard::PANVAC() const { return m_PANVAC; }
qreal DashBoard::MAP2() const { return m_MAP2; }
qreal DashBoard::AUXT() const { return m_AUXT; }
qreal DashBoard::AFR() const { return m_AFR; }
qreal DashBoard::AFRLEFTBANKTARGET() const { return m_AFRLEFTBANKTARGET; }
qreal DashBoard::AFRRIGHTBANKTARGET() const { return m_AFRRIGHTBANKTARGET; }
qreal DashBoard::AFRLEFTBANKACTUAL() const { return m_AFRLEFTBANKACTUAL; }
qreal DashBoard::AFRRIGHTBANKACTUAL() const { return m_AFRRIGHTBANKACTUAL; }
qreal DashBoard::BOOSTOFFSET() const { return m_BOOSTOFFSET; }
qreal DashBoard::REVLIM3STEP() const { return m_REVLIM3STEP; }
qreal DashBoard::REVLIM2STEP() const { return m_REVLIM2STEP; }
qreal DashBoard::REVLIMGIGHSIDE() const { return m_REVLIMGIGHSIDE; }
qreal DashBoard::REVLIMBOURNOUT() const { return m_REVLIMBOURNOUT; }
qreal DashBoard::LEFTBANKO2CORR() const { return m_LEFTBANKO2CORR; }
qreal DashBoard::RIGHTBANKO2CORR() const { return m_RIGHTBANKO2CORR; }
qreal DashBoard::TRACTIONCTRLOFFSET() const { return m_TRACTIONCTRLOFFSET; }
qreal DashBoard::DRIVESHAFTOFFSET() const { return m_DRIVESHAFTOFFSET; }
qreal DashBoard::TCCOMMAND() const { return m_TCCOMMAND; }
qreal DashBoard::FSLCOMMAND() const { return m_FSLCOMMAND; }
qreal DashBoard::FSLINDEX() const { return m_FSLINDEX; }

qreal DashBoard::AFRcyl1() const { return m_AFRcyl1; }
qreal DashBoard::AFRcyl2() const { return m_AFRcyl2; }
qreal DashBoard::AFRcyl3() const { return m_AFRcyl3; }
qreal DashBoard::AFRcyl4() const { return m_AFRcyl4; }
qreal DashBoard::AFRcyl5() const { return m_AFRcyl5; }
qreal DashBoard::AFRcyl6() const { return m_AFRcyl6; }
qreal DashBoard::AFRcyl7() const { return m_AFRcyl7; }
qreal DashBoard::AFRcyl8() const { return m_AFRcyl8; }
qreal DashBoard::TPS() const { return m_TPS; }
qreal DashBoard::IdleValue() const { return m_IdleValue; }
qreal DashBoard::MVSS() const { return m_MVSS; }
qreal DashBoard::SVSS() const { return m_SVSS; }
qreal DashBoard::Inj1() const { return m_Inj1; }
qreal DashBoard::Inj2() const { return m_Inj2; }
qreal DashBoard::Inj3() const { return m_Inj3; }
qreal DashBoard::Inj4() const { return m_Inj4; }
qreal DashBoard::Ign1() const { return m_Ign1; }
qreal DashBoard::Ign2() const { return m_Ign2; }
qreal DashBoard::Ign3() const { return m_Ign3; }
qreal DashBoard::Ign4() const { return m_Ign4; }
qreal DashBoard::TRIM() const { return m_TRIM; }
qreal DashBoard::LAMBDA() const { return m_LAMBDA; }
qreal DashBoard::LAMBDATarget() const { return m_LAMBDATarget; }
qreal DashBoard::FuelPress() const { return m_FuelPress; }
qreal DashBoard::GearOilPress() const { return m_GearOilPress; }

// Qsensors
qreal DashBoard::accelx() const { return m_accelx; }
qreal DashBoard::accely() const { return m_accely; }
qreal DashBoard::accelz() const { return m_accelz; }
qreal DashBoard::gyrox() const { return m_gyrox; }
qreal DashBoard::gyroy() const { return m_gyroy; }
qreal DashBoard::gyroz() const { return m_gyroz; }
qreal DashBoard::compass() const { return m_compass; }
qreal DashBoard::ambitemp() const { return m_ambitemp; }
qreal DashBoard::ambipress() const { return m_ambipress; }

//calculations
qreal DashBoard::Gear() const { return m_Gear; }
qreal DashBoard::Gearoffset() const { return m_Gearoffset; }

qreal DashBoard::GearCalculation() const { return m_GearCalculation; }
qreal DashBoard::Power() const { return m_Power; }
qreal DashBoard::Torque() const { return m_Torque; }
qreal DashBoard::AccelTimer() const { return m_AccelTimer; }
qreal DashBoard::Weight() const { return m_Weight; }

//Official Pi screen present screen
bool DashBoard::screen() const { return m_screen; }

//User Dashboard Stringlist
QStringList DashBoard::maindashsetup() const { return m_maindashsetup; }
QStringList DashBoard::dashsetup3() const { return m_dashsetup3; }
QStringList DashBoard::dashsetup2() const { return m_dashsetup2; }
QStringList DashBoard::dashsetup1() const { return m_dashsetup1; }

QStringList DashBoard::dashfiles() const { return m_dashfiles; }
QStringList DashBoard::backroundpictures() const { return m_backroundpictures; }

qreal DashBoard::accelpedpos() const { return m_accelpedpos; }
qreal DashBoard::airtempensor2() const { return m_airtempensor2; }
qreal DashBoard::antilaglauchswitch() const { return m_antilaglauchswitch; }
qreal DashBoard::antilaglaunchon() const { return m_antilaglaunchon; }
qreal DashBoard::auxrevlimitswitch() const { return m_auxrevlimitswitch; }
qreal DashBoard::avfueleconomy() const { return m_avfueleconomy; }
qreal DashBoard::battlight() const { return m_battlight; }
qreal DashBoard::boostcontrol() const { return m_boostcontrol; }
qreal DashBoard::brakepress() const { return m_brakepress; }
qreal DashBoard::clutchswitchstate() const { return m_clutchswitchstate; }
qreal DashBoard::coolantpress() const { return m_coolantpress; }
qreal DashBoard::decelcut() const { return m_decelcut; }
qreal DashBoard::diffoiltemp() const { return m_diffoiltemp; }
qreal DashBoard::distancetoempty() const { return m_distancetoempty; }
qreal DashBoard::egt1() const { return m_egt1; }
qreal DashBoard::egt2() const { return m_egt2; }
qreal DashBoard::egt3() const { return m_egt3; }
qreal DashBoard::egt4() const { return m_egt4; }
qreal DashBoard::egt5() const { return m_egt5; }
qreal DashBoard::egt6() const { return m_egt6; }
qreal DashBoard::egt7() const { return m_egt7; }
qreal DashBoard::egt8() const { return m_egt8; }
qreal DashBoard::egt9() const { return m_egt9; }
qreal DashBoard::egt10() const { return m_egt10; }
qreal DashBoard::egt11() const { return m_egt11; }
qreal DashBoard::egt12() const { return m_egt12; }
qreal DashBoard::excamangle1() const { return m_excamangle1; }
qreal DashBoard::excamangle2() const { return m_excamangle2; }
qreal DashBoard::flatshiftstate() const { return m_flatshiftstate; }
qreal DashBoard::fuelclevel() const { return m_fuelclevel; }
qreal DashBoard::fuelcomposition() const { return m_fuelcomposition; }
qreal DashBoard::fuelconsrate() const { return m_fuelconsrate; }
qreal DashBoard::fuelcutperc() const { return m_fuelcutperc; }
qreal DashBoard::fuelflowdiff() const { return m_fuelflowdiff; }
qreal DashBoard::fuelflowret() const { return m_fuelflowret; }
qreal DashBoard::fueltrimlongtbank1() const { return m_fueltrimlongtbank1; }
qreal DashBoard::fuelflow() const { return m_fuelflow; }
qreal DashBoard::fueltrimlongtbank2() const { return m_fueltrimlongtbank2; }
qreal DashBoard::fueltrimshorttbank1() const { return m_fueltrimshorttbank1; }
qreal DashBoard::fueltrimshorttbank2() const { return m_fueltrimshorttbank2; }
qreal DashBoard::gearswitch() const { return m_gearswitch; }
qreal DashBoard::handbrake() const { return m_handbrake; }
qreal DashBoard::highbeam() const { return m_highbeam; }
qreal DashBoard::lowBeam() const { return m_lowBeam; }
qreal DashBoard::tractionControl() const { return m_tractionControl; }
qreal DashBoard::homeccounter() const { return m_homeccounter; }
qreal DashBoard::incamangle1() const { return m_incamangle1; }
qreal DashBoard::incamangle2() const { return m_incamangle2; }
qreal DashBoard::knocklevlogged1() const { return m_knocklevlogged1; }
qreal DashBoard::knocklevlogged2() const { return m_knocklevlogged2; }
qreal DashBoard::knockretardbank1() const { return m_knockretardbank1; }
qreal DashBoard::knockretardbank2() const { return m_knockretardbank2; }
qreal DashBoard::lambda2() const { return m_lambda2; }
qreal DashBoard::lambda3() const { return m_lambda3; }
qreal DashBoard::lambda4() const { return m_lambda4; }
qreal DashBoard::launchcontolfuelenrich() const { return m_launchcontolfuelenrich; }
qreal DashBoard::launchctrolignretard() const { return m_launchctrolignretard; }
qreal DashBoard::leftindicator() const { return m_leftindicator; }
qreal DashBoard::limpmode() const { return m_limpmode; }
qreal DashBoard::mil() const { return m_mil; }
qreal DashBoard::missccount() const { return m_missccount; }
qreal DashBoard::nosactive() const { return m_nosactive; }
qreal DashBoard::nospress() const { return m_nospress; }
qreal DashBoard::nosswitch() const { return m_nosswitch; }
qreal DashBoard::oilpres() const { return m_oilpres; }
qreal DashBoard::oiltemp() const { return m_oiltemp; }
qreal DashBoard::rallyantilagswitch() const { return m_rallyantilagswitch; }
qreal DashBoard::rightindicator() const { return m_rightindicator; }
qreal DashBoard::targetbstlelkpa() const { return m_targetbstlelkpa; }
qreal DashBoard::timeddutyout1() const { return m_timeddutyout1; }
qreal DashBoard::timeddutyout2() const { return m_timeddutyout2; }
qreal DashBoard::timeddutyoutputactive() const { return m_timeddutyoutputactive; }
qreal DashBoard::torqueredcutactive() const { return m_torqueredcutactive; }
qreal DashBoard::torqueredlevelactive() const { return m_torqueredlevelactive; }
qreal DashBoard::transientthroactive() const { return m_transientthroactive; }
qreal DashBoard::transoiltemp() const { return m_transoiltemp; }
qreal DashBoard::triggerccounter() const { return m_triggerccounter; }
qreal DashBoard::triggersrsinceasthome() const { return m_triggersrsinceasthome; }
qreal DashBoard::turborpm() const { return m_turborpm; }
qreal DashBoard::turborpm2() const { return m_turborpm2; }
qreal DashBoard::wastegatepress() const { return m_wastegatepress; }
qreal DashBoard::wheeldiff() const { return m_wheeldiff; }
qreal DashBoard::wheelslip() const { return m_wheelslip; }
qreal DashBoard::wheelspdftleft() const { return m_wheelspdftleft; }
qreal DashBoard::wheelspdftright() const { return m_wheelspdftright; }
qreal DashBoard::wheelspdrearleft() const { return m_wheelspdrearleft; }
qreal DashBoard::wheelspdrearright() const { return m_wheelspdrearright; }
QString DashBoard::musicpath() const {return m_musicpath; }
int DashBoard::supportedReg() const {return m_supportedReg; }
qreal DashBoard::speedpercent() const {return m_speedpercent; }

int DashBoard::maxRPM() const {return m_maxRPM; }
int DashBoard::rpmStage1() const {return m_rpmStage1; }
int DashBoard::rpmStage2() const {return m_rpmStage2; }
int DashBoard::rpmStage3() const {return m_rpmStage3; }
int DashBoard::rpmStage4() const {return m_rpmStage4; }
int DashBoard::waterwarn() const {return m_waterwarn; }
int DashBoard::rpmwarn() const {return m_rpmwarn; }
int DashBoard::knockwarn() const {return m_knockwarn; }
qreal DashBoard::boostwarn() const {return m_boostwarn; }
int DashBoard::smoothrpm() const {return m_smoothrpm; }
int DashBoard::smoothspeed() const {return m_smoothspeed; }
int DashBoard::smootexAnalogInput7() const {return m_smoothexAnalogInput7; }
int DashBoard::gearcalc1() const {return m_gearcalc1; }
int DashBoard::gearcalc2() const {return m_gearcalc2; }
int DashBoard::gearcalc3() const {return m_gearcalc3; }
int DashBoard::gearcalc4() const {return m_gearcalc4; }
int DashBoard::gearcalc5() const {return m_gearcalc5; }
int DashBoard::gearcalc6() const {return m_gearcalc6; }
int DashBoard::gearcalcactivation() const {return m_gearcalcactivation; }
int DashBoard::ecu() const { return m_ecu; }
int DashBoard::rpmstyle1() const { return m_rpmstyle1; }
int DashBoard::rpmstyle2() const { return m_rpmstyle2; }
int DashBoard::rpmstyle3() const { return m_rpmstyle3; }
int DashBoard::RotaryTrimpot1() const { return m_RotaryTrimpot1; }
int DashBoard::RotaryTrimpot2() const { return m_RotaryTrimpot2; }
int DashBoard::RotaryTrimpot3() const { return m_RotaryTrimpot3; }
int DashBoard::CalibrationSelect() const { return m_CalibrationSelect; }

QString DashBoard::Error() const { return m_Error; }
QString DashBoard::autogear() const { return m_autogear; }

int DashBoard::ExternalSpeed() const {return m_ExternalSpeed; }

//laptimer

int DashBoard::currentLap() const {return m_currentLap; }
QString DashBoard::laptime() const {return m_laptime; }
QString DashBoard::Lastlaptime() const {return m_Lastlaptime; }
QString DashBoard::bestlaptime() const {return m_bestlaptime; }
int DashBoard::draggable() const { return m_draggable; }

QStringList DashBoard::wifi() const {return m_wifi; }

qreal DashBoard::Analog0() const {return m_Analog0; }
qreal DashBoard::Analog1() const {return m_Analog1; }
qreal DashBoard::Analog2() const {return m_Analog2; }
qreal DashBoard::Analog3() const {return m_Analog3; }
qreal DashBoard::Analog4() const {return m_Analog4; }
qreal DashBoard::Analog5() const {return m_Analog5; }
qreal DashBoard::Analog6() const {return m_Analog6; }
qreal DashBoard::Analog7() const {return m_Analog7; }
qreal DashBoard::Analog8() const {return m_Analog8; }
qreal DashBoard::Analog9() const {return m_Analog9; }
qreal DashBoard::Analog10() const {return m_Analog10; }


qreal DashBoard::AnalogCalc0() const {return m_AnalogCalc0; }
qreal DashBoard::AnalogCalc1() const {return m_AnalogCalc1; }
qreal DashBoard::AnalogCalc2() const {return m_AnalogCalc2; }
qreal DashBoard::AnalogCalc3() const {return m_AnalogCalc3; }
qreal DashBoard::AnalogCalc4() const {return m_AnalogCalc4; }
qreal DashBoard::AnalogCalc5() const {return m_AnalogCalc5; }
qreal DashBoard::AnalogCalc6() const {return m_AnalogCalc6; }
qreal DashBoard::AnalogCalc7() const {return m_AnalogCalc7; }
qreal DashBoard::AnalogCalc8() const {return m_AnalogCalc8; }
qreal DashBoard::AnalogCalc9() const {return m_AnalogCalc9; }
qreal DashBoard::AnalogCalc10() const {return m_AnalogCalc10;}

qreal DashBoard::EXAnalogCalc0() const {return m_EXAnalogCalc0; }
qreal DashBoard::EXAnalogCalc1() const {return m_EXAnalogCalc1; }
qreal DashBoard::EXAnalogCalc2() const {return m_EXAnalogCalc2; }
qreal DashBoard::EXAnalogCalc3() const {return m_EXAnalogCalc3; }
qreal DashBoard::EXAnalogCalc4() const {return m_EXAnalogCalc4; }
qreal DashBoard::EXAnalogCalc5() const {return m_EXAnalogCalc5; }
qreal DashBoard::EXAnalogCalc6() const {return m_EXAnalogCalc6; }
qreal DashBoard::EXAnalogCalc7() const {return m_EXAnalogCalc7; }

qreal DashBoard::Lambdamultiply() const {return m_Lambdamultiply;}
qreal DashBoard::Userchannel1() const {return m_Userchannel1;}
qreal DashBoard::Userchannel2() const {return m_Userchannel2;}
qreal DashBoard::Userchannel3() const {return m_Userchannel3;}
qreal DashBoard::Userchannel4() const {return m_Userchannel4;}
qreal DashBoard::Userchannel5() const {return m_Userchannel5;}
qreal DashBoard::Userchannel6() const {return m_Userchannel6;}
qreal DashBoard::Userchannel7() const {return m_Userchannel7;}
qreal DashBoard::Userchannel8() const {return m_Userchannel8;}
qreal DashBoard::Userchannel9() const {return m_Userchannel9;}
qreal DashBoard::Userchannel10() const {return m_Userchannel10;}
qreal DashBoard::Userchannel11() const {return m_Userchannel11;}
qreal DashBoard::Userchannel12() const {return m_Userchannel12;}
qreal DashBoard::FuelLevel() const {return m_FuelLevel;}
qreal DashBoard::SteeringWheelAngle() const {return m_SteeringWheelAngle;}
int DashBoard::Brightness() const {return m_Brightness;}
int DashBoard::Visibledashes() const {return m_Visibledashes;}
int DashBoard::oilpressurelamp() const {return m_oilpressurelamp;}
int DashBoard::overtempalarm() const {return m_overtempalarm;}
int DashBoard::alternatorfail() const {return m_alternatorfail;}
int DashBoard::AuxTemp1() const {return m_AuxTemp1;}

qreal DashBoard::sixtyfoottime() const {return m_sixtyfoottime;}
qreal DashBoard::sixtyfootspeed() const {return m_sixtyfootspeed;}
qreal DashBoard::threehundredthirtyfoottime() const {return m_threehundredthirtyfoottime;}
qreal DashBoard::threehundredthirtyfootspeed() const {return m_threehundredthirtyfootspeed;}
qreal DashBoard::eightmiletime() const {return m_eightmiletime;}
qreal DashBoard::eightmilespeed() const {return m_eightmilespeed;}
qreal DashBoard::quartermiletime() const {return m_quartermiletime;}
qreal DashBoard::quartermilespeed() const {return m_quartermilespeed;}
qreal DashBoard::thousandfoottime() const {return m_thousandfoottime;}
qreal DashBoard::thousandfootspeed() const {return m_thousandfootspeed;}
qreal DashBoard::zerotohundredt() const {return m_zerotohundredt;}
qreal DashBoard::hundredtotwohundredtime() const {return m_hundredtotwohundredtime;}
qreal DashBoard::twohundredtothreehundredtime() const {return m_twohundredtothreehundredtime;}
qreal DashBoard::reactiontime() const {return m_reactiontime;}

qreal DashBoard::IGBTPhaseATemp() const {return m_IGBTPhaseATemp;}
qreal DashBoard::IGBTPhaseBTemp() const {return m_IGBTPhaseBTemp;}
qreal DashBoard::IGBTPhaseCTemp() const {return m_IGBTPhaseCTemp;}
qreal DashBoard::GateDriverTemp() const {return m_GateDriverTemp;}
qreal DashBoard::ControlBoardTemp() const {return m_ControlBoardTemp;}
qreal DashBoard::RtdTemp1() const {return m_RtdTemp1;}
qreal DashBoard::RtdTemp2() const {return m_RtdTemp2;}
qreal DashBoard::RtdTemp3() const {return m_RtdTemp3;}
qreal DashBoard::RtdTemp4() const {return m_RtdTemp4;}
qreal DashBoard::RtdTemp5() const {return m_RtdTemp5;}
qreal DashBoard::EMotorTemperature() const {return m_EMotorTemperature;}
qreal DashBoard::TorqueShudder() const {return m_reactiontime;}
qreal DashBoard::DigInput1FowardSw() const {return m_TorqueShudder;}
qreal DashBoard::DigInput2ReverseSw() const {return m_DigInput2ReverseSw;}
qreal DashBoard::DigInput3BrakeSw() const {return m_DigInput3BrakeSw;}
qreal DashBoard::DigInput4RegenDisableSw() const {return m_DigInput4RegenDisableSw;}
qreal DashBoard::DigInput5IgnSw() const {return m_DigInput5IgnSw;}
qreal DashBoard::DigInput6StartSw() const {return m_DigInput6StartSw;}
qreal DashBoard::DigInput7Bool() const {return m_DigInput7Bool;}
qreal DashBoard::DigInput8Bool() const {return m_DigInput8Bool;}
qreal DashBoard::EMotorAngle() const {return m_EMotorAngle;}
qreal DashBoard::EMotorSpeed() const {return m_EMotorSpeed;}
qreal DashBoard::ElectricalOutFreq() const {return m_ElectricalOutFreq;}
qreal DashBoard::DeltaResolverFiltered() const {return m_DeltaResolverFiltered;}
qreal DashBoard::PhaseACurrent() const {return m_PhaseACurrent;}
qreal DashBoard::PhaseBCurrent() const {return m_PhaseBCurrent;}
qreal DashBoard::PhaseCCurrent() const {return m_PhaseCCurrent;}
qreal DashBoard::DCBusCurrent() const {return m_DCBusCurrent;}
qreal DashBoard::DCBusVoltage() const {return m_DCBusVoltage;}
qreal DashBoard::OutputVoltage() const {return m_OutputVoltage;}
qreal DashBoard::VABvdVoltage() const {return m_VABvdVoltage;}
qreal DashBoard::VBCvqVoltage() const {return m_VBCvqVoltage;}
qreal DashBoard::TirepresLF() const {return m_TirepresLF;}
qreal DashBoard::TirepresRF() const {return m_TirepresRF;}
qreal DashBoard::TirepresRR() const {return m_TirepresRR;}
qreal DashBoard::TirepresLR() const {return m_TirepresLR;}
qreal DashBoard::TiretempLF() const {return m_TiretempLF;}
qreal DashBoard::TiretempRF() const {return m_TiretempRF;}
qreal DashBoard::TiretempRR() const {return m_TiretempRR;}
qreal DashBoard::TiretempLR() const {return m_TiretempLR;}

qreal DashBoard::DigitalInput1() const {return m_DigitalInput1;}
qreal DashBoard::DigitalInput2() const {return m_DigitalInput2;}
qreal DashBoard::DigitalInput3() const {return m_DigitalInput3;}
qreal DashBoard::DigitalInput4() const {return m_DigitalInput4;}
qreal DashBoard::DigitalInput5() const {return m_DigitalInput5;}
qreal DashBoard::DigitalInput6() const {return m_DigitalInput6;}
qreal DashBoard::DigitalInput7() const {return m_DigitalInput7;}

// EXBoard

qreal DashBoard::EXDigitalInput1() const {return m_EXDigitalInput1;}
qreal DashBoard::EXDigitalInput2() const {return m_EXDigitalInput2;}
qreal DashBoard::EXDigitalInput3() const {return m_EXDigitalInput3;}
qreal DashBoard::EXDigitalInput4() const {return m_EXDigitalInput4;}
qreal DashBoard::EXDigitalInput5() const {return m_EXDigitalInput5;}
qreal DashBoard::EXDigitalInput6() const {return m_EXDigitalInput6;}
qreal DashBoard::EXDigitalInput7() const {return m_EXDigitalInput7;}
qreal DashBoard::EXDigitalInput8() const {return m_EXDigitalInput8;}

qreal DashBoard::EXAnalogInput0() const {return m_EXAnalogInput0;}
qreal DashBoard::EXAnalogInput1() const {return m_EXAnalogInput1;}
qreal DashBoard::EXAnalogInput2() const {return m_EXAnalogInput2;}
qreal DashBoard::EXAnalogInput3() const {return m_EXAnalogInput3;}
qreal DashBoard::EXAnalogInput4() const {return m_EXAnalogInput4;}
qreal DashBoard::EXAnalogInput5() const {return m_EXAnalogInput5;}
qreal DashBoard::EXAnalogInput6() const {return m_EXAnalogInput6;}
qreal DashBoard::EXAnalogInput7() const {return m_EXAnalogInput7;}


//
qreal DashBoard::igncut() const {return m_igncut;}
qreal DashBoard::undrivenavgspeed() const {return m_undrivenavgspeed;}
qreal DashBoard::drivenavgspeed() const {return m_drivenavgspeed;}
qreal DashBoard::dsettargetslip() const {return m_dsettargetslip;}
qreal DashBoard::tractionctlpowerlimit() const {return m_tractionctlpowerlimit;}
qreal DashBoard::knockallpeak() const {return m_knockallpeak;}
qreal DashBoard::knockcorr() const {return m_knockcorr;}
qreal DashBoard::knocklastcyl() const {return m_knocklastcyl;}
qreal DashBoard::totalfueltrim() const {return m_totalfueltrim;}
qreal DashBoard::totaligncomp() const {return m_totaligncomp;}
qreal DashBoard::egthighest() const {return m_egthighest;}
qreal DashBoard::cputempecu() const {return m_cputempecu;}
qreal DashBoard::errorcodecount() const {return m_errorcodecount;}
qreal DashBoard::lostsynccount() const {return m_lostsynccount;}
qreal DashBoard::egtdiff() const {return m_egtdiff;}
qreal DashBoard::activeboosttable() const {return m_activeboosttable;}
qreal DashBoard::activetunetable() const {return m_activetunetable;}
qreal DashBoard::genericoutput1() const {return m_genericoutput1;}

