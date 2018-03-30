#include <dashboard.h>
#include <QStringList>
#include <QDebug>



DashBoard::DashBoard(QObject *parent)
    : QObject(parent)


    //  Odometer


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

{
}



// Odometer
void DashBoard::setOdo(const qreal &Odo)
{
    if (m_Odo == Odo)
        return;
    m_Odo = Odo;
    emit OdoChanged(Odo);
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
    emit IntakepressChanged(Intakepress);
}

void DashBoard::setPressureV(const qreal &PressureV)
{
    if (m_PressureV == PressureV)
        return;
    m_PressureV = PressureV;
    emit PressureVChanged(PressureV);
}

void DashBoard::setThrottleV(const qreal &ThrottleV)
{
    if (m_ThrottleV == ThrottleV)
        return;
    m_ThrottleV= ThrottleV;
    emit ThrottleVChanged(ThrottleV);
}

void DashBoard::setPrimaryinp(const qreal &Primaryinp)
{
    if (m_Primaryinp == Primaryinp)
        return;
    m_Primaryinp= Primaryinp;
    emit PrimaryinpChanged(Primaryinp);
}

void DashBoard::setFuelc(const qreal &Fuelc)
{
    if (m_Fuelc == Fuelc)
        return;
    m_Fuelc= Fuelc;
    emit FuelcChanged(Fuelc);
}

void DashBoard::setLeadingign(const qreal &Leadingign)
{
    if (m_Leadingign == Leadingign)
        return;
    m_Leadingign= Leadingign;
    emit LeadingignChanged(Leadingign);
}

void DashBoard::setTrailingign(const qreal &Trailingign)
{
    if (m_Trailingign == Trailingign)
        return;
    m_Trailingign= Trailingign;
    emit TrailingignChanged(Trailingign);
}

void DashBoard::setFueltemp(const qreal &Fueltemp)
{
    if (m_Fueltemp == Fueltemp)
        return;
    if (m_units == "metric")
    {m_Fueltemp = Fueltemp;}
    if (m_units == "imperial")
    {m_Fueltemp = qRound(Fueltemp * 1.8 + 32);}
    emit FueltempChanged(Fueltemp);
}

void DashBoard::setMoilp(const qreal &Moilp)
{
    if (m_Moilp == Moilp)
        return;
    m_Moilp = Moilp;
    emit MoilpChanged(Moilp);
}

void DashBoard::setBoosttp(const qreal &Boosttp)
{
    if (m_Boosttp == Boosttp)
        return;
    m_Boosttp = Boosttp;
    emit BoosttpChanged(Boosttp);
}

void DashBoard::setBoostwg(const qreal &Boostwg)
{
    if (m_Boostwg == Boostwg)
        return;
    m_Boostwg = Boostwg;
    emit BoostwgChanged(Boostwg);
}

void DashBoard::setWatertemp(const qreal &Watertemp)
{
    if (m_Watertemp == Watertemp)
        return;
    if (m_units == "metric")
    {m_Watertemp = Watertemp;}
    if (m_units == "imperial")
    {m_Watertemp = qRound(Watertemp * 1.8 + 32);}

    emit WatertempChanged(Watertemp);
}

void DashBoard::setIntaketemp(const qreal &Intaketemp)
{
    if (m_Intaketemp == Intaketemp)
        return;
    if (m_units == "metric")
    { m_Intaketemp = Intaketemp;}
    if (m_units == "imperial")
    {m_Intaketemp = qRound(Intaketemp * 1.8 + 32);}

    emit IntaketempChanged(Intaketemp);
}

void DashBoard::setKnock(const qreal &Knock)
{
    if (m_Knock == Knock)
        return;
    m_Knock = Knock;
    emit KnockChanged(Knock);
}

void DashBoard::setBatteryV(const qreal &BatteryV)
{
    if (m_BatteryV == BatteryV)
        return;
    m_BatteryV = BatteryV;
    emit BatteryVChanged(BatteryV);
}

void DashBoard::setSpeed(const qreal &speed)
{
    if (m_speed == speed)
        return;
    if (m_units == "metric")
    {m_speed = speed;}
    if (m_units == "imperial")
    {m_speed = qRound(speed * 0.621371);}
    emit speedChanged(speed);
}

