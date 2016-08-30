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
    Q_PROPERTY(qint8 Leadingign READ Leadingign WRITE setLeadingign NOTIFY LeadingignChanged)
    Q_PROPERTY(qint8 Trailingign READ Trailingign WRITE setTrailingign NOTIFY TrailingignChanged)
    Q_PROPERTY(qint8 Fueltemp READ Fueltemp WRITE setFueltemp NOTIFY FueltempChanged)
    Q_PROPERTY(qint8 Moilp READ Moilp WRITE setMoilp NOTIFY MoilpChanged)
    Q_PROPERTY(qint8 Boosttp READ Boosttp WRITE setBoosttp NOTIFY BoosttpChanged)
    Q_PROPERTY(qint8 Boostwg READ Boostwg WRITE setBoostwg NOTIFY BoostwgChanged)
    Q_PROPERTY(qint8 Watertemp READ Watertemp WRITE setWatertemp NOTIFY WatertempChanged)
    Q_PROPERTY(qint8 Intaketemp READ Intaketemp WRITE setIntaketemp NOTIFY IntaketempChanged)
    Q_PROPERTY(qint8 Knock READ Knock WRITE setKnock NOTIFY KnockChanged)
    Q_PROPERTY(qint8 BatteryV READ BatteryV WRITE setBatteryV NOTIFY BatteryVChanged)
    Q_PROPERTY(qint16 speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(qint16 Iscvduty READ Iscvduty WRITE setIscvduty NOTIFY IscvdutyChanged)
    Q_PROPERTY(qint8 O2volt READ O2volt WRITE setO2volt NOTIFY O2voltChanged)
    Q_PROPERTY(qint8 na1 READ na1 WRITE setna1 NOTIFY na1Changed)
    Q_PROPERTY(qint16 Secinjpulse READ Secinjpulse WRITE setSecinjpulse NOTIFY SecinjpulseChanged)
    Q_PROPERTY(qint8 na2 READ Intaketemp WRITE setna2 NOTIFY na2Changed)




public:
    DashBoard(QObject *parent = 0);
    // Advanced Info FD3S
    void setRevs(const qint16 &revs);
    void setIntakepress(const qint16 &Intakepress);
    void setPressureV(const qint16 &PressureV);
    void setThrottleV(const qint16 &ThrottleV);
    void setPrimaryinp(const qint16 &Primaryinp);
    void setFuelc(const qint16 &Fuelc);
    void setLeadingign(const qint8 &Leadingign);
    void setTrailingign(const qint8 &Trailingign);
    void setFueltemp(const qint8 &Fueltemp);
    void setMoilp(const qint8 &Moilp);
    void setBoosttp(const qint8 &Boosttp);
    void setBoostwg(const qint8 &Boostwg);
    void setWatertemp(const qint8 &Watertemp);
    void setIntaketemp(const qint8 &Intaketemp);
    void setKnock(const qint8 &Knock);
    void setBatteryV(const qint8 &BatteryV);
    void setSpeed(const qint16 &speed);   
    void setIscvduty (const qint16 &Iscvduty );
    void setO2volt(const qint8 &O2volt);
    void setna1(const qint8 &na1);
    void setSecinjpulse(const qint16 &Secinjpulse);
    void setna2(const qint8 &na2);

    // Advanced Info FD3S
    qint16 revs() const;
    qint16 Intakepress() const;
    qint16 PressureV() const;
    qint16 ThrottleV() const;
    qint16 Primaryinp() const;
    qint16 Fuelc() const;
    qint8 Leadingign() const;
    qint8 Trailingign() const;
    qint8 Fueltemp() const;
    qint8 Moilp() const;
    qint8 Boosttp() const;
    qint8 Boostwg() const;
    qint8 Watertemp() const;
    qint8 Intaketemp() const;
    qint8 Knock() const;
    qint16 speed() const;
    qint8 BatteryV() const;
    qint16 Iscvduty() const;
    qint8 O2volt() const;
    qint8 na1() const;
    qint16 Secinjpulse() const;
    qint8 na2() const;

signals:

    // Advanced Info FD3S
    void revsChanged(qint16 revs);
    void IntakepressChanged(qint16 Intakepress);
    void PressureVChanged(qint16 PressureV);
    void ThrottleVChanged(qint16 ThrottleV);
    void PrimaryinpChanged(qint16 Primaryinp);
    void FuelcChanged(qint16 Fuelc);
    void LeadingignChanged(qint8 Leadingign);
    void TrailingignChanged(qint8 Trailingign);
    void FueltempChanged(qint8 Fueltemp);
    void MoilpChanged(qint8 Moilp);
    void BoosttpChanged(qint8 Boosttp);
    void BoostwgChanged(qint8 Boostwg);
    void WatertempChanged(qint8 Watertemp);
    void IntaketempChanged(qint8 Intaketemp);
    void KnockChanged(qint8 Knock);
    void speedChanged(qint16 speed);
    void BatteryVChanged(qint8 BatteryV);
    void IscvdutyChanged(qint16 Iscvduty);
    void O2voltChanged(qint8 O2volt);
    void na1Changed(qint8 na1);
    void SecinjpulseChanged(qint16 Secinjpulse);
    void na2Changed(qint8 na2);

private:
    // Advanced Info FD3S
    qint16 m_revs;
    qint16 m_Intakepress;
    qint16 m_PressureV;
    qint16 m_ThrottleV;
    qint16 m_Primaryinp;
    qint16 m_Fuelc;
    qint8 m_Leadingign;
    qint8 m_Trailingign;
    qint8 m_Fueltemp;
    qint8 m_Moilp;
    qint8 m_Boosttp;
    qint8 m_Boostwg;
    qint8 m_Watertemp;
    qint8 m_Intaketemp;
    qint8 m_Knock;
    qint16 m_speed;
    qint8 m_BatteryV;
    qint16 m_Iscvduty;
    qint8 m_O2volt;
    qint8 m_na1;
    qint16 m_Secinjpulse;
    qint8 m_na2;

};
