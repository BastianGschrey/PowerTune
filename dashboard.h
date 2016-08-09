#ifndef DASHBOARD_H
#define DASHBOARD_H

#endif // DASHBOARD_H

#include <QtQuick/QQuickPaintedItem>

class DashBoard : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(qint16 revs READ revs WRITE setRevs)
    Q_PROPERTY(qint16 speed READ speed WRITE setSpeed)

public:
    DashBoard(QQuickItem *parent = 0);

    void setRevs(const qint16 &revs);
    void setSpeed(const qint16 &speed);

    qint16 revs() const;
    qint16 speed() const;

    void painter(QPainter *painter);

private:
    qint16 m_revs;
    qint16 m_speed;
};
