#include "Apexi.h"
#include "dashboard.h"
#include "connect.h"
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QBitArray>
#include <QByteArrayMatcher>
#include <QFile>
#include <QTextStream>



int units =0;// 0 Metric / 1 Imperial
QByteArray rawmessagedata;
QByteArray fullFuelBase;
qreal AN1AN2calc;
qreal AN3AN4calc;
qreal test;

//QBitArray flagArray;
QString Logfile;
QString Auxname1;
QString Auxname2;
qreal odometer;
int Model = 0;
int Logging =3;
int Loggerstat;
int auxval1;
int auxval2;
int auxval3;
int auxval4;
int requestIndex = 0; //ID for requested data type Power FC
int expectedbytes;
int Bytes;



double mul[80] = FC_INFO_MUL;  // required values for calculation from raw to readable values for Advanced Sensor info
double add[] = FC_INFO_ADD;

static QString mapFD3S[] ={"InjDuty", "IGL","IGT","Rpm","Speed","Boost","Knock","WtrTemp","AirTemp","BatVolt","PIM","VTA1","VTA2","VMOP","WTRT","AIRT","FUEL","O2S","STR","A/C","PWS","NTR","CLT","STP","CAT","ELD","HWL"};//	FPD	FPR	APR	PAC	CCN	TCN	PRC	AN1 raw	AN2 raw	AN3 raw	AN4 raw	AN1-AN2 Wide Band	AN2 raw	AN3 raw	AN4 raw	MAPN	MAPP	RPM	PIM	PIM V	TPS V	InjFrPr	Inj +/-	IGL	IGT	FuelT	Oil	PC%	WG%	WtrT	AirT	Knock	BatV	Speed	???(2)	O2S	???	InjFrSc
/*{"rpm", "pim", "pimV",
                        "TPS Voltage", "InjFp ms", "Inj",
                        "IGL", "IGT",
                        "Fuel", "Moilp", "Boosttp",
                        "Boostwg", "Watertemp", "Intaketemp",
                        "Knock", "BatteryV",
                        "Speed", "Iscvduty", "O2volt",
                        "na1", "Secinjpulse", "na2",
                        "AUX1", "AUX2", "AUX3", "AUX4",
                        "Analog1", "Analog2", "Analog3", "Analog4",
                        "Power", "Accel", "GForce", "ForceN", "Gear", "PrimaryInjD", "AccelTimer",
                        "Rec","Sens_PIM","Sens_VTA1","Sens_VTA2","Sens_VMOP","Sens_Wtrt","Sens_Airt",
                        "Sens_Fuel","Sens_O2", "STR", "A/C", "PWS", "NTR", "CLT",
                        "STP", "CAT", "ELD", "HWL", "FPD", "FPR", "APR", "PAC", "CCN", "TCN", "PRC" ,"MAP_N","MAP_P",
                        "Basic_Injduty", "Basic_IGL", "Basic_IGT", "Basic_RPM", "Basic_KPH", "Basic_Boost", "Basic_Knock", "Basic_Watert", "Basic_Airt", "Basic_BattV",};
*/
Apexi::Apexi(QObject *parent)
    : QObject(parent)
    , m_dashboard(Q_NULLPTR)
{
}

Apexi::Apexi(DashBoard *dashboard, QObject *parent)
    : QObject(parent)
    , m_dashboard(dashboard)
{
}

void Apexi::initSerialPort()
{
    if (m_serialport)
    {
        delete m_serialport;
    }
    m_serialport = new SerialPort(this);
    connect(this->m_serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));
    connect(m_serialport, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &Apexi::handleError);
    connect(m_serialport, &QSerialPort::bytesWritten, this, &Apexi::handleBytesWritten);
    connect(&m_timer, &QTimer::timeout, this, &Apexi::handleTimeout);
    m_readData.clear();



}

//function for flushing all serial buffers
void Apexi::clear()
{
    m_serialport->clear();
}


//function to open serial port
void Apexi::openConnection(const QString &portName)
{

    initSerialPort();
    m_serialport->setPortName(portName);
    m_serialport->setBaudRate(QSerialPort::Baud57600);
    m_serialport->setParity(QSerialPort::NoParity);
    m_serialport->setDataBits(QSerialPort::Data8);
    m_serialport->setStopBits(QSerialPort::OneStop);
    m_serialport->setFlowControl(QSerialPort::NoFlowControl);;

    if(m_serialport->open(QIODevice::ReadWrite) == false)
    {
        m_dashboard->setSerialStat(m_serialport->errorString());
        Apexi::closeConnection();
    }
    else
    {
        m_dashboard->setSerialStat(QString("Connected to Serialport"));
        requestIndex = 0;
        Apexi::sendRequest(requestIndex);
    }


}
void Apexi::closeConnection()
{
    disconnect(this->m_serialport,SIGNAL(readyRead()),this,SLOT(readyToRead()));
    disconnect(m_serialport, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &Apexi::handleError);
    disconnect(m_serialport, &QSerialPort::bytesWritten, this, &Apexi::handleBytesWritten);
    disconnect(&m_timer, &QTimer::timeout, this, &Apexi::handleTimeout);
    m_serialport->close();
}

void Apexi::handleTimeout()
{
    m_dashboard->setTimeoutStat(QString("Is Timeout : Y"));
    m_timer.stop();
    m_serialport->close();
    if(m_serialport->open(QIODevice::ReadWrite) == false)
    {
        m_dashboard->setSerialStat(m_serialport->errorString());
    }
    else
    {
        m_dashboard->setSerialStat(QString("Connected to Serialport"));
    }

    requestIndex = 0;
    m_readData.clear();

    Apexi::sendRequest(requestIndex);
}

void Apexi::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        QString fileName = "Errors.txt";
        QFile mFile(fileName);
        if(!mFile.open(QFile::Append | QFile::Text)){
        }
        QTextStream out(&mFile);
        out << "Serial Error " << (m_serialport->errorString()) <<endl;
        mFile.close();
        m_dashboard->setSerialStat(m_serialport->errorString());

    }
}



void Apexi::readyToRead()
{
    m_readData = m_serialport->readAll();

    m_dashboard->setRecvData(QString("Receive Data : " + m_readData.toHex()));
    Apexi::apexiECU(m_readData);
}



void Apexi::apexiECU(const QByteArray &buffer)
{

    m_buffer.append(buffer);
    QByteArray startpattern = m_writeData.left(1);
    QByteArrayMatcher startmatcher(startpattern);

    int pos = 0;
    while((pos = startmatcher.indexIn(m_buffer, pos)) != -1)
    {
        m_dashboard->setRunStat(m_buffer.toHex());
        if (pos !=0)
        {
            m_buffer.remove(0, pos);
            if (m_buffer.length() > expectedbytes)
            {
                m_buffer.remove(expectedbytes,m_buffer.length() );
            }
        }

        if (pos == 0 )
        {
            break;
        }


    }

    if (m_buffer.length() == expectedbytes)
    {
        m_dashboard->setTimeoutStat(QString("Is Timeout : N"));

        m_apexiMsg =  m_buffer;
        m_buffer.clear();
        m_timer.stop();
        if(requestIndex <= 5){requestIndex++;}
        else{requestIndex = 2;}
        readData(m_apexiMsg);
        m_apexiMsg.clear();
        Apexi::sendRequest(requestIndex);
        //        }
    }
}




