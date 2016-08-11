#ifndef DASHBOARD_H
#define DASHBOARD_H

#endif // DASHBOARD_H

#include <QObject>

class DashBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint16 revs READ revs WRITE setRevs NOTIFY revsChanged)
    Q_PROPERTY(qint16 speed READ speed WRITE setSpeed NOTIFY speedChanged)

public:
    DashBoard(QObject *parent = 0);

    void setRevs(const qint16 &revs);
    void setSpeed(const qint16 &speed);

    qint16 revs() const;
    qint16 speed() const;

signals:
    void revsChanged(qint16 revs);
    void speedChanged(qint16 speed);

private:
    qint16 m_revs;
    qint16 m_speed;
};