void DashBoard::setIscvduty(const qreal &Iscvduty)
{
    if (m_Iscvduty == Iscvduty)
        return;
    m_Iscvduty = Iscvduty;
    emit IscvdutyChanged(Iscvduty);
}

void DashBoard::setO2volt(const qreal &O2volt)
{
    if (m_O2volt == O2volt)
        return;
    m_O2volt = O2volt;
    emit O2voltChanged(O2volt);
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
    emit SecinjpulseChanged(Secinjpulse);
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
    emit EngLoadChanged(EngLoad);
}

void DashBoard::setMAF1V(const qreal &MAF1V)
{
    if (m_MAF1V == MAF1V)
        return;
    m_MAF1V = MAF1V;
    emit MAF1VChanged(MAF1V);
}

void DashBoard::setMAF2V(const qreal &MAF2V)
{
    if (m_MAF2V == MAF2V)
        return;
    m_MAF2V = MAF2V;
    emit MAF2VChanged(MAF2V);
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
    emit IgnChanged(Ign);
}

void DashBoard::setInj(const qreal &Inj)
{
    if (m_Inj == Inj)
        return;
    m_Inj = Inj;
    emit InjChanged(Inj);
}
void DashBoard::setDwell(const qreal &Dwell)
{
    if (m_Dwell == Dwell)
        return;
    m_Dwell = Dwell;
    emit DwellChanged(Dwell);
}

void DashBoard::setBoostPres(const qreal &BoostPres)
{
    if (m_BoostPres == BoostPres)
        return;
    m_BoostPres = BoostPres;
    emit BoostPresChanged(BoostPres);
}

void DashBoard::setBoostDuty(const qreal &BoostDuty)
{
    if (m_BoostDuty == BoostDuty)
        return;
    m_BoostDuty = BoostDuty;
    emit BoostDutyChanged(BoostDuty);
}

void DashBoard::setMAFactivity(const qreal &MAFactivity)
{
    if (m_MAFactivity == MAFactivity)
        return;
    m_MAFactivity = MAFactivity;
    emit MAFactivityChanged(MAFactivity);
}

void DashBoard::setO2volt_2(const qreal &O2volt_2)
{
    if (m_O2volt_2 == O2volt_2)
        return;
    m_O2volt_2 = O2volt_2;
    emit O2volt_2Changed(O2volt_2);
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
    emit InjDutyChanged(InjDuty);
}



//Flags

void DashBoard::setFlag1(const qreal &Flag1)
{
    if (m_Flag1 == Flag1)
        return;
    m_Flag1 = Flag1;
    emit Flag1Changed(Flag1);
}

void DashBoard::setFlag2(const qreal &Flag2)
{
    if (m_Flag2 == Flag2)
        return;
    m_Flag2 = Flag2;
    emit Flag2Changed(Flag2);
}

void DashBoard::setFlag3(const qreal &Flag3)
{
    if (m_Flag3 == Flag3)
        return;
    m_Flag3 = Flag3;
    emit Flag3Changed(Flag3);
}

void DashBoard::setFlag4(const qreal &Flag4)
{
    if (m_Flag4 == Flag4)
        return;
    m_Flag4 = Flag4;
    emit Flag4Changed(Flag4);
}

void DashBoard::setFlag5(const qreal &Flag5)
{
    if (m_Flag5 == Flag5)
        return;
    m_Flag5 = Flag5;
    emit Flag5Changed(Flag5);
}

void DashBoard::setFlag6(const qreal &Flag6)
{
    if (m_Flag6 == Flag6)
        return;
    m_Flag6 = Flag6;
    emit Flag6Changed(Flag6);
}

void DashBoard::setFlag7(const qreal &Flag7)
{
    if (m_Flag7 == Flag7)
        return;
    m_Flag7 = Flag7;
    emit Flag7Changed(Flag7);
}

void DashBoard::setFlag8(const qreal &Flag8)
{
    if (m_Flag8 == Flag8)
        return;
    m_Flag8 = Flag8;
    emit Flag8Changed(Flag8);
}

void DashBoard::setFlag9(const qreal &Flag9)
{
    if (m_Flag9 == Flag9)
        return;
    m_Flag9 = Flag9;
    emit Flag9Changed(Flag9);
}

