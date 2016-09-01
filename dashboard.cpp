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

{
}
// Advanced Info FD3S
void DashBoard::setRevs(const qint16 &revs)
{
    if (m_revs == revs)
        return;
    m_revs = revs;
    emit revsChanged(revs);
}

void DashBoard::setIntakepress(const qint16 &Intakepress)
{
    if (m_Intakepress == Intakepress)
        return;
    m_Intakepress = Intakepress;
    emit IntakepressChanged(Intakepress);
}

void DashBoard::setPressureV(const qint16 &PressureV)
{
    if (m_PressureV == PressureV)
        return;
    m_PressureV = PressureV;
    emit PressureVChanged(PressureV);
}

void DashBoard::setThrottleV(const qint16 &ThrottleV)
{
    if (m_ThrottleV == ThrottleV)
        return;
    m_ThrottleV= ThrottleV;
    emit ThrottleVChanged(ThrottleV);
}

void DashBoard::setPrimaryinp(const qint16 &Primaryinp)
{
    if (m_Primaryinp == Primaryinp)
        return;
    m_Primaryinp= Primaryinp;
    emit PrimaryinpChanged(Primaryinp);
}

void DashBoard::setFuelc(const qint16 &Fuelc)
{
    if (m_Fuelc == Fuelc)
        return;
    m_Fuelc= Fuelc;
    emit FuelcChanged(Fuelc);
}

void DashBoard::setLeadingign(const qint16 &Leadingign)
{
    if (m_Leadingign == Leadingign)
        return;
    m_Leadingign= Leadingign;
    emit LeadingignChanged(Leadingign);
}

void DashBoard::setTrailingign(const qint16 &Trailingign)
{
    if (m_Trailingign == Trailingign)
        return;
    m_Trailingign= Trailingign;
    emit TrailingignChanged(Trailingign);
}

void DashBoard::setFueltemp(const qint16 &Fueltemp)
{
    if (m_Fueltemp == Fueltemp)
        return;
    m_Fueltemp = Fueltemp;
    emit FueltempChanged(Fueltemp);
}

void DashBoard::setMoilp(const qint16 &Moilp)
{
    if (m_Moilp == Moilp)
        return;
    m_Moilp = Moilp;
    emit MoilpChanged(Moilp);
}

void DashBoard::setBoosttp(const qint16 &Boosttp)
{
    if (m_Boosttp == Boosttp)
        return;
    m_Boosttp = Boosttp;
    emit BoosttpChanged(Boosttp);
}

void DashBoard::setBoostwg(const qint16 &Boostwg)
{
    if (m_Boostwg == Boostwg)
        return;
    m_Boostwg = Boostwg;
    emit BoostwgChanged(Boostwg);
}

void DashBoard::setWatertemp(const qint16 &Watertemp)
{
    if (m_Watertemp == Watertemp)
        return;
    m_Watertemp = Watertemp;
    emit WatertempChanged(Watertemp);
}

void DashBoard::setIntaketemp(const qint16 &Intaketemp)
{
    if (m_Intaketemp == Intaketemp)
        return;
    m_Intaketemp = Intaketemp;
    emit IntaketempChanged(Intaketemp);
}

void DashBoard::setKnock(const qint16 &Knock)
{
    if (m_Knock == Knock)
        return;
    m_Knock = Knock;
    emit KnockChanged(Knock);
}

void DashBoard::setBatteryV(const qint16 &BatteryV)
{
    if (m_BatteryV == BatteryV)
        return;
    m_BatteryV = BatteryV;
    emit BatteryVChanged(BatteryV);
}

void DashBoard::setSpeed(const qint16 &speed)
{
    if (m_speed == speed)
        return;
    m_speed = speed;
    emit speedChanged(speed);
}

void DashBoard::setIscvduty(const qint16 &Iscvduty)
{
    if (m_Iscvduty == Iscvduty)
        return;
    m_Iscvduty = Iscvduty;
    emit IscvdutyChanged(Iscvduty);
}

void DashBoard::setO2volt(const qint16 &O2volt)
{
    if (m_O2volt == O2volt)
        return;
    m_O2volt = O2volt;
    emit O2voltChanged(O2volt);
}
void DashBoard::setna1(const qint16 &na1)
{
    if (m_na1 == na1)
        return;
    m_na1 = na1;
    emit na1Changed(na1);
}

