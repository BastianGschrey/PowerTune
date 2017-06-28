#ifndef GPS_H
#define GPS_H

#include <QByteArray>
#include <QDebug>
#include <QList>

class GPGGA {
public:
    float _utcTime; //hhmmss.ss
    float _latitude;
    float _longitude;
    int _quality; //0 = Invalid, 1 = GPS fix, 2 = DGPS fix
    int _satelites; //In view
    float _hdop; //Relative accuracy of horizontal position
    float _altitude; //Meters above mean sea level
    float _geoildalSeparation; //Height of geoid above WGS84 ellipsoid

    GPGGA();
};

class GPGSA {
public:
    char _modeType; //M = Manual, A = Automatic
    int _mode; //1 = Fix not available, 2 = 2D, 3 = 3D
    QList<int> *_satelites = NULL; //IDs of SVs used in position fix
    float _pdop;
    float _hdop;
    float _vdop;

    GPGSA();
};

class SATELITE {
public:
    int _id; //SV PRN number
    int _elevation; //In degrees, 90 maximum
    int _azimuth; //Degrees from true north, 000 to 359
    int _snr; //00-99 dB (null when not tracking)

    SATELITE();
};

class GPGSV {
public:
    QList<SATELITE> *_satelites = NULL;

    GPGSV();
};

class GPRMC {
public:
    float _utcTime; //Time Stamp
    char _validity; //A = ok, V = invalid
    float _latitude; //Current Latitude
    float _longitude; //Current Longitude
    float _speed; //Speed in Kilometers per hour
    float _course; //True course
    int _utDate; //Date Stamp

    GPRMC();
};

class GPS {
public:
    GPGGA *_gpgga = NULL;
    GPGSA *_gpgsa = NULL;
    GPGSV *_gpgsv = NULL;
    GPRMC *_gprmc = NULL;

    GPS();
    void parseGPS(QByteArray gpsPackage);
    GPGGA *parseGPGGA(QByteArray gpggaPackage);
    GPGSA *parseGPGSA(QByteArray gpgsaPackage);
    GPGSV *parseGPGSV(QByteArray gpgsvPackage);
    GPRMC *parseGPRMC(QByteArray gprmcPackage);

private:
    bool checkSum(QByteArray package, int checksum);
    QList<QByteArray> *splitPackage(QByteArray package, QString packageName);
};

#endif // GPS_H
