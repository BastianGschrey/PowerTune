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

};
