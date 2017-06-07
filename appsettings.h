#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QObject>

class AppSettings : public QObject
{
    Q_OBJECT
public:
    explicit AppSettings(QObject *parent = 0);

    Q_INVOKABLE int getBaudRate();
    Q_INVOKABLE void setBaudRate(const int &arg);

    Q_INVOKABLE int getParity();
    Q_INVOKABLE void setParity(const int &arg);

    Q_INVOKABLE int getDataBits();
    Q_INVOKABLE void setDataBits(const int &arg);

    Q_INVOKABLE int getStopBits();
    Q_INVOKABLE void setStopBits(const int &arg);

    Q_INVOKABLE int getFlowControl();
    Q_INVOKABLE void setFlowControl(const int &arg);

    Q_INVOKABLE int getECU();
    Q_INVOKABLE void setECU(const int &arg);

    Q_INVOKABLE int getInterface();
    Q_INVOKABLE void setInterface(const int &arg);

    Q_INVOKABLE int getLogging();
    Q_INVOKABLE void setLogging(const int &arg);



private:
    void setValue(const QString &key, const QVariant &value);
    QVariant getValue(const QString &key);
};

#endif // APPSETTINGS_H