void DashBoard::setFlag10(const qreal &Flag10)
{
    if (m_Flag10 == Flag10)
        return;
    m_Flag10 = Flag10;
    emit Flag10Changed(Flag10);
}

void DashBoard::setFlag11(const qreal &Flag11)
{
    if (m_Flag11 == Flag11)
        return;
    m_Flag11 = Flag11;
    emit Flag11Changed(Flag11);
}

void DashBoard::setFlag12(const qreal &Flag12)
{
    if (m_Flag12 == Flag12)
        return;
    m_Flag12 = Flag12;
    emit Flag12Changed(Flag12);
}

void DashBoard::setFlag13(const qreal &Flag13)
{
    if (m_Flag13 == Flag13)
        return;
    m_Flag13 = Flag13;
    emit Flag13Changed(Flag13);
}

void DashBoard::setFlag14(const qreal &Flag14)
{
    if (m_Flag14 == Flag14)
        return;
    m_Flag14 = Flag14;
    emit Flag14Changed(Flag14);
}

void DashBoard::setFlag15(const qreal &Flag15)
{
    if (m_Flag15 == Flag15)
        return;
    m_Flag15 = Flag15;
    emit Flag15Changed(Flag15);
}

void DashBoard::setFlag16(const qreal &Flag16)
{
    if (m_Flag16 == Flag16)
        return;
    m_Flag16 = Flag16;
    emit Flag16Changed(Flag16);
}


//Flag Strings

void DashBoard::setFlagString1(const QString &FlagString1)
{
    if (m_FlagString1 == FlagString1)
        return;
    m_FlagString1 = FlagString1;
    emit FlagString1Changed(FlagString1);
}

void DashBoard::setFlagString2(const QString &FlagString2)
{
    if (m_FlagString2 == FlagString2)
        return;
    m_FlagString2 = FlagString2;
    emit FlagString2Changed(FlagString2);
}

void DashBoard::setFlagString3(const QString &FlagString3)
{
    if (m_FlagString3 == FlagString3)
        return;
    m_FlagString3 = FlagString3;
    emit FlagString3Changed(FlagString3);
}

void DashBoard::setFlagString4(const QString &FlagString4)
{
    if (m_FlagString4 == FlagString4)
        return;
    m_FlagString4 = FlagString4;
    emit FlagString4Changed(FlagString4);
}

void DashBoard::setFlagString5(const QString &FlagString5)
{
    if (m_FlagString5 == FlagString5)
        return;
    m_FlagString5 = FlagString5;
    emit FlagString5Changed(FlagString5);
}

void DashBoard::setFlagString6(const QString &FlagString6)
{
    if (m_FlagString6 == FlagString6)
        return;
    m_FlagString6 = FlagString6;
    emit FlagString6Changed(FlagString6);
}

void DashBoard::setFlagString7(const QString &FlagString7)
{
    if (m_FlagString7 == FlagString7)
        return;
    m_FlagString7 = FlagString7;
    emit FlagString7Changed(FlagString7);
}

void DashBoard::setFlagString8(const QString &FlagString8)
{
    if (m_FlagString8 == FlagString8)
        return;
    m_FlagString8 = FlagString8;
    emit FlagString8Changed(FlagString8);
}

void DashBoard::setFlagString9(const QString &FlagString9)
{
    if (m_FlagString9 == FlagString9)
        return;
    m_FlagString9 = FlagString9;
    emit FlagString9Changed(FlagString9);
}

void DashBoard::setFlagString10(const QString &FlagString10)
{
    if (m_FlagString10 == FlagString10)
        return;
    m_FlagString10 = FlagString10;
    emit FlagString10Changed(FlagString10);
}

void DashBoard::setFlagString11(const QString &FlagString11)
{
    if (m_FlagString11 == FlagString11)
        return;
    m_FlagString11 = FlagString11;
    emit FlagString11Changed(FlagString11);
}

void DashBoard::setFlagString12(const QString &FlagString12)
{
    if (m_FlagString12 == FlagString12)
        return;
    m_FlagString12 = FlagString12;
    emit FlagString12Changed(FlagString12);
}

void DashBoard::setFlagString13(const QString &FlagString13)
{
    if (m_FlagString13 == FlagString13)
        return;
    m_FlagString13 = FlagString13;
    emit FlagString13Changed(FlagString13);
}

