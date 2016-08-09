#include <dashboard.h>

DashBoard::DashBoard(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
}

void DashBoard::setRevs(const qint16 &revs)
{
    m_revs = revs;
}

void DashBoard::setSpeed(const qint16 &speed)
{
    m_speed = speed;
}

qint16 DashBoard::revs() const
{
    return m_revs;
}

qint16 DashBoard::speed() const
{
    return m_speed;
}