void Apexi::readData(QByteArray rawmessagedata)
{

    if( rawmessagedata.length() )
    {
        //Power FC Decode
        quint8 requesttype = rawmessagedata[0];


        switch (requesttype) {
        case ID::Advance:
            Apexi::decodeAdv(rawmessagedata);
            break;
        case ID::SensorStrings:
            Apexi::decodeSensorStrings(rawmessagedata);
            break;
        case ID::SensorData:
            Apexi::decodeSensor(rawmessagedata);
            break;
        case ID::AuxData:
            Apexi::decodeAux(rawmessagedata);
            break;
        case ID::MapIndex:
            Apexi::decodeMap(rawmessagedata);
            break;
        case ID::BaiscData:
            Apexi::decodeBasic(rawmessagedata);
            break;
        case ID::Init:
            Apexi::decodeInit(rawmessagedata);
            break;
        case ID::Version:
            Apexi::decodeVersion(rawmessagedata);
            break;

        default:
            break;
        }



        /*
            if(requesttype == 0xB8){Apexi::decodeRevIdle(rawmessagedata);}
            if(requesttype == 0x7D){Apexi::decodeTurboTrans(rawmessagedata);}
            if(requesttype == 0x76){Apexi::decodeLeadIgn(rawmessagedata, 0);}
            if(requesttype == 0x77){Apexi::decodeLeadIgn(rawmessagedata, 5);}
            if(requesttype == 0x78){Apexi::decodeLeadIgn(rawmessagedata, 10);}
            if(requesttype == 0x79){Apexi::decodeLeadIgn(rawmessagedata, 15);}
            if(requesttype == 0x81){Apexi::decodeTrailIgn(rawmessagedata, 0);}
            if(requesttype == 0x82){Apexi::decodeTrailIgn(rawmessagedata, 5);}
            if(requesttype == 0x83){Apexi::decodeTrailIgn(rawmessagedata, 10);}
            if(requesttype == 0x84){Apexi::decodeTrailIgn(rawmessagedata, 15);}
            if(requesttype == 0x86){Apexi::decodeInjcorr(rawmessagedata, 0);}
            if(requesttype == 0x87){Apexi::decodeInjcorr(rawmessagedata, 5);}
            if(requesttype == 0x88){Apexi::decodeInjcorr(rawmessagedata, 10);}
            if(requesttype == 0x89){Apexi::decodeInjcorr(rawmessagedata, 15);}
            if(requesttype == 0xB0){Apexi::decodeFuelBase(rawmessagedata, 0);}
            if(requesttype == 0xB1){Apexi::decodeFuelBase(rawmessagedata, 1);}
            if(requesttype == 0xB2){Apexi::decodeFuelBase(rawmessagedata, 2);}
            if(requesttype == 0xB3){Apexi::decodeFuelBase(rawmessagedata, 3);}
            if(requesttype == 0xB4){Apexi::decodeFuelBase(rawmessagedata, 4);}
            if(requesttype == 0xB5){Apexi::decodeFuelBase(rawmessagedata, 5);}
            if(requesttype == 0xB6){Apexi::decodeFuelBase(rawmessagedata, 6);}
            if(requesttype == 0xB7){Apexi::decodeFuelBase(rawmessagedata, 7);}
            if(requesttype == 0xF5){Apexi::decodeVersion(rawmessagedata);}
            if(requesttype == 0xF3){Apexi::decodeInit(rawmessagedata);}
            if(requesttype == 0xAB){Apexi::decodeBoostCont(rawmessagedata);}
            if(requesttype == 0x7B){Apexi::decodeInjOverlap(rawmessagedata);}
            if(requesttype == 0x92){Apexi::decodeInjPriLagvsBattV(rawmessagedata);}
            if(requesttype == 0x9F){Apexi::decodeInjScLagvsBattV(rawmessagedata);}
            if(requesttype == 0x8D){Apexi::decodeFuelInjectors(rawmessagedata);}
            */
    }
    rawmessagedata.clear();


}

void Apexi::handleBytesWritten(qint64 bytes)
{
    m_bytesWritten += bytes;
    if (m_bytesWritten == m_writeData.size()) {
        m_bytesWritten = 0;
    }
}

// Serial requests are send via Serial
void Apexi::writeRequestPFC(QByteArray p_request)
{
    m_writeData = p_request;
    qint64 bytesWritten = m_serialport->write(p_request);
    m_dashboard->setSerialStat(QString("Sending Request " + p_request.toHex()));

    if (bytesWritten == -1) {
        m_dashboard->setSerialStat(m_serialport->errorString());
    } else if (bytesWritten != m_writeData.size()) {
        m_dashboard->setSerialStat(m_serialport->errorString());
    }

}

//Power FC requests