void DashBoard::setFlagString14(const QString &FlagString14)
{
    if (m_FlagString14 == FlagString14)
        return;
    m_FlagString14 = FlagString14;
    emit FlagString14Changed(FlagString14);
}

void DashBoard::setFlagString15(const QString &FlagString15)
{
    if (m_FlagString15 == FlagString15)
        return;
    m_FlagString15 = FlagString15;
    emit FlagString15Changed(FlagString15);
}

void DashBoard::setFlagString16(const QString &FlagString16)
{
    if (m_FlagString16 == FlagString16)
        return;
    m_FlagString16 = FlagString16;
    emit FlagString16Changed(FlagString16);
}


void DashBoard::setPlatform(const QString &Platform)
{
    if (m_Platform == Platform)
        return;
    m_Platform = Platform;
    emit PlatformChanged(Platform);
}

//Sensor Strings

void DashBoard::setSensorString1(const QString &SensorString1)
{
    if (m_SensorString1 == SensorString1)
        return;
    m_SensorString1 = SensorString1;
    emit SensorString1Changed(SensorString1);
}

void DashBoard::setSensorString2(const QString &SensorString2)
{
    if (m_SensorString2 == SensorString2)
        return;
    m_SensorString2 = SensorString2;
    emit SensorString2Changed(SensorString2);
}

void DashBoard::setSensorString3(const QString &SensorString3)
{
    if (m_SensorString3 == SensorString3)
        return;
    m_SensorString3 = SensorString3;
    emit SensorString3Changed(SensorString3);
}

void DashBoard::setSensorString4(const QString &SensorString4)
{
    if (m_SensorString4 == SensorString4)
        return;
    m_SensorString4 = SensorString4;
    emit SensorString4Changed(SensorString4);
}

void DashBoard::setSensorString5(const QString &SensorString5)
{
    if (m_SensorString5 == SensorString5)
        return;
    m_SensorString5 = SensorString5;
    emit SensorString5Changed(SensorString5);
}

void DashBoard::setSensorString6(const QString &SensorString6)
{
    if (m_SensorString6 == SensorString6)
        return;
    m_SensorString6 = SensorString6;
    emit SensorString6Changed(SensorString6);
}

void DashBoard::setSensorString7(const QString &SensorString7)
{
    if (m_SensorString7 == SensorString7)
        return;
    m_SensorString7 = SensorString7;
    emit SensorString7Changed(SensorString7);
}

void DashBoard::setSensorString8(const QString &SensorString8)
{
    if (m_SensorString8 == SensorString8)
        return;
    m_SensorString8 = SensorString8;
    emit SensorString8Changed(SensorString8);
}

void DashBoard::setSerialStat(const QString &SerialStat)
{
    if (m_SerialStat == SerialStat)
        return;
    m_SerialStat = SerialStat;
    emit SerialStatChanged(SerialStat);
}

void DashBoard::setRecvData(const QString &RecvData)
{
    if (m_RecvData == RecvData)
        return;
    m_RecvData = RecvData;
    emit RecvDataChanged(RecvData);
}

void DashBoard::setTimeoutStat(const QString &TimeoutStat)
{
    if (m_TimeoutStat == TimeoutStat)
        return;
    m_TimeoutStat = TimeoutStat;
    emit TimeoutStatChanged(TimeoutStat);
}

void DashBoard::setRunStat(const QString &RunStat)
{
    if (m_RunStat == RunStat)
        return;
    m_RunStat = RunStat;
    emit RunStatChanged(RunStat);
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
    emit MAPChanged(MAP);
}

void DashBoard::setAUXT(const qreal &AUXT)
{
    if (m_AUXT == AUXT)
        return;
    m_AUXT = AUXT;
    emit AUXTChanged(AUXT);
}

void DashBoard::setAFR(const qreal &AFR)
{
    if (m_AFR == AFR)
        return;
    m_AFR = AFR;
    emit AFRChanged(AFR);
}

void DashBoard::setTPS(const qreal &TPS)
{
    if (m_TPS == TPS)
        return;
    m_TPS = TPS;
    emit TPSChanged(TPS);
}

