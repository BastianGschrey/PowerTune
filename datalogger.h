#ifndef DATALOGGER_H
#define DATALOGGER_H
#include <QThread>
#include <QObject>

    class datalogger;
    class DashBoard;

    class datalogger : public QObject
    {
        Q_OBJECT


    public:


        explicit datalogger(QObject *parent = 0);
        explicit datalogger(DashBoard *dashboard, QObject *parent = 0);
        Q_INVOKABLE void startLog(QString Logfilename);


    public slots:

    void updateLog(QString Logfilename);
    void createHeader(QString Logfilename);

    private:
        DashBoard *m_dashboard;
};

#endif // DATALOGGER_H