void DashBoard::setSecinjpulse(const qint16 &Secinjpulse)
{
    if (m_Secinjpulse == Secinjpulse)
        return;
    m_Secinjpulse = Secinjpulse;
    emit SecinjpulseChanged(Secinjpulse);
}

void DashBoard::setna2(const qint16 &na2)
{
    if (m_na2 == na2)
        return;
    m_na2 = na2;
    emit na2Changed(na2);
}

//Sensor info

void DashBoard::setpim(const qint16 &pim)
{
    if (m_pim == pim)
        return;
    m_pim = pim;
    emit pimChanged(pim);
}

void DashBoard::setvta1(const qint16 &vta1)
{
    if (m_vta1 == vta1)
        return;
    m_vta1 = vta1;
    emit vta1Changed(vta1);
}

void DashBoard::setvta2(const qint16 &vta2)
{
    if (m_vta2 == vta2)
        return;
    m_vta2 = vta2;
    emit vta2Changed(vta2);
}

void DashBoard::setvmop(const qint16 &vmop)
{
    if (m_vmop == vmop)
        return;
    m_vmop = vmop;
    emit vmopChanged(vmop);
}

void DashBoard::setwtrt(const qint16 &wtrt)
{
    if (m_wtrt == wtrt)
        return;
    m_wtrt = wtrt;
    emit wtrtChanged(wtrt);
}

void DashBoard::setairt(const qint16 &airt)
{
    if (m_airt == airt)
        return;
    m_airt = airt;
    emit airtChanged(airt);
}

void DashBoard::setfuelt(const qint16 &fuelt)
{
    if (m_fuelt == fuelt)
        return;
    m_fuelt = fuelt;
    emit fueltChanged(fuelt);
}

void DashBoard::setO2S(const qint16 &O2S)
{
    if (m_O2S == O2S)
        return;
    m_O2S = O2S;
    emit O2SChanged(O2S);
}



//Flags

void DashBoard::setFlag1(const qint16 &Flag1)
{
    if (m_Flag1 == Flag1)
        return;
    m_Flag1 = Flag1;
    emit Flag1Changed(Flag1);
}

void DashBoard::setFlag2(const qint16 &Flag2)
{
    if (m_Flag2 == Flag2)
        return;
    m_Flag2 = Flag2;
    emit Flag2Changed(Flag2);
}

void DashBoard::setFlag3(const qint16 &Flag3)
{
    if (m_Flag3 == Flag3)
        return;
    m_Flag3 = Flag3;
    emit Flag3Changed(Flag3);
}

void DashBoard::setFlag4(const qint16 &Flag4)
{
    if (m_Flag4 == Flag4)
        return;
    m_Flag4 = Flag4;
    emit Flag4Changed(Flag4);
}

void DashBoard::setFlag5(const qint16 &Flag5)
{
    if (m_Flag5 == Flag5)
        return;
    m_Flag5 = Flag5;
    emit Flag5Changed(Flag5);
}

void DashBoard::setFlag6(const qint16 &Flag6)
{
    if (m_Flag6 == Flag6)
        return;
    m_Flag6 = Flag6;
    emit Flag6Changed(Flag6);
}

void DashBoard::setFlag7(const qint16 &Flag7)
{
    if (m_Flag7 == Flag7)
        return;
    m_Flag7 = Flag7;
    emit Flag7Changed(Flag7);
}

void DashBoard::setFlag8(const qint16 &Flag8)
{
    if (m_Flag8 == Flag8)
        return;
    m_Flag8 = Flag8;
    emit Flag8Changed(Flag8);
}

void DashBoard::setFlag9(const qint16 &Flag9)
{
    if (m_Flag9 == Flag9)
        return;
    m_Flag9 = Flag9;
    emit Flag9Changed(Flag9);
}

void DashBoard::setFlag10(const qint16 &Flag10)
{
    if (m_Flag10 == Flag10)
        return;
    m_Flag10 = Flag10;
    emit Flag10Changed(Flag10);
}

void DashBoard::setFlag11(const qint16 &Flag11)
{
    if (m_Flag11 == Flag11)
        return;
    m_Flag11 = Flag11;
    emit Flag11Changed(Flag11);
}

