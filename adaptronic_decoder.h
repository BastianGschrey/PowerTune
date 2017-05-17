#ifndef ADAPTRONIC_DECODER_H
#define ADAPTRONIC_DECODER_H

#include <QObject>

class adaptronic_decoder : public QObject
{
    Q_OBJECT

public:
    adaptronic_decoder();

    double adaptronicPackage[20];

    struct adaptronic_stream_1{

        quint16 RPM;
        quint16 MAP;
        quint16 MAT;
        quint16 WT;
        quint16 AuxT;
        quint16 AFR;
        quint16 Knock;
        quint16 TPS;
        quint16 IdleDC;
        quint16 BatV;
        quint16 MasterVSS;
        quint16 SlaveVSS;
        quint16 InjectorPW1;
        quint16 InjectorPW2;
        quint16 InjectorPW3;
        quint16 InjectorPW4;
        quint16 IgnitionTiming1;
        quint16 IgnitionTiming2;
        quint16 IgnitionTiming3;
        quint16 IgnitionTiming4;
        quint16 FuelTrim;
        adaptronic_stream_1 parse(const QByteArray &);
    };




public slots:



};


#endif // ADAPTRONIC_DECODER_H