void Apexi::sendRequest(int requestIndex)
{
    switch (requestIndex){
    /*
    case 0:
        //First request from (this is what FC Edit does seems to get a 4 or 8 Byte response , not sure what this does)
        Apexi::writeRequestPFC(QByteArray::fromHex("0102FC"));
        if (interface ==0)
        {expectedbytes = 4;}
        if (interface ==1)
        {expectedbytes = 8;}
        break;
*/
    //case 1:
    case 0:
        //Init Platform (This returns the Platform String )
        Apexi::writeRequestPFC(QByteArray::fromHex("F3020A"));
        expectedbytes = 11;
        break;
        /*
    case 2:
        //Apexi::getWarConStrFlags();
        Apexi::writeRequestPFC(QByteArray::fromHex("D60227"));
        expectedbytes = 88;
        break;
    case 3:
        //Apexi::getVersion();
        Apexi::writeRequestPFC(QByteArray::fromHex("F50208"));
        expectedbytes = 8;
        break;
    case 4:
        //Apexi::getMapRef();
        Apexi::writeRequestPFC(QByteArray::fromHex("8A0273"));
        expectedbytes = 83;
        break;
    case 5:
        //Apexi::getRevIdle();
        Apexi::writeRequestPFC(QByteArray::fromHex("B80245"));
        expectedbytes = 17;
        break;
    case 6:
        //Apexi::getLeadign1();
        Apexi::writeRequestPFC(QByteArray::fromHex("760287"));
        expectedbytes = 103;
        break;
    case 7:
        //Apexi::getLeadign2();
        Apexi::writeRequestPFC(QByteArray::fromHex("770286"));
        expectedbytes = 103;
        break;
    case 8:
        //Apexi::getLeadign3();
        Apexi::writeRequestPFC(QByteArray::fromHex("780285"));
        expectedbytes = 103;
        break;
    case 9:
        //Apexi::getLeadign4();
        Apexi::writeRequestPFC(QByteArray::fromHex("790284"));
        expectedbytes= 103;
        break;
    case 10:
        //Apexi::getTrailIgn1();
        Apexi::writeRequestPFC(QByteArray::fromHex("81027C"));
        expectedbytes= 103;
        break;
    case 11:
        //Apexi::getTrailIgn2();
        Apexi::writeRequestPFC(QByteArray::fromHex("82027B"));
        expectedbytes= 103;
        break;
    case 12:
        //Apexi::getTrailIgn3();
        Apexi::writeRequestPFC(QByteArray::fromHex("83027A"));
        expectedbytes = 103;
        break;
    case 13:
        //Apexi::getTrailIgn4();
        Apexi::writeRequestPFC(QByteArray::fromHex("840279"));
        expectedbytes = 103;
        break;
    case 14:
        //Apexi::getPimStrInjA();
        Apexi::writeRequestPFC(QByteArray::fromHex("CB0232"));
        expectedbytes = 110;
        break;
    case 15:
        //Apexi::getInjOverlap();
        Apexi::writeRequestPFC(QByteArray::fromHex("7B0282"));
        expectedbytes = 9;
        break;
    case 16:
        //Apexi::getInjvsFuelT();
        Apexi::writeRequestPFC(QByteArray::fromHex("7C0281"));
        expectedbytes = 12;
        break;
    case 17:
        //Apexi::getTurboTrans();
        Apexi::writeRequestPFC(QByteArray::fromHex("7D0280"));
        expectedbytes = 12;
        break;
    case 18:
        //Apexi::getOilervsWaterT();
        Apexi::writeRequestPFC(QByteArray::fromHex("7E027F"));
        expectedbytes = 9;
        break;
    case 19:
        //Apexi::getFanvsWater();
        Apexi::writeRequestPFC(QByteArray::fromHex("7F027E"));
        expectedbytes = 6;
        break;
    case 20:
        //Apexi::getInjcorr1();
        Apexi::writeRequestPFC(QByteArray::fromHex("860277"));
        expectedbytes = 103;
        break;
    case 21:
        //Apexi::getInjcorr2();
        Apexi::writeRequestPFC(QByteArray::fromHex("870276"));
        expectedbytes = 103;
        break;
    case 22:
        //Apexi::getInjcorr3();
        Apexi::writeRequestPFC(QByteArray::fromHex("880275"));
        expectedbytes = 103;
        break;
    case 23:
        //Apexi::getInjcorr4();
        Apexi::writeRequestPFC(QByteArray::fromHex("890274"));
        expectedbytes = 103;
        break;
    case 24:
        //Apexi::getFuelInj();
        Apexi::writeRequestPFC(QByteArray::fromHex("8D0270"));
        expectedbytes = 27;
        break;
    case 25:
        //Apexi::getCranking();
        Apexi::writeRequestPFC(QByteArray::fromHex("8E026F"));
        expectedbytes = 15;
        break;
    case 26:
        //Apexi::getWaterTcorr();
        Apexi::writeRequestPFC(QByteArray::fromHex("8F026E"));
        expectedbytes = 17;
        break;
    case 27:
        //Apexi::getInjvsWaterBoost();
        Apexi::writeRequestPFC(QByteArray::fromHex("90026D"));
        expectedbytes = 9;
        break;
    case 28:
        //Apexi::getInjvsAirTBoost();
        Apexi::writeRequestPFC(QByteArray::fromHex("91026C"));
        expectedbytes = 11;
        break;
    case 29:
        //Apexi::getInjPrimaryLag();
        Apexi::writeRequestPFC(QByteArray::fromHex("92026B"));
        expectedbytes = 15;
        break;
    case 30:
        //Apexi::getAccInj();
        Apexi::writeRequestPFC(QByteArray::fromHex("93026A"));
        expectedbytes = 28;
        break;
    case 31:
        //Apexi::getInjvsAccel();
        Apexi::writeRequestPFC(QByteArray::fromHex("940269"));
        expectedbytes = 12;
        break;
    case 32:
        //Apexi::getIgnvsAircold();
        Apexi::writeRequestPFC(QByteArray::fromHex("960267"));
        expectedbytes = 7;
        break;
    case 33:
        //Apexi::getIgnvsWater();
        Apexi::writeRequestPFC(QByteArray::fromHex("980265"));
        expectedbytes = 7;
        break;
    case 34:
        //Apexi::getIgnvsAirwarm();
        Apexi::writeRequestPFC(QByteArray::fromHex("9A0263"));
        expectedbytes = 9;
        break;
    case 35:
        //Apexi::getLIgnvsRPM();
        Apexi::writeRequestPFC(QByteArray::fromHex("9B0262"));
        expectedbytes = 9;
        break;
    case 36:
        //Apexi::getIgnvsBatt();
        Apexi::writeRequestPFC(QByteArray::fromHex("9C0261"));
        expectedbytes = 9;
        break;
    case 37:
        //Apexi::getBoostvsIgn();
        Apexi::writeRequestPFC(QByteArray::fromHex("9D0260"));
        expectedbytes = 7;
        break;
    case 38:
        //Apexi::getTrailIgnvsRPM();
        Apexi::writeRequestPFC(QByteArray::fromHex("9E025F"));
        expectedbytes = 9;
        break;
    case 39:
        //Apexi::getInjSecLagvsBattV();
        Apexi::writeRequestPFC(QByteArray::fromHex("9F025E"));
        expectedbytes = 15;
        break;
    case 40:
        //Apexi::getKnockWarn();
        Apexi::writeRequestPFC(QByteArray::fromHex("A90254"));
        expectedbytes = 7;
        break;
    case 41:
        //Injejtor warning
        Apexi::writeRequestPFC(QByteArray::fromHex("A80255"));
        expectedbytes = 7;
        break;
    case 42:
        //Apexi::getO2Feedback();
        Apexi::writeRequestPFC(QByteArray::fromHex("AA0253"));
        expectedbytes = 6;
        break;
    case 43:
        //Apexi::getBoostcontrol();
        Apexi::writeRequestPFC(QByteArray::fromHex("AB0252"));
        expectedbytes = 14;
        break;
    case 44:
        //Apexi::getSettingProtections();
        Apexi::writeRequestPFC(QByteArray::fromHex("AC0251"));
        expectedbytes = 13;
        break;
    case 45:
        //Apexi::getTunerString();
        Apexi::writeRequestPFC(QByteArray::fromHex("AD0250"));
        expectedbytes = 11;
        break;
    case 46:
        //Apexi::getFuelBase0();
        Apexi::writeRequestPFC(QByteArray::fromHex("B0024D"));
        expectedbytes = 103;
        break;
    case 47:
        //Apexi::getFuelBase1();
        Apexi::writeRequestPFC(QByteArray::fromHex("B1024C"));
        expectedbytes = 103;
        break;
    case 48:
        //Apexi::getFuelBase2();
        Apexi::writeRequestPFC(QByteArray::fromHex("B2024B"));
        expectedbytes = 103;
        break;
    case 49:
        //Apexi::getFuelBase3();
        Apexi::writeRequestPFC(QByteArray::fromHex("B3024A"));
        expectedbytes = 103;
        break;
    case 50:
        //Apexi::getFuelBase4();
        Apexi::writeRequestPFC(QByteArray::fromHex("B40249"));
        expectedbytes = 103;
        break;
    case 51:
        //Apexi::getFuelBase5();
        Apexi::writeRequestPFC(QByteArray::fromHex("B50248"));
        expectedbytes = 103;
        break;
    case 52:
        //Apexi::getFuelBase6();
        Apexi::writeRequestPFC(QByteArray::fromHex("B60247"));
        expectedbytes = 103;
        break;
    case 53:
        //Apexi::getFuelBase7();
        Apexi::writeRequestPFC(QByteArray::fromHex("B70246"));
        expectedbytes = 103;
        break;
    case 54:
        //Apexi::getInjvsAirTemp();
        Apexi::writeRequestPFC(QByteArray::fromHex("B90244"));
        expectedbytes = 15;
        break;
    case 55:
        //Apexi::getInjvsTPS();
        Apexi::writeRequestPFC(QByteArray::fromHex("BB0242"));
        expectedbytes = 11;
        break;
    case 56:
        //Apexi::getPIMScaleOffset();
        Apexi::writeRequestPFC(QByteArray::fromHex("BC0241"));
        expectedbytes = 23;
        break;
    case 57:
        //Init Platform
        Apexi::writeRequestPFC(QByteArray::fromHex("F3020A"));
        expectedbytes = 11;
        break;
*/
        //case 58:
    case 1:
        //Apexi::getSensorStrings();
        Apexi::writeRequestPFC(QByteArray::fromHex("DD0220"));
        expectedbytes = 83;
        break;



        // Live Data
    case 2:
        //Apexi::getAdvData();
        Apexi::writeRequestPFC(QByteArray::fromHex("F0020D"));
        expectedbytes = 33;
        break;

    case 3:
        //Apexi::getMapIndices();
        Apexi::writeRequestPFC(QByteArray::fromHex("DB0222"));
        expectedbytes = 5;
        break;
    case 4:
        //Apexi::getSensorData();
        Apexi::writeRequestPFC(QByteArray::fromHex("DE021F"));
        expectedbytes = 21;
        break;
    case 5:
        //Apexi::getBasic();
        Apexi::writeRequestPFC(QByteArray::fromHex("DA0223"));
        expectedbytes = 23;
        break;
    case 6:
        //Apexi::getAux();
        Apexi::writeRequestPFC(QByteArray::fromHex("0002FD"));
        expectedbytes = 7;

        break;
    }

    m_timer.start(5000);
}




