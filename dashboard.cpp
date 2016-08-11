#include <dashboard.h>

DashBoard::DashBoard(QObject *parent)
    : QObject(parent)
    , m_revs(10)
    , m_speed(220)
{
}

void DashBoard::setRevs(const qint16 &revs)
{
    if (m_revs == revs)
        return;
    m_revs = revs;
    emit revsChanged(revs);
}

void DashBoard::setSpeed(const qint16 &speed)
{
    if (m_speed == speed)
        return;
    m_speed = speed;
    emit speedChanged(speed);
}

qint16 DashBoard::revs() const { return m_revs; }
qint16 DashBoard::speed() const { return m_speed; }
