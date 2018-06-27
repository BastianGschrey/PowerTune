#include <dashboard.h>
#include <QStringList>
#include <QDebug>



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
    , m_EngLoad(0)
    , m_MAF1V(0)
    , m_MAF2V(0)
    , m_injms(0)
    , m_Inj(0)
    , m_Ign(0)
    , m_Dwell(0)
    , m_BoostPres(0)
    , m_BoostDuty(0)
    , m_MAFactivity(0)
    , m_O2volt_2(0)


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
    , m_AUXT(0)
    , m_AFR(0)
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

    //GPS Strings
    , m_gpsTime ("0")
    , m_gpsAltitude ("0")
    , m_gpsLatitude ("0")
    , m_gpsLongitude ("0")
    , m_gpsSpeed ("0")
    , m_gpsVisibleSatelites ("0")

  //units
    , m_units("unit")

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
    ,  m_wastegatepress(0)
    ,  m_wheeldiff(0)
    ,  m_wheelslip(0)
    ,  m_wheelspdftleft(0)
    ,  m_wheelspdftright(0)
    ,  m_speedpercent(1)
    ,  m_MaxRPM(8000)
    ,  m_RPMStage1(3000)
    ,  m_RPMStage2(4000)
    ,  m_RPMStage3(6000)
    ,  m_RPMStage4(7000)


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

// Advanced Info FD3S
void DashBoard::setrpm(const qreal &rpm)
{
    if (m_rpm == rpm)
        return;
    m_rpm = rpm;
    emit rpmChanged(rpm);
}

void DashBoard::setIntakepress(const qreal &Intakepress)
{
    if (m_Intakepress == Intakepress)
        return;
    m_Intakepress = Intakepress;
    emit intakepressChanged(Intakepress);
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
    {m_Fueltemp = qRound(Fueltemp * 1.8 + 32);}
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
    {m_Watertemp = qRound(Watertemp * 1.8 + 32);}

    emit watertempChanged(Watertemp);
}