void Apexi::Auxcalc (const QString &unitaux1,const int &an1V0,const int &an2V5,const QString &unitaux2,const int &an3V0,const int &an4V5)
{
    int aux1min = an1V0;
    int aux2max = an2V5;
    int aux3min = an3V0;
    int aux4max = an4V5;
    QString Auxunit1 = unitaux1;
    QString Auxunit2 = unitaux2;

    Apexi::calculatorAux(aux1min,aux2max,aux3min,aux4max,Auxunit1,Auxunit2);
}


void Apexi::setUnits(const int &unitSelect)
{
    units = unitSelect;
    if (units == 0 )
    {m_dashboard->setunits("metric");}
    if (units == 1 )
    {m_dashboard->setunits("imperial");}
}


void Apexi::decodeAdv(QByteArray rawmessagedata)
{

    fc_adv_info_t* info=reinterpret_cast<fc_adv_info_t*>(rawmessagedata.data());
    if (Model == 1)
    {

        packageADV[0] = info->RPM + add[0];
        packageADV[1] = info->Intakepress;
        packageADV[2] = info->PressureV * 0.001; //value in V
        packageADV[3] = info->ThrottleV * 0.001; //value in V
        packageADV[4] = info->Primaryinp * 0.001;
        packageADV[5] = info->Fuelc;
        packageADV[6] = info->Leadingign -25;
        packageADV[7] = info->Trailingign -25;
        packageADV[8] = info->Fueltemp + add[8];
        packageADV[9] = info->Moilp;     //Value lower by 10 compared to FC Edit
        packageADV[10] = info->Boosttp / 2.56;    // (FC edit shows just raw value
        packageADV[11] = info->Boostwg / 2.56;     // (FC edit shows just raw value
        if (units == 0 )
        {
            packageADV[12] = info->Watertemp -80;
            packageADV[13] = info->Intaketemp -80;
        }
        if (units == 1 )
        {
            packageADV[12] = qRound(((info->Watertemp -80)* 1.8) + 32) ;
            packageADV[13] = qRound(((info->Intaketemp -80)* 1.8) + 32);
        }
        packageADV[14] = info->Knock;
        packageADV[15] = info->BatteryV * 0.1;
        if (units == 0 )
        {
            packageADV[16] = info->Speed ;
        }
        if (units == 1 )
        {
            packageADV[16] = qRound(info->Speed  * 0.621371);
        }
        packageADV[17] = info->Iscvduty * 0.001;
        packageADV[18] = info->O2volt;
        packageADV[19] = info->na1;
        packageADV[20] = info->Secinjpulse * 0.001;
        packageADV[21] = info->na2;

        m_dashboard->setRevs(packageADV[0]);
        m_dashboard->setIntakepress(packageADV[1]);
        m_dashboard->setPressureV(packageADV[2]);
        m_dashboard->setThrottleV(packageADV[3]);
        m_dashboard->setPrimaryinp(packageADV[4]);
        m_dashboard->setFuelc(packageADV[5]);
        m_dashboard->setLeadingign(packageADV[6]);
        m_dashboard->setTrailingign(packageADV[7]);
        m_dashboard->setFueltemp(packageADV[8]);
        m_dashboard->setMoilp(packageADV[9]);
        m_dashboard->setBoosttp(packageADV[10]);
        m_dashboard->setBoostwg(packageADV[11]);
        m_dashboard->setWatertemp(packageADV[12]);
        m_dashboard->setIntaketemp(packageADV[13]);
        m_dashboard->setKnock(packageADV[14]);
        m_dashboard->setBatteryV(packageADV[15]);
        m_dashboard->setSpeed(packageADV[16]);
        m_dashboard->setIscvduty(packageADV[17]);
        m_dashboard->setO2volt(packageADV[18]);
        m_dashboard->setna1(packageADV[19]);
        m_dashboard->setSecinjpulse(packageADV[20]);
        m_dashboard->setna2(packageADV[21]);


        //    //qDebug() << "Time passed since last call"<< startTime.msecsTo(QTime::currentTime());
        //odometer += ((startTime.msecsTo(QTime::currentTime())) * ((packageADV[16]) / 3600000)); // Odometer
        //m_dashboard->setOdo(odometer);
       // startTime.restart();


    }
    // Nissan and Subaru
    if (Model == 2)
    {
        fc_adv_info_t2* info=reinterpret_cast<fc_adv_info_t2*>(rawmessagedata.data());

        packageADV2[0] = info->RPM;
        packageADV2[1] = info->EngLoad;
        packageADV2[2] = info->MAF1V *0.001;
        packageADV2[3] = info->MAF2V *0.001;
        packageADV2[4] = info->injms *0.004;
        packageADV2[5] = info->Inj; //fc edit shows raw byte
        packageADV2[6] = info->Ign;
        packageADV2[7] = info->Dwell;
        packageADV2[8] = -760 + info->BoostPres;
        if (packageADV2[8] >= 0x8000)
            packageADV2[8] = (packageADV[8] - 0x8000) * 0.01;
        else
            packageADV2[8] = (1.0 / 2560 + 0.001) * packageADV[8];
        packageADV2[9] = info->BoostDuty *0.005;
        if (units == 0 )
        {
            packageADV2[10] = info->Watertemp -80;
            packageADV2[11] = info->Intaketemp -80;
        }
        if (units == 1 )
        {
            packageADV2[10] = qRound(((info->Watertemp -80)* 1.8) + 32);
            packageADV2[11] = qRound(((info->Intaketemp -80)* 1.8) + 32);

        }
        packageADV2[12] = info->Knock;
        packageADV2[13] = info->BatteryV *0.1;
        if (units == 0 )
        {
            packageADV2[14] = info->Speed;
        }
        if (units == 1 )
        {
            packageADV2[14] = qRound(info->Speed * 0.621371);
        }
        //    packageADV2[14] *= speed_correction;
        //    previousSpeed_kph[buf_currentIndex] = packageADV[14];
        packageADV2[15] = info->MAFactivity *0.16;
        packageADV2[16] = info->O2volt *0.005;
        packageADV2[17] = info->O2volt_2 *0.005;
        packageADV2[18] = info->ThrottleV *0.001;

        m_dashboard->setRevs(packageADV2[0]);
        m_dashboard->setEngLoad(packageADV2[1]);
        m_dashboard->setMAF1V(packageADV2[2]);
        m_dashboard->setMAF2V(packageADV2[3]);
        m_dashboard->setinjms(packageADV2[4]);
        m_dashboard->setInj(packageADV2[5]);
        m_dashboard->setIgn(packageADV2[6]);
        m_dashboard->setDwell(packageADV2[7]);
        m_dashboard->setBoostPres(packageADV2[8]);
        m_dashboard->setBoostDuty(packageADV2[9]);
        m_dashboard->setWatertemp(packageADV2[10]);
        m_dashboard->setIntaketemp(packageADV2[11]);
        m_dashboard->setKnock(packageADV2[12]);
        m_dashboard->setBatteryV(packageADV2[13]);
        m_dashboard->setSpeed(packageADV2[14]);
        m_dashboard->setMAFactivity(packageADV2[15]);
        m_dashboard->setO2volt(packageADV2[16]);
        m_dashboard->setO2volt_2(packageADV2[17]);
        m_dashboard->setThrottleV(packageADV2[18]);

    }
    //Toyota
    if (Model == 3)
    {
        fc_adv_info_t3* info=reinterpret_cast<fc_adv_info_t3*>(rawmessagedata.data());

        packageADV3[0] = mul[0] * info->RPM3 + add[0];
        //previousRev_rpm[buf_currentIndex] = packageADV[0];
        packageADV3[1] = info->Intakepress3;
        packageADV3[2] = info->PressureV3 * 0.001;
        packageADV3[3] = info->ThrottleV3 * 0.001;
        packageADV3[4] = info->Primaryinp3;
        packageADV3[5] = info->Fuelc3;
        packageADV3[6] = info->Ign3;
        packageADV3[7] = info->Dwell3;
        packageADV3[8] = -760 + info->BoostPres3;
        /*
        if (packageADV3[8] >= 0x8000)
            packageADV3[8] = (packageADV3[8] - 0x8000) * 0.01;
        else
            packageADV3[8] = (1.0 / 2560 + 0.001) * packageADV3[8];
*/
        packageADV3[9] = mul[9] * info->BoostDuty3 + add[9];
        if (units == 0 )
        {
            packageADV3[10] = info->Watertemp3 -80;
            packageADV3[11] = info->Intaketemp3 -80;
        }
        if (units == 1 )
        {
            packageADV3[10] = qRound(((info->Watertemp3 -80)* 1.8) + 32);
            packageADV3[11] = qRound(((info->Intaketemp3 -80)* 1.8) + 32);

        }
        packageADV3[12] = info->Knock3;
        packageADV3[13] = info->BatteryV3 *0.1;
        if (units == 0 )
        {
            packageADV3[14] = info->Speed3;
        }
        if (units == 1 )
        {
            packageADV3[14] = qRound(info->Speed3 * 0.621371);
        }
        // packageADV3[14] *= speed_correction;
        //previousSpeed_kph[buf_currentIndex] = packageADV[14];
        //        packageADV3[15] = mul[15] * info->Iscvduty + add[15];
        packageADV3[16] = mul[16] * info->O2volt3 + add[16];
        //        packageADV3[17] = mul[17] * info->SuctionAirTemp + add[17];
        //        packageADV3[18] = mul[18] * info->ThrottleV_2 + add[18];
        packageADV3[19] = mul[19] * info->na13 + add[19];
        packageADV3[20] = 0;
        packageADV3[21] = 0;


        m_dashboard->setRevs(packageADV3[0]);
        m_dashboard->setIntakepress(packageADV3[1]);
        m_dashboard->setPressureV(packageADV3[2]);
        m_dashboard->setThrottleV(packageADV3[3]);
        m_dashboard->setPrimaryinp(packageADV3[4]);
        m_dashboard->setFuelc(packageADV3[5]);
        m_dashboard->setLeadingign(packageADV3[6]);
        m_dashboard->setTrailingign(packageADV3[7]);
        m_dashboard->setpim(packageADV3[8]);
        m_dashboard->setWatertemp(packageADV3[10]);
        m_dashboard->setIntaketemp(packageADV3[11]);
        m_dashboard->setKnock(packageADV3[12]);
        m_dashboard->setBatteryV(packageADV3[13]);
        m_dashboard->setSpeed(packageADV3[14]);


    }

}



