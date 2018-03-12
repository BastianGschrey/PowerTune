#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#include <QThread>
#include <QObject>
#include <QTime>
#include <QTimer>

class DashBoard;

class calculations : public QObject
{
    Q_OBJECT


public:


    explicit calculations(QObject *parent = 0);
    explicit calculations(DashBoard *dashboard, QObject *parent = 0);

public slots:

//void updateLog();
//void createHeader();

private:
    DashBoard *m_dashboard;
    QTimer      m_updatetimer;
};



#endif // CALCULATIONS_H