void DashBoard::setIntaketemp(const qreal &Intaketemp)
{
    if (m_Intaketemp == Intaketemp)
        return;
    if (m_units == "metric")
    { m_Intaketemp = Intaketemp;}
    if (m_units == "imperial")
    {m_Intaketemp = qRound(Intaketemp * 1.8 + 32);}

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
    if (m_speed == speed)
        return;
    if (m_units == "metric")
    {m_speed = qRound(speed * m_speedpercent);}
    if (m_units == "imperial")
    {m_speed = qRound((speed * 0.621371) * m_speedpercent);}
    emit speedChanged(speed);
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
    m_BoostPres = BoostPres;
    emit boostPresChanged(BoostPres);
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

// GPS


void DashBoard::setgpsTime (const QString &gpsTime)
{
    if (m_gpsTime == gpsTime)
        return;
    m_gpsTime = gpsTime;
    emit gpsTimeChanged(gpsTime);
}

void DashBoard::setgpsAltitude(const QString &gpsAltitude)
{
    if (m_gpsAltitude == gpsAltitude)
        return;
    m_gpsAltitude = gpsAltitude;
    emit gpsAltitudeChanged(gpsAltitude);
}

void DashBoard::setgpsLatitude(const QString &gpsLatitude)
{
    if (m_gpsLatitude == gpsLatitude)
        return;
    m_gpsLatitude = gpsLatitude;
    emit gpsLatitudeChanged(gpsLatitude);
}

void DashBoard::setgpsLongitude(const QString &gpsLongitude)
{
    if (m_gpsLongitude == gpsLongitude)
        return;
    m_gpsLongitude = gpsLongitude;
    emit gpsLongitudeChanged(gpsLongitude);
}

void DashBoard::setgpsSpeed(const QString &gpsSpeed)
{
    if (m_gpsSpeed == gpsSpeed)
        return;
    m_gpsSpeed = gpsSpeed;
    emit gpsSpeedChanged(gpsSpeed);
}

void DashBoard::setgpsVisibleSatelites(const QString &gpsVisibleSatelites)
{
    if (m_gpsVisibleSatelites == gpsVisibleSatelites)
        return;
    m_gpsVisibleSatelites = gpsVisibleSatelites;
    emit gpsVisibleSatelitesChanged(gpsVisibleSatelites);
}

// Units
void DashBoard::setunits (const QString &units)
{
    if (m_units == units)
        return;
    m_units = units;
    emit unitsChanged(units);
}

//Adaptronic extra


void DashBoard::setMAP(const qreal &MAP)
{
    if (m_MAP == MAP)
        return;
    m_MAP = MAP;
    emit mAPChanged(MAP);
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
    if (m_units == "metric")
    { m_MVSS= MVSS;}
    if (m_units == "imperial")
    {m_MVSS = qRound(MVSS * 0.621371);}

    emit mVSSChanged(MVSS);
}

void DashBoard::setSVSS(const qreal &SVSS)
{
    if (m_SVSS == SVSS)
        return;
    if (m_units == "metric")
    { m_SVSS= SVSS;}
    if (m_units == "imperial")
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
    m_LAMBDA = LAMBDA;
    emit lAMBDAChanged(LAMBDA);
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
    m_FuelPress = FuelPress;
    emit fuelPressChanged(FuelPress);
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
    if (m_units == "metric")
    { m_ambitemp = ambitemp;}
    if (m_units == "imperial")
    {m_ambitemp = qRound(ambitemp * 1.8 + 32);}
    emit ambitempChanged(ambitemp);
}
void DashBoard::setambipress(const qreal &ambipress)
{
    if (m_ambipress == ambipress)
        return;
    m_ambipress = ambipress;
    emit ambipressChanged(ambipress);
}

//Calculations

void DashBoard::setGear(const qreal &Gear)
{
    if (m_Gear == Gear)
        return;
    m_Gear = Gear;
    emit gearChanged(Gear);
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

void DashBoard::setdashsetup(const QStringList &dashsetup)
{
    if (m_dashsetup == dashsetup)
        return;
    m_dashsetup = dashsetup;
    emit dashsetupChanged(dashsetup);
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
    {m_airtempensor2 = qRound(airtempensor2 * 1.8 + 32);}
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
    m_brakepress = brakepress;
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
    m_coolantpress = coolantpress;
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
    {m_diffoiltemp = qRound(diffoiltemp * 1.8 + 32);}
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
  m_lambda2 = lambda2;
  emit lambda2Changed(lambda2);
}
void DashBoard::setlambda3(const qreal &lambda3)
{
  if (m_lambda3 == lambda3)
      return;
  m_lambda3 = lambda3;
  emit lambda3Changed(lambda3);
}
void DashBoard::setlambda4(const qreal &lambda4)
{
  if (m_lambda4 == lambda4)
      return;
  m_lambda4 = lambda4;
  emit lambda4Changed(lambda4);
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
  m_nospress = nospress;
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
  m_oilpres = oilpres;
  emit oilpresChanged(oilpres);
}
void DashBoard::setoiltemp(const qreal &oiltemp)
{
  if (m_oiltemp == oiltemp)
      return;
  if (m_units == "metric")
  {m_oiltemp = oiltemp;}
  if (m_units == "imperial")
  {m_oiltemp = qRound(oiltemp * 1.8 + 32);}
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
  {m_transoiltemp = qRound(transoiltemp * 1.8 + 32);}
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
void DashBoard::setwastegatepress(const qreal &wastegatepress)
{
  if (m_wastegatepress == wastegatepress)
      return;
  m_wastegatepress = wastegatepress;
  emit wastegatepressChanged(wastegatepress);
}
void DashBoard::setwheeldiff(const qreal &wheeldiff)
{
  if (m_wheeldiff == wheeldiff)
      return;
  if (m_units == "metric")
  {m_wheeldiff = wheeldiff;}
  if (m_units == "imperial")
  {m_wheeldiff = qRound(wheeldiff * 1.8 + 32);}
  emit wheeldiffChanged(wheeldiff);
}
void DashBoard::setwheelslip(const qreal &wheelslip)
{
  if (m_wheelslip == wheelslip)
      return;
  if (m_units == "metric")
  {m_wheelslip = wheelslip;}
  if (m_units == "imperial")
  {m_wheelslip = qRound(wheelslip * 1.8 + 32);}
  emit wheelslipChanged(wheelslip);
}
void DashBoard::setwheelspdftleft(const qreal &wheelspdftleft)
{
  if (m_wheelspdftleft == wheelspdftleft)
      return;
  if (m_units == "metric")
  {m_wheelspdftleft = wheelspdftleft;}
  if (m_units == "imperial")
  {m_wheelspdftleft = qRound(wheelspdftleft * 1.8 + 32);}
  emit wheelspdftleftChanged(wheelspdftleft);
}
void DashBoard::setwheelspdftright(const qreal &wheelspdftright)
{
  if (m_wheelspdftright == wheelspdftright)
      return;
  if (m_units == "metric")
  {m_wheelspdftright = wheelspdftright;}
  if (m_units == "imperial")
  {m_wheelspdftright = qRound(wheelspdftright * 1.8 + 32);}
  emit wheelspdftrightChanged(wheelspdftright);
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

void DashBoard::setMaxRPM(const int &MaxRPM)
{
    if (m_MaxRPM == MaxRPM)
        return;
    m_MaxRPM = MaxRPM;
    emit MaxRPMChanged(MaxRPM);
}

void DashBoard::setRPMStage1(const int &RPMStage1)
{
    if (m_RPMStage1 == RPMStage1)
        return;
    m_RPMStage1 = RPMStage1;
    emit RPMStage1Changed(RPMStage1);
}
void DashBoard::setRPMStage2(const int &RPMStage2)
{
    if (m_RPMStage2 == RPMStage2)
        return;
    m_RPMStage2 = RPMStage2;
    emit RPMStage2Changed(RPMStage2);
}
void DashBoard::setRPMStage3(const int &RPMStage3)
{
    if (m_RPMStage3 == RPMStage3)
        return;
    m_RPMStage3 = RPMStage3;
    emit RPMStage3Changed(RPMStage3);
}
void DashBoard::setRPMStage4(const int &RPMStage4)
{
    if (m_RPMStage4 == RPMStage4)
        return;
    m_RPMStage4 = RPMStage4;
    emit RPMStage4Changed(RPMStage4);
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
qreal DashBoard::na1() const { return m_na1; }
qreal DashBoard::Secinjpulse() const { return m_Secinjpulse; }
qreal DashBoard::na2() const { return m_na2; }
qreal DashBoard::InjDuty() const { return m_InjDuty; }
qreal DashBoard::EngLoad() const { return m_EngLoad; }
qreal DashBoard::MAF1V() const { return m_MAF1V; }
qreal DashBoard::MAF2V() const { return m_MAF2V; }
qreal DashBoard::injms() const { return m_injms; }
qreal DashBoard::Inj() const { return m_Inj; }
qreal DashBoard::Ign() const { return m_Ign; }
qreal DashBoard::Dwell() const { return m_Dwell; }
qreal DashBoard::BoostPres() const { return m_BoostPres; }
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


//GPS

QString DashBoard::gpsTime() const { return m_gpsTime; }
QString DashBoard::gpsAltitude() const { return m_gpsAltitude; }
QString DashBoard::gpsLatitude() const { return m_gpsLatitude; }
QString DashBoard::gpsLongitude () const { return m_gpsLongitude; }
QString DashBoard::gpsSpeed() const { return m_gpsSpeed; }
QString DashBoard::gpsVisibleSatelites () const { return m_gpsVisibleSatelites; }

//units
QString DashBoard::units() const { return m_units; }


//Adaptronic extra


qreal DashBoard::MAP() const { return m_MAP; }
qreal DashBoard::AUXT() const { return m_AUXT; }
qreal DashBoard::AFR() const { return m_AFR; }
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
qreal DashBoard::Power() const { return m_Power; }
qreal DashBoard::Torque() const { return m_Torque; }
qreal DashBoard::AccelTimer() const { return m_AccelTimer; }
qreal DashBoard::Weight() const { return m_Weight; }

//Official Pi screen present screen
bool DashBoard::screen() const { return m_screen; }

//User Dashboard Stringlist
QStringList DashBoard::dashsetup() const { return m_dashsetup; }

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
qreal DashBoard::wastegatepress() const { return m_wastegatepress; }
qreal DashBoard::wheeldiff() const { return m_wheeldiff; }
qreal DashBoard::wheelslip() const { return m_wheelslip; }
qreal DashBoard::wheelspdftleft() const { return m_wheelspdftleft; }
qreal DashBoard::wheelspdftright() const { return m_wheelspdftright; }
QString DashBoard::musicpath() const {return m_musicpath; }
int DashBoard::supportedReg() const {return m_supportedReg; }
qreal DashBoard::speedpercent() const {return m_speedpercent; }

int DashBoard::MaxRPM() const {return m_MaxRPM; }
int DashBoard::RPMStage1() const {return m_RPMStage1; }
int DashBoard::RPMStage2() const {return m_RPMStage2; }
int DashBoard::RPMStage3() const {return m_RPMStage3; }
int DashBoard::RPMStage4() const {return m_RPMStage4; }