void Apexi::decodeSensor(QByteArray rawmessagedata)
{
    fc_sens_info_t* info=reinterpret_cast<fc_sens_info_t*>(rawmessagedata.data());

    packageSens[0] = info->sens1 * 0.01;
    packageSens[1] = info->sens2 * 0.01;
    packageSens[2] = info->sens3 * 0.01;
    packageSens[3] = info->sens4 * 0.01;
    packageSens[4] = info->sens5 * 0.01;
    packageSens[5] = info->sens6 * 0.01;
    packageSens[6] = info->sens7 * 0.01;
    packageSens[7] = info->sens8 * 0.01;

    QBitArray flagArray(16);
    for (int i=0; i<16; i++)
        flagArray.setBit(i, info->flags>>i & 1);


    m_dashboard->setsens1(packageSens[0]);
    m_dashboard->setsens2(packageSens[1]);
    m_dashboard->setsens3(packageSens[2]);
    m_dashboard->setsens4(packageSens[3]);
    m_dashboard->setsens5(packageSens[4]);
    m_dashboard->setsens6(packageSens[5]);
    m_dashboard->setsens7(packageSens[6]);
    m_dashboard->setsens8(packageSens[7]);

    //Bit Flags for Sensors
    m_dashboard->setFlag1(flagArray[0]);
    m_dashboard->setFlag2(flagArray[1]);
    m_dashboard->setFlag3(flagArray[2]);
    m_dashboard->setFlag4(flagArray[3]);
    m_dashboard->setFlag5(flagArray[4]);
    m_dashboard->setFlag6(flagArray[5]);
    m_dashboard->setFlag7(flagArray[6]);
    m_dashboard->setFlag8(flagArray[7]);
    m_dashboard->setFlag9(flagArray[8]);
    m_dashboard->setFlag10(flagArray[9]);
    m_dashboard->setFlag11(flagArray[10]);
    m_dashboard->setFlag12(flagArray[11]);
    m_dashboard->setFlag13(flagArray[12]);
    m_dashboard->setFlag14(flagArray[13]);
    m_dashboard->setFlag15(flagArray[14]);
    m_dashboard->setFlag16(flagArray[15]);


}

