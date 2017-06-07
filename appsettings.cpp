#include "appsettings.h"
#include <QSettings>
#include <QDebug>

AppSettings::AppSettings(QObject *parent) : QObject(parent)
{

}

int AppSettings::getBaudRate()
{
    return getValue("serial/baudrate").toInt();
}

void AppSettings::setBaudRate(const int &arg)
{
    setValue("serial/baudrate", arg);
}

int AppSettings::getParity()
{
    return getValue("serial/parity").toInt();
}

void AppSettings::setParity(const int &arg)
{
    setValue("serial/parity", arg);
}

int AppSettings::getDataBits()
{
    return getValue("serial/databits").toInt();
}

void AppSettings::setDataBits(const int &arg)
{
    setValue("serial/databits", arg);
}

int AppSettings::getStopBits()
{
    return getValue("serial/stopbits").toInt();
}

void AppSettings::setStopBits(const int &arg)
{
    setValue("serial/stopbits", arg);
}

int AppSettings::getFlowControl()
{
    return getValue("serial/flowcontrol").toInt();
}

void AppSettings::setFlowControl(const int &arg)
{
    setValue("serial/flowcontrol", arg);
}

int AppSettings::getECU()
{
    return getValue("serial/ECU").toInt();

}

void AppSettings::setECU(const int &arg)
{
    setValue("serial/ECU", arg);
}

int AppSettings::getInterface()
{
    return getValue("serial/Interface").toInt();

}

void AppSettings::setInterface(const int &arg)
{
    setValue("serial/Interface", arg);
}

int AppSettings::getLogging()
{
    return getValue("serial/Logging").toInt();

}

void AppSettings::setLogging(const int &arg)
{
    setValue("serial/Logging", arg);
}

void AppSettings::setValue(const QString &key, const QVariant &value)
{
    QSettings settings("PowerTuneQML", "PowerTuneQMLGUI", this);
    settings.setValue(key, value);
}

QVariant AppSettings::getValue(const QString &key)
{
    QSettings settings("PowerTuneQML", "PowerTuneQMLGUI", this);
    return settings.value(key);
}
