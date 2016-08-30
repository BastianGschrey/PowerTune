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