void Apexi::decodeAux(QByteArray rawmessagedata)
{
    fc_aux_info_t* info=reinterpret_cast<fc_aux_info_t*>(rawmessagedata.data());


    packageAux[0] = mul[29] * info->AN1 + add[29];
    packageAux[1] = mul[30] * info->AN2 + add[30];
    packageAux[2] = mul[31] * info->AN3 + add[31];
    packageAux[3] = mul[32] * info->AN4 + add[32];

    //Analog1
    AN1AN2calc = ((((auxval2-auxval1)/5) * (packageAux[0] - packageAux[1])) + auxval1);
    AN3AN4calc = ((((auxval4-auxval3)/5) * (packageAux[2] - packageAux[3])) + auxval3);
    m_dashboard->setauxcalc1(AN1AN2calc);
    //Analog2
    m_dashboard->setauxcalc2(AN3AN4calc);

}


void Apexi::decodeMap(QByteArray rawmessagedata)
{
    fc_map_info_t* info=reinterpret_cast<fc_map_info_t*>(rawmessagedata.data());

    packageMap[0] = mul[0] * info->Map_N + add[0];
    packageMap[1] = mul[0] * info->Map_P + add[0];

    //    ui->txtMapConsole->clear();

    //    ui->txtMapConsole->append(map[66] + " " + QString::number(packageMap[0]));
    //    ui->txtMapConsole->append(map[67] + " " + QString::number(packageMap[1]));
}
void Apexi::decodeBasic(QByteArray rawmessagedata)
{
    fc_Basic_info_t* info=reinterpret_cast<fc_Basic_info_t*>(rawmessagedata.data());

    int Boost;

    packageBasic[0] = mul[15] * info->Basic_Injduty + add[0];
    packageBasic[1] = mul[0] * info->Basic_IGL + add[6];
    packageBasic[2] = mul[0] * info->Basic_IGT + add[6];
    packageBasic[3] = mul[0] * info->Basic_RPM + add[0];
    if (units == 0)
    {
        packageBasic[4] = mul[0] * info->Basic_KPH + add[0];
    }
    if (units == 1)
    {
        packageBasic[4] = (mul[0] * info->Basic_KPH + add[0]) * 0.621371;
    }
    packageBasic[5] = mul[0] * info->Basic_Boost -760;
    packageBasic[6] = mul[0] * info->Basic_Knock + add[0];
    if (units == 0)
    {
        packageBasic[7] = mul[0] * info->Basic_Watert + add[8];
    }
    if (units == 1)
    {
        packageBasic[7] = qRound(((mul[0] * info->Basic_Watert + add[8])*1.8) + 32) ;
    }
    if (units == 0)
    {
        packageBasic[8] = mul[0] * info->Basic_Airt + add[8];
    }
    if (units == 1)
    {
        packageBasic[8] = qRound(((mul[0] * info->Basic_Airt + add[8]) *1.8) + 32) ;
    }
    packageBasic[9] = mul[15] * info->Basic_BattV + add[0];
    if (units == 0)
    {
        if (packageBasic[5] >= 0) // while boost pressure is positive multiply by 0.01 to show kg/cm2
        {
            Boost = packageBasic[5] *0.01;
        }
        else Boost = packageBasic[5]; // while boost pressure is negative show pressure in mmhg
    }
    if (units == 1)
    {
        if (packageBasic[5] >= 0) // while boost pressure is positive multiply by 0.01 to show PSI
        {
            Boost = packageBasic[5] * 0.142233;
        }
        else Boost = packageBasic[5] * 0.039370079; // while boost pressure is negative show pressure in inhg
    }



    // m_dashboard->setInjDuty(packageBasic[0]);
    m_dashboard->setLeadingign(packageBasic[1]);
    m_dashboard->setTrailingign(packageBasic[2]);
    m_dashboard->setRevs(packageBasic[3]);
    m_dashboard->setSpeed(packageBasic[4]);
    m_dashboard->setpim(Boost);
    m_dashboard->setKnock(packageBasic[6]);
    m_dashboard->setWatertemp(packageBasic[7]);
    m_dashboard->setIntaketemp(packageBasic[8]);
    m_dashboard->setBatteryV(packageBasic[9]);

}
/*
void Apexi::ApexievIdle(QByteArray rawmessagedata)
{
    fc_RevIdle_info_t* info=reinterpret_cast<fc_RevIdle_info_t*>(rawmessagedata.data());

    packageRevIdle[0] = info->RevLIM;
    packageRevIdle[1] = info->FCAE;
    packageRevIdle[2] = info->FCEL;
    packageRevIdle[3] = info->FCAC;
    packageRevIdle[4] = info->IdleAE;
    packageRevIdle[5] = info->IdleEL;
    packageRevIdle[6] = info->IdleAC;

}

void Apexi::decodeTurboTrans(QByteArray rawmessagedata)
{
    fc_TurboTrans_info_t* info=reinterpret_cast<fc_TurboTrans_info_t*>(rawmessagedata.data());

    packageTurboTrans[0] = mul[35] * info->TPS01;
    packageTurboTrans[1] = mul[35] * info->TPS02;
    packageTurboTrans[2] = mul[35] * info->TPS03;
    packageTurboTrans[3] = mul[36] * info->LowRPM1;
    packageTurboTrans[4] = mul[36] * info->LowRPM2;
    packageTurboTrans[5] = mul[36] * info->LowRPM3;
    packageTurboTrans[6] = mul[36] * info->HighRPM1;
    packageTurboTrans[7] = mul[36] * info->HighRPM2;
    packageTurboTrans[8] = mul[36] * info->HighRPM3;

}

void Apexi::decodeLeadIgn(QByteArray rawmessagedata, quint8 column)
{
    //Fill Table view with Leading ignition Table1


    quint8 columnLimit = column + 5;
    quint8 countarray = 1; //counter for the position in the array
    for (column; column < columnLimit; column++) //increases the counter column by 1 until column 5
    {

        for (int row = 0; row < 20 ; row++)// counter to increase row up to 20 then set counter to 0 for next column
        {
            if(countarray <= 102){countarray++;} //Increases the counter "countarray till 100"
            //                    QStandardItem *value = new QStandardItem(QString::number(rawmessagedata[countarray]-25)); //insert the array here and use count array for position in array
            //                    model->setItem(row,column,value);
            //                    ui->tableLeadIgn->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            //                    ui->tableLeadIgn->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            //                    ui->tableLeadIgn->setModel(model);
        }
    }

}


//Trailing Ignition Map

void Apexi::decodeTrailIgn(QByteArray rawmessagedata, quint8 column)
{
    //Fill Table view with Trailing ignition Table1

    quint8 columnLimit = column + 5;
    quint8 countarray = 1; //counter for the position in the array
    for (column; column < columnLimit; column++) //increases the counter column by 1 until column 5
    {
        for (quint8 row = 0; row < 20 ; row++)// counter to increase row up to 20 then set counter to 0 for next column
        {
            if(countarray <= 102){countarray++;} //Increases the counter "countarray till 100"
            //                    QStandardItem *value = new QStandardItem(QString::number(rawmessagedata[countarray]-25)); //insert the array here and use count array for position in array
            //                    model1->setItem(row,column,value);
            //                    ui->tableTrailIgn->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            //                    ui->tableTrailIgn->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            //                    ui->tableTrailIgn->setModel(model1);
        }
    }

}
*/