void DashBoard::setFlag12(const qint16 &Flag12)
{
    if (m_Flag12 == Flag12)
        return;
    m_Flag12 = Flag12;
    emit Flag12Changed(Flag12);
}

void DashBoard::setFlag13(const qint16 &Flag13)
{
    if (m_Flag13 == Flag13)
        return;
    m_Flag13 = Flag13;
    emit Flag13Changed(Flag13);
}

void DashBoard::setFlag14(const qint16 &Flag14)
{
    if (m_Flag14 == Flag14)
        return;
    m_Flag14 = Flag14;
    emit Flag14Changed(Flag14);
}

void DashBoard::setFlag15(const qint16 &Flag15)
{
    if (m_Flag15 == Flag15)
        return;
    m_Flag15 = Flag15;
    emit Flag15Changed(Flag15);
}

void DashBoard::setFlag16(const qint16 &Flag16)
{
    if (m_Flag16 == Flag16)
        return;
    m_Flag16 = Flag16;
    emit Flag16Changed(Flag16);
}





// Advanced Info FD3S
qint16 DashBoard::revs() const { return m_revs; }
qint16 DashBoard::Intakepress() const { return m_Intakepress; }
qint16 DashBoard::PressureV() const { return m_PressureV; }
qint16 DashBoard::ThrottleV() const { return m_ThrottleV; }
qint16 DashBoard::Primaryinp() const { return m_Primaryinp; }
qint16 DashBoard::Fuelc() const { return m_Fuelc; }
qint16 DashBoard::Leadingign() const { return m_Leadingign; }
qint16 DashBoard::Trailingign() const { return m_Trailingign; }
qint16 DashBoard::Fueltemp() const { return m_Fueltemp; }
qint16 DashBoard::Moilp() const { return m_Moilp; }
qint16 DashBoard::Boosttp() const { return m_Boosttp; }
qint16 DashBoard::Boostwg() const { return m_Boostwg; }
qint16 DashBoard::Watertemp() const { return m_Watertemp; }
qint16 DashBoard::Intaketemp() const { return m_Intaketemp; }
qint16 DashBoard::Knock() const { return m_Knock; }
qint16 DashBoard::BatteryV() const { return m_BatteryV; }
qint16 DashBoard::speed() const { return m_speed; }
qint16 DashBoard::Iscvduty() const { return m_Iscvduty; }
qint16 DashBoard::O2volt() const { return m_O2volt; }
qint16 DashBoard::na1() const { return m_na1; }
qint16 DashBoard::Secinjpulse() const { return m_Secinjpulse; }
qint16 DashBoard::na2() const { return m_na2; }



//Sensor info

qint16 DashBoard::pim() const { return m_pim; }
qint16 DashBoard::vta1() const { return m_vta1; }
qint16 DashBoard::vta2() const { return m_vta2; }
qint16 DashBoard::vmop() const { return m_vmop; }
qint16 DashBoard::wtrt() const { return m_wtrt; }
qint16 DashBoard::airt() const { return m_airt; }
qint16 DashBoard::fuelt() const { return m_fuelt; }
qint16 DashBoard::O2S() const { return m_O2S; }

//Flags

qint16 DashBoard::Flag1() const { return m_Flag1; }
qint16 DashBoard::Flag2() const { return m_Flag2; }
qint16 DashBoard::Flag3() const { return m_Flag3; }
qint16 DashBoard::Flag4() const { return m_Flag4; }
qint16 DashBoard::Flag5() const { return m_Flag5; }
qint16 DashBoard::Flag6() const { return m_Flag6; }
qint16 DashBoard::Flag7() const { return m_Flag7; }
qint16 DashBoard::Flag8() const { return m_Flag8; }
qint16 DashBoard::Flag9() const { return m_Flag9; }
qint16 DashBoard::Flag10() const { return m_Flag10; }
qint16 DashBoard::Flag11() const { return m_Flag11; }
qint16 DashBoard::Flag12() const { return m_Flag12; }
qint16 DashBoard::Flag13() const { return m_Flag13; }
qint16 DashBoard::Flag14() const { return m_Flag14; }
qint16 DashBoard::Flag15() const { return m_Flag15; }
qint16 DashBoard::Flag16() const { return m_Flag16; }


