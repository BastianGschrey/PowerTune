#include "appsettings.h"
#include <QSettings>

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