//Injector correction
/*
void Apexi::decodeInjcorr(QByteArray rawmessagedata, quint8 column)
{
    //Fill Table view with Injector correction Table1
     quint8 columnLimit = column + 5;

    quint8 countarray = 1; //counter for the position in the array
    for (column; column < columnLimit; column++) //increases the counter column by 1 until column 5
    {
        for (quint8 row = 0; row < 20 ; row++)// counter to increase row up to 20 then set counter to 0 for next column
        {
            if(countarray <= 102){countarray++;} //Increases the counter "countarray till 100"
            //                    QStandardItem *value = new QStandardItem(QString::number((rawmessagedata[countarray]-128)*mul[40])); //insert the array here and use count array for position in array
            //                    model2->setItem(row,column,value);
            //                    ui->tableInjCorr->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            //                    ui->tableInjCorr->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            //                    ui->tableInjCorr->setModel(model2);
        }
    }

}
*/
/*
void Apexi::decodeFuelBase(QByteArray rawmessagedata, quint8 package)
{
    quint8 index = 0;
    ////qDebug() << "add package!";

    for(quint8 index = 2; index < 102; index++)
    {
        fullFuelBase.append(rawmessagedata[index]);
    }

    if(package == 7)
    {
        fc_fullFuelBase_info_t* info=reinterpret_cast<fc_fullFuelBase_info_t*>(fullFuelBase.data());

        for (quint8 column = 0; column <= 20; column++) //increases the counter column by 1 until column 5
        {
            for (quint8 row = 0; row < 20 ; row++)// counter to increase row up to 20 then set counter to 0 for next column
            {
//                ui->tableFuelBase->setItem(row, column, new QTableWidgetItem(QString::number(info->fuelBase[index])));
                index++;
               // //qDebug() << row << " : " << column;
            }
        }

    }
}

void Apexi::decodeBoostCont(QByteArray rawmessagedata)
{
    fc_BoostCont_info_t* info=reinterpret_cast<fc_BoostCont_info_t*>(rawmessagedata.data());

    packageBoostControl[0] = info->Setting1;
    packageBoostControl[1] = info->Setting2;
    packageBoostControl[2] = info->Setting3;
    packageBoostControl[3] = mul[37] * info->BoostPrimary1;
    packageBoostControl[4] = mul[37] * info->BoostSecondary1;
    packageBoostControl[5] = mul[37] * info->BoostPrimary2;
    packageBoostControl[6] = mul[37] * info->BoostSecondary2;
    packageBoostControl[7] = info->DutyPrimary1;
    packageBoostControl[8] = info->DutySecondary1;
    packageBoostControl[9] = info->DutyPrimary2;
    packageBoostControl[10] = info->DutySecondary2;

//    ui->lineBoostPri1->setText (QString::number(packageBoostControl[3]));
//    ui->lineBoostSec1->setText (QString::number(packageBoostControl[4]));
//    ui->lineBoostPri2->setText (QString::number(packageBoostControl[5]));
//    ui->lineBoostSec2->setText (QString::number(packageBoostControl[6]));
//    ui->lineBoostDutyPri1->setText (QString::number(packageBoostControl[7]));
//    ui->lineBoostDutySec1->setText (QString::number(packageBoostControl[8]));
//    ui->lineBoostDutyPri2->setText (QString::number(packageBoostControl[9]));
//    ui->lineBoostDutySec2->setText (QString::number(packageBoostControl[10]));

}
void Apexi::decodeInjOverlap(QByteArray rawmessagedata)
{
    fc_InjOverlap_info_t* info=reinterpret_cast<fc_InjOverlap_info_t*>(rawmessagedata.data());

    packageInjOverlap[0] = mul[39] * info->InjOvBoost1;
    packageInjOverlap[1] = info->lineInjOvSet1;
    packageInjOverlap[2] = mul[39] * info->InjOvBoost2;
    packageInjOverlap[3] = info->lineInjOvSet2;
    packageInjOverlap[4] = mul[39] * info->InjOvBoost3;
    packageInjOverlap[5] = info->lineInjOvSet3;


//    ui->lineInjOvBoost1->setText (QString::number(packageInjOverlap[0]));
//    ui->lineInjOvSet1->setText (QString::number(packageInjOverlap[1]));
//    ui->lineInjOvBoost2->setText (QString::number(packageInjOverlap[2]));
//    ui->lineInjOvSet2->setText (QString::number(packageInjOverlap[3]));
//    ui->lineInjOvBoost3->setText (QString::number(packageInjOverlap[4]));
//    ui->lineInjOvSet3->setText (QString::number(packageInjOverlap[5]));


}
*/
void Apexi::decodeVersion(QByteArray rawmessagedata)
{
    //    ui->lineVersion->setText (QString(rawmessagedata).mid(2,5));
}
void Apexi::decodeInit(QByteArray rawmessagedata)
{
    QString Modelname = QString(rawmessagedata).mid(2,8);
    //Mazda
    if (Modelname == "13B-REW ")
    {
        Model =1;
    }

    //Nissan
    if (Modelname == "RB20DET " || Modelname == "RB26DETT" || Modelname == "SR20DET1" || Modelname == "SR20DET2"  || Modelname == "CA18DET " || Modelname == "RB25DET ")
    {
        Model =2;
    }

    //Toyota
    if (Modelname == "4E-FTE2 " || Modelname == "1JZ-GTE "||Modelname == "1JZ-GTE3"|| Modelname == "1ZZ-FRE " || Modelname == "2jZ-GTE1" || Modelname == "2ZZ-GE  " || Modelname == "3S-GE   " || Modelname == "3S-GTE3 " || Modelname == " 3S-GTE " || Modelname == "3E-FTE2 ")
    {
        Model =3;
    }


    //Subaru
    if (Modelname == "EJ20K   " || Modelname == "EJ207   " )
    {
        Model =2;
    }
    //Honda
    if (Modelname == "B16B    " || Modelname == "B18C    " )
    {
        Model =2;
    }
    //Mitsubishi
    if (Modelname == "4G63    ")
    {
        Model =3;
    }

    m_dashboard->setPlatform(QString(rawmessagedata).mid(2,8));
}

