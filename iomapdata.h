#ifndef IOMAPDATA_H
#define IOMAPDATA_H

#include <QObject>
#include <QString>
#include <QList>
#include <QtPositioning>

class ioMapData:public QObject
{
    Q_OBJECT
public:
    explicit ioMapData(QObject *parent = 0);
    Q_INVOKABLE QGeoPath loadMapData(QString country, QString trackName);
    Q_INVOKABLE QGeoPath parseKML(QList<QString> list);
    Q_INVOKABLE QList<QString> getCountries();
    Q_INVOKABLE QList<QString> getTracks(QString country);
    Q_INVOKABLE int getTrackCount(QString country);
    Q_INVOKABLE int getCountryCount();
    Q_INVOKABLE QList<QString> getCenter(QString country, QString trackName);
    Q_INVOKABLE QList<QString> getStartFinishLine(QString country, QString trackName);
    Q_INVOKABLE QList<QString> getSecondFinishLine(QString country, QString trackName);
    Q_INVOKABLE qreal getZOOMLEVEL(QString country, QString trackName);
    Q_INVOKABLE bool getExistsSecondFinish(QString country, QString trackName);
    Q_INVOKABLE bool getTrackExists(QString country, QString trackName);


signals:

public slots:
};

#endif // IOMAPDATA_H
