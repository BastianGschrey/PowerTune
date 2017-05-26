#include <dashboard.h>

DashBoard::DashBoard(QObject *parent)
    : QObject(parent)

// Advanced Info FD3S
    , m_revs(0)
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


 // Sensor Info FD3S

    , m_pim(0)
    , m_vta1(0)
    , m_vta2(0)
    , m_vmop(0)
    , m_wtrt(0)
    , m_airt(0)
    , m_fuelt(0)
    , m_O2S(0)

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


{
}
// Advanced Info FD3S
void DashBoard::setRevs(const qreal &revs)
{
    if (m_revs == revs)
        return;
    m_revs = revs;
    emit revsChanged(revs);
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
    m_Fueltemp = Fueltemp;
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
    m_Watertemp = Watertemp;
    emit WatertempChanged(Watertemp);
}

void DashBoard::setIntaketemp(const qreal &Intaketemp)
{
    if (m_Intaketemp == Intaketemp)
        return;
    m_Intaketemp = Intaketemp;
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
    m_speed = speed;
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

//Sensor info

void DashBoard::setpim(const qreal &pim)
{
    if (m_pim == pim)
        return;
    m_pim = pim;
    emit pimChanged(pim);
}

void DashBoard::setvta1(const qreal &vta1)
{
    if (m_vta1 == vta1)
        return;
    m_vta1 = vta1;
    emit vta1Changed(vta1);
}

void DashBoard::setvta2(const qreal &vta2)
{
    if (m_vta2 == vta2)
        return;
    m_vta2 = vta2;
    emit vta2Changed(vta2);
}

void DashBoard::setvmop(const qreal &vmop)
{
    if (m_vmop == vmop)
        return;
    m_vmop = vmop;
    emit vmopChanged(vmop);
}

void DashBoard::setwtrt(const qreal &wtrt)
{
    if (m_wtrt == wtrt)
        return;
    m_wtrt = wtrt;
    emit wtrtChanged(wtrt);
}

void DashBoard::setairt(const qreal &airt)
{
    if (m_airt == airt)
        return;
    m_airt = airt;
    emit airtChanged(airt);
}

void DashBoard::setfuelt(const qreal &fuelt)
{
    if (m_fuelt == fuelt)
        return;
    m_fuelt = fuelt;
    emit fueltChanged(fuelt);
}

void DashBoard::setO2S(const qreal &O2S)
{
    if (m_O2S == O2S)
        return;
    m_O2S = O2S;
    emit O2SChanged(O2S);
}

void DashBoard::setInjDuty(const qreal &InjDuty)
{
    if (m_InjDuty == InjDuty)
        return;
    m_InjDuty = InjDuty;
    emit O2SChanged(InjDuty);
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

void DashBoard::setPlatform(const QString &Platform)
{
    if (m_Platform == Platform)
        return;
    m_Platform = Platform;
    emit PlatformChanged(Platform);
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
    m_MVSS = MVSS;
    emit MVSSChanged(MVSS);
}

void DashBoard::setSVSS(const qreal &SVSS)
{
    if (m_SVSS == SVSS)
        return;
    m_SVSS = SVSS;
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



// Advanced Info FD3S
qreal DashBoard::revs() const { return m_revs; }
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




//Sensor info

qreal DashBoard::pim() const { return m_pim; }
qreal DashBoard::vta1() const { return m_vta1; }
qreal DashBoard::vta2() const { return m_vta2; }
qreal DashBoard::vmop() const { return m_vmop; }
qreal DashBoard::wtrt() const { return m_wtrt; }
qreal DashBoard::airt() const { return m_airt; }
qreal DashBoard::fuelt() const { return m_fuelt; }
qreal DashBoard::O2S() const { return m_O2S; }

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

QString DashBoard::Platform() const { return m_Platform; }

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