void Apexi::decodeSensorStrings(QByteArray rawmessagedata)
{

    m_dashboard->setSensorString1 (QString(rawmessagedata).mid(2,4));
    m_dashboard->setSensorString2 (QString(rawmessagedata).mid(6,4));
    m_dashboard->setSensorString3 (QString(rawmessagedata).mid(10,4));
    m_dashboard->setSensorString4 (QString(rawmessagedata).mid(14,4));
    m_dashboard->setSensorString5 (QString(rawmessagedata).mid(18,4));
    m_dashboard->setSensorString6 (QString(rawmessagedata).mid(22,4));
    m_dashboard->setSensorString7 (QString(rawmessagedata).mid(26,4));
    m_dashboard->setSensorString8 (QString(rawmessagedata).mid(30,4));


    m_dashboard->setFlagString1 (QString(rawmessagedata).mid(34,3));
    m_dashboard->setFlagString2 (QString(rawmessagedata).mid(37,3));
    m_dashboard->setFlagString3 (QString(rawmessagedata).mid(40,3));
    m_dashboard->setFlagString4 (QString(rawmessagedata).mid(43,3));
    m_dashboard->setFlagString5 (QString(rawmessagedata).mid(46,3));
    m_dashboard->setFlagString6 (QString(rawmessagedata).mid(49,3));
    m_dashboard->setFlagString7 (QString(rawmessagedata).mid(52,3));
    m_dashboard->setFlagString8 (QString(rawmessagedata).mid(55,3));
    m_dashboard->setFlagString9 (QString(rawmessagedata).mid(58,3));
    m_dashboard->setFlagString10 (QString(rawmessagedata).mid(61,3));
    m_dashboard->setFlagString11 (QString(rawmessagedata).mid(64,3));
    m_dashboard->setFlagString12 (QString(rawmessagedata).mid(67,3));
    m_dashboard->setFlagString13 (QString(rawmessagedata).mid(70,3));
    m_dashboard->setFlagString14 (QString(rawmessagedata).mid(73,3));
    m_dashboard->setFlagString15 (QString(rawmessagedata).mid(76,3));
    m_dashboard->setFlagString16 (QString(rawmessagedata).mid(79,3));
}

/*
void Apexi::decodeInjPriLagvsBattV(QByteArray rawmessagedata)
{
    fc_InjPriLagvsBattV_info_t* info=reinterpret_cast<fc_InjPriLagvsBattV_info_t*>(rawmessagedata.data());

    packageInjPriLagvsBattV[0] = mul[38] * info->InjPriLag16V;
    packageInjPriLagvsBattV[1] = mul[38] * info->InjPriLag14V;
    packageInjPriLagvsBattV[2] = mul[38] * info->InjPriLag12V;
    packageInjPriLagvsBattV[3] = mul[38] * info->InjPriLag10V;
    packageInjPriLagvsBattV[4] = mul[38] * info->InjPriLag8V;
    packageInjPriLagvsBattV[5] = mul[38] * info->InjPriLag6V;

    //    ui->lineInjPrLag16V->setText (QString::number(packageInjPriLagvsBattV[0]));
    //    ui->lineInjPrLag14V->setText (QString::number(packageInjPriLagvsBattV[1]));
    //    ui->lineInjPrLag12V->setText (QString::number(packageInjPriLagvsBattV[2]));
    //    ui->lineInjPrLag10V->setText (QString::number(packageInjPriLagvsBattV[3]));
//    ui->lineInjPrLag8V->setText (QString::number(packageInjPriLagvsBattV[4]));
//    ui->lineInjPrLag6V->setText (QString::number(packageInjPriLagvsBattV[5]));
}
void Apexi::decodeInjScLagvsBattV(QByteArray rawmessagedata)
{
    fc_InjScLagvsBattV_info_t* info=reinterpret_cast<fc_InjScLagvsBattV_info_t*>(rawmessagedata.data());

    packageInjScLagvsBattV[0] = mul[38] * info->InjScLag16V;
    packageInjScLagvsBattV[1] = mul[38] * info->InjScLag14V;
    packageInjScLagvsBattV[2] = mul[38] * info->InjScLag12V;
    packageInjScLagvsBattV[3] = mul[38] * info->InjScLag10V;
    packageInjScLagvsBattV[4] = mul[38] * info->InjScLag8V;
    packageInjScLagvsBattV[5] = mul[38] * info->InjScLag6V;

//    ui->lineInjScLag16V->setText (QString::number(packageInjScLagvsBattV[0]));
//    ui->lineInjScLag14V->setText (QString::number(packageInjScLagvsBattV[1]));
//    ui->lineInjScLag12V->setText (QString::number(packageInjScLagvsBattV[2]));
//    ui->lineInjScLag10V->setText (QString::number(packageInjScLagvsBattV[3]));
//    ui->lineInjScLag8V->setText (QString::number(packageInjScLagvsBattV[4]));
//    ui->lineInjScLag6V->setText (QString::number(packageInjScLagvsBattV[5]));
}
void Apexi::decodeFuelInjectors(QByteArray rawmessagedata)
{
    fc_FuelInjectors_info_t* info=reinterpret_cast<fc_FuelInjectors_info_t*>(rawmessagedata.data());

    packageFuelInjectors[1] = mul[41] * info->frontpulse * mul[42];
    packageFuelInjectors[3] = mul[41] * info->rearpulse * mul[42];
    packageFuelInjectors[4] = 4 * info->frntprilag;//(multiply by 0.004)
    packageFuelInjectors[6] = 4 * info->frntseclag;//(multiply by 0.004)
    packageFuelInjectors[8] = 4 *info->rearprilag;//(multiply by 0.004)
    packageFuelInjectors[10] = 4 *info->rearseclag;//(multiply by 0.004)
    packageFuelInjectors[12] = info->prinjsize;
    packageFuelInjectors[13] = info->secinjsize;
    packageFuelInjectors[14] = info->prisectransprc /10; // divide by 10 to get %
    packageFuelInjectors[15] = info->prisectransms /10; //(multiply by 0.004)


//    ui->linefrontpulse->setText (QString::number(packageFuelInjectors[1]));
//    ui->linerearpulse->setText (QString::number(packageFuelInjectors[3]));
//    ui->linefrntprilag->setText (QString::number(packageFuelInjectors[4]));
//    ui->linefrntseclag->setText (QString::number(packageFuelInjectors[6]));
//    ui->linerearprilag->setText (QString::number(packageFuelInjectors[8]));
//    ui->linerearseclag->setText (QString::number(packageFuelInjectors[10]));
//    ui->linePriInjSize->setText (QString::number(packageFuelInjectors[12]));
//    ui->lineSecInjSize->setText (QString::number(packageFuelInjectors[13]));
//    ui->linePriSecTransPrc->setText (QString::number(packageFuelInjectors[14]));
//    ui->linePriSecTransms->setText (QString::number(packageFuelInjectors[15]));
}
*/



void Apexi::calculatorAux(int aux1min,int aux2max,int aux3min,int aux4max,QString Auxunit1,QString Auxunit2)
{
    auxval1 = aux1min;
    auxval2 = aux2max;
    auxval3 = aux3min;
    auxval4 = aux4max;

    Auxname1 = Auxunit1;
    Auxname2 = Auxunit2;



}