void DashBoard::setIdleValue(const qreal &IdleValue)
{
    if (m_IdleValue == IdleValue)
        return;
    m_IdleValue = IdleValue;
    emit IdleValueChanged(IdleValue);
}

void DashBoard::setMVSS(const qreal &MVSS)
{
    if (m_MVSS == MVSS)
        return;
    if (m_units == "metric")
    { m_MVSS= MVSS;}
    if (m_units == "imperial")
    {m_MVSS = qRound(MVSS * 0.621371);}

    emit MVSSChanged(MVSS);
}

void DashBoard::setSVSS(const qreal &SVSS)
{
    if (m_SVSS == SVSS)
        return;
    if (m_units == "metric")
    { m_SVSS= SVSS;}
    if (m_units == "imperial")
    {m_SVSS = qRound(SVSS * 0.621371);}
    emit SVSSChanged(SVSS);
}

void DashBoard::setInj1(const qreal &Inj1)
{
    if (m_Inj1 == Inj1)
        return;
    m_Inj1 = Inj1;
    emit Inj1Changed(Inj1);
}

void DashBoard::setInj2(const qreal &Inj2)
{
    if (m_Inj2 == Inj2)
        return;
    m_Inj2 = Inj2;
    emit Inj2Changed(Inj2);
}

void DashBoard::setInj3(const qreal &Inj3)
{
    if (m_Inj3 == Inj3)
        return;
    m_Inj3 = Inj3;
    emit Inj3Changed(Inj3);
}

void DashBoard::setInj4(const qreal &Inj4)
{
    if (m_Inj4 == Inj4)
        return;
    m_Inj4 = Inj4;
    emit Inj4Changed(Inj4);
}

void DashBoard::setIgn1(const qreal &Ign1)
{
    if (m_Ign1 == Ign1)
        return;
    m_Ign1 = Ign1;
    emit Ign1Changed(Ign1);
}

void DashBoard::setIgn2(const qreal &Ign2)
{
    if (m_Ign2 == Ign2)
        return;
    m_Ign2 = Ign2;
    emit Ign2Changed(Ign2);
}

void DashBoard::setIgn3(const qreal &Ign3)
{
    if (m_Ign3 == Ign3)
        return;
    m_Ign3 = Ign3;
    emit Ign3Changed(Ign3);
}

void DashBoard::setIgn4(const qreal &Ign4)
{
    if (m_Ign4 == Ign4)
        return;
    m_Ign4 = Ign4;
    emit Ign4Changed(Ign4);
}

void DashBoard::setTRIM(const qreal &TRIM)
{
    if (m_TRIM == TRIM)
        return;
    m_TRIM = TRIM;
    emit TRIMChanged(TRIM);
}

void DashBoard::setLAMBDA(const qreal &LAMBDA)
{
    if (m_LAMBDA == LAMBDA)
        return;
    m_LAMBDA = LAMBDA;
    emit LAMBDAChanged(LAMBDA);
}

void DashBoard::setLAMBDATarget(const qreal &LAMBDATarget)
{
    if (m_LAMBDATarget == LAMBDATarget)
        return;
    m_LAMBDATarget = LAMBDATarget;
    emit LAMBDATargetChanged(LAMBDATarget);
}

void DashBoard::setFuelPress(const qreal &FuelPress)
{
    if(m_FuelPress == FuelPress)
        return;
    m_FuelPress = FuelPress;
    emit FuelPressChanged(FuelPress);
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
    emit GearChanged(Gear);
}
void DashBoard::setPower(const qreal &Power)
{
    if (m_Power == Power)
        return;
    m_Power = Power;
    emit PowerChanged(Power);
}
void DashBoard::setTorque(const qreal &Torque)
{
    if (m_Torque == Torque)
        return;
    m_Torque = Torque;
    emit TorqueChanged(Torque);
}
void DashBoard::setAccelTimer(const qreal &AccelTimer)
{
    if (m_AccelTimer == AccelTimer)
        return;
    m_AccelTimer = AccelTimer;
    emit AccelTimerChanged(AccelTimer);
}
void DashBoard::setWeight(const qreal &Weight)
{
    if (m_Weight == Weight)
        return;
    m_Weight = Weight;
    emit WeightChanged(Weight);
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

// Odometer
qreal DashBoard::Odo() const { return m_Odo; }

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
