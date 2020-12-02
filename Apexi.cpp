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



QByteArray rawmessagedata;
QByteArray fullFuelBase;
qreal AN1AN2calc;
qreal AN3AN4calc;
qreal test;
qreal kpaboost;
int reconnect = 0;
QString port;
//QBitArray flagArray;
QString Logfile;
QString Auxname1;
QString Auxname2;
QString Modelname;
int Model = 0;
int Logging =3;
int Loggerstat;

float auxval1; // an1-2 v0
float auxval2; // an1-2 v5
float auxval3; // an3-4 v0
float auxval4; // an3-4 v5

int requestIndex = 0; //ID for requested data type Power FC
int expectedbytes;
int Bytes;
int Protocol = 0;
qreal advboost;


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

void Apexi::SetProtocol(const int &protocolselect)
{
    Protocol = protocolselect;
}

void Apexi::initSerialPort()
{
  /*
    if (m_serialport)
    {
        delete m_serialport;
    }
  */
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
    qDebug()<<"open Apexi";
    port = portName;
    initSerialPort();
    m_serialport->setPortName(port);
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
void Apexi::retryconnect()
{
    Apexi::openConnection(port);
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
    
    requestIndex = 2;
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
  /*  
  //Test enable raw message log 
    QString fileName = "RawMessage.txt";
    QFile mFile(fileName);
    if(!mFile.open(QFile::Append | QFile::Text)){
    }
    QTextStream out(&mFile);
    out << m_readData.toHex() <<endl;
    mFile.close();
    // Test End
  */
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
        if(requestIndex <= 6){requestIndex++;}
        else{requestIndex = 3;}
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
        case ID::OldSensorData:
            Apexi::decodeSensor(rawmessagedata);
            break;
        case ID::AuxData:
            Apexi::decodeAux(rawmessagedata);
            break;
        case ID::MapIndex:
            Apexi::decodeMap(rawmessagedata);
            break;
        case ID::OldMapIndex:
            Apexi::decodeMap(rawmessagedata);
            break;
        case ID::BasicData:
            Apexi::decodeBasic(rawmessagedata);
            break;
        case ID::OldBasicData:
            Apexi::decodeBasic(rawmessagedata);
            break;
        case ID::Init:
            Apexi::decodeInit(rawmessagedata);
            if (reconnect == 0)
            {
               qDebug() << "reconnect";
               reconnect = 1;
               requestIndex = 0;
               Apexi::closeConnection();
               QTimer::singleShot(2000, this, SLOT(retryconnect()));


            }
            break;
            
            /*
        case ID::Version:
            Apexi::decodeVersion(rawmessagedata);
            break;
       */
        default:
            break;
        }
        
        
        
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
   // m_dashboard->setSerialStat(QString("Sending Request " + p_request.toHex()));
    
    if (bytesWritten == -1) {
        m_dashboard->setSerialStat(m_serialport->errorString());
    } else if (bytesWritten != m_writeData.size()) {
        m_dashboard->setSerialStat(m_serialport->errorString());
    }
    
}

//Power FC requests

void Apexi::sendRequest(int requestIndex)
{
    if (Protocol == 0){
        switch (requestIndex){
        
        
        
        //New Apexi Structure
        case 0:
            //Init Platform (This returns the Platform String )
            Apexi::writeRequestPFC(QByteArray::fromHex("F3020A"));
            expectedbytes = 11;
            break;
        case 1:
            //Apexi::getSensorStrings();
            Apexi::writeRequestPFC(QByteArray::fromHex("DD0220"));
            expectedbytes = 83;
            break;
        case 2:
            //Init Platform (This returns the Platform String )
            Apexi::writeRequestPFC(QByteArray::fromHex("F3020A"));
            expectedbytes = 11;
            break;
            // Live Data
        case 3:
            //Apexi::getAdvData();
            Apexi::writeRequestPFC(QByteArray::fromHex("F0020D"));
            expectedbytes = 33;
            break;
            
        case 4:
            //Apexi::getMapIndices();
            Apexi::writeRequestPFC(QByteArray::fromHex("DB0222"));
            expectedbytes = 5;
            break;
        case 5:
            //Apexi::getSensorData();
            Apexi::writeRequestPFC(QByteArray::fromHex("DE021F"));
            expectedbytes = 21;
            break;
        case 6:
            //Apexi::getBasic();
            Apexi::writeRequestPFC(QByteArray::fromHex("DA0223"));
            expectedbytes = 23;
            break;
        case 7:
            //Apexi::getAux();
            Apexi::writeRequestPFC(QByteArray::fromHex("0002FD"));
            expectedbytes = 7;
            break;
        }
    }
    if (Protocol == 1)
    {
        switch (requestIndex){
        // Old Apexi Structure
        case 0:
            //Init Platform (This returns the Platform String )
            Apexi::writeRequestPFC(QByteArray::fromHex("F3020A"));
            expectedbytes = 11;
            break;
        case 1:
            //Apexi::getSensorStrings();
            Apexi::writeRequestPFC(QByteArray::fromHex("690294"));
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
            Apexi::writeRequestPFC(QByteArray::fromHex("680295"));
            expectedbytes = 5;
            break;
        case 4:
            //Apexi::getSensorData();
            Apexi::writeRequestPFC(QByteArray::fromHex("6A0293"));
            expectedbytes = 21;
            break;
        case 5:
            //Apexi::getBasic();
            Apexi::writeRequestPFC(QByteArray::fromHex("660297"));
            expectedbytes = 23;
            break;
        case 6:
            //Apexi::getAux();
            Apexi::writeRequestPFC(QByteArray::fromHex("0002FD"));
            expectedbytes = 7;
            
            break;
        }
    }
    
    m_timer.start(700); //Set timout to 700 mseconds 
}




void Apexi::Auxcalc (const QString &unitaux1,const qreal &an1V0,const qreal &an2V5,const QString &unitaux2,const qreal &an3V0,const qreal &an4V5)
{
    qreal aux1min = an1V0;
    qreal aux2max = an2V5;
    qreal aux3min = an3V0;
    qreal aux4max = an4V5;
    QString Auxunit1 = unitaux1;
    QString Auxunit2 = unitaux2;

    Apexi::calculatorAux(aux1min,aux2max,aux3min,aux4max,Auxunit1,Auxunit2);
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
        packageADV[12] = info->Watertemp -80;
        packageADV[13] = info->Intaketemp -80;
        packageADV[14] = info->Knock;
        packageADV[15] = info->BatteryV * 0.1;
        packageADV[16] = info->Speed ;
        packageADV[17] = info->Iscvduty * 0.001;
        packageADV[18] = info->O2volt;
        packageADV[19] = info->na1;
        packageADV[20] = info->Secinjpulse * 0.001;
        packageADV[21] = info->na2;
        
        m_dashboard->setrpm(packageADV[0]);
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
        {
            packageADV2[8] = (packageADV[8] - 0x8000) * 0.01;  //Positive Boost kgcm2

        }
        else
        {

            packageADV2[8] = (1.0 / 2560 + 0.001) * packageADV[8]; //Negative Boost in mmhg


        }
        packageADV2[9] = info->BoostDuty *0.005;
        packageADV2[10] = info->Watertemp -80;
        packageADV2[11] = info->Intaketemp -80;
        packageADV2[12] = info->Knock;
        packageADV2[13] = info->BatteryV *0.1;
        packageADV2[14] = info->Speed;
        packageADV2[15] = info->MAFactivity *0.16;
        packageADV2[16] = info->O2volt *0.005;
        packageADV2[17] = info->O2volt_2 *0.005;
        packageADV2[18] = info->ThrottleV *0.001;
        
        m_dashboard->setrpm(packageADV2[0]);
        m_dashboard->setEngLoad(packageADV2[1]);
        m_dashboard->setMAF1V(packageADV2[2]);
        m_dashboard->setMAF2V(packageADV2[3]);
        m_dashboard->setinjms(packageADV2[4]);
        //m_dashboard->setFue(packageADV2[5]);
        m_dashboard->setIgn(packageADV2[6]);
        m_dashboard->setDwell(packageADV2[7]);
        //m_dashboard->setMAP(packageADV2[8]);
        //m_dashboard->setBoostPreskpa(kpaboost);
        m_dashboard->setBoostDuty(packageADV2[9]);
        m_dashboard->setWatertemp(packageADV2[10]);
        m_dashboard->setIntaketemp(packageADV2[11]);
        m_dashboard->setKnock(packageADV2[12]);
        m_dashboard->setBatteryV(packageADV2[13]);
        m_dashboard->setSpeed(packageADV2[14]);
        m_dashboard->setMAFactivity(packageADV2[15]);
        m_dashboard->setO2volt(packageADV2[16]);
        m_dashboard->setO2volt_2(packageADV2[17]);
        m_dashboard->setThrottleV((packageADV2[18]*100));
        m_dashboard->setTPS((packageADV2[18]*100)/4.38);
        
    }
    //Toyota
    if (Model == 3)
    {
        fc_adv_info_t3* info=reinterpret_cast<fc_adv_info_t3*>(rawmessagedata.data());
        int checkboost = (unsigned char)rawmessagedata[17];
        packageADV3[0] = mul[0] * info->RPM3 + add[0];
        //previousRev_rpm[buf_currentIndex] = packageADV[0];
        packageADV3[1] = info->Intakepress3;
        packageADV3[2] = info->PressureV3 * 0.001;
        packageADV3[3] = info->ThrottleV3 * 0.001;
        packageADV3[4] = info->Primaryinp3;
        packageADV3[5] = info->Fuelc3;
        packageADV3[6] = info->Ign3;
        packageADV3[7] = info->Dwell3;
        if (checkboost == 128)
        {
            int convert = (unsigned char)rawmessagedata[16];
            advboost = convert * 0.01;
        }
        else
        {
            packageADV3[8] = info->BoostPres3 -760;
            advboost = packageADV3[8];
        }
        packageADV3[9] = mul[9] * info->BoostDuty3 + add[9];
        packageADV3[10] = info->Watertemp3 -80;
        packageADV3[11] = info->Intaketemp3 -80;
        packageADV3[12] = info->Knock3;
        packageADV3[13] = info->BatteryV3 *0.1;
        packageADV3[14] = info->Speed3;
        
        // packageADV3[14] *= speed_correction;
        //previousSpeed_kph[buf_currentIndex] = packageADV[14];
        //        packageADV3[15] = mul[15] * info->Iscvduty + add[15];
        packageADV3[16] = mul[16] * info->O2volt3 + add[16];
        //        packageADV3[17] = mul[17] * info->SuctionAirTemp + add[17];
        //        packageADV3[18] = mul[18] * info->ThrottleV_2 + add[18];
        packageADV3[19] = mul[19] * info->na13 + add[19];
        packageADV3[20] = 0;
        packageADV3[21] = 0;
        
        
        m_dashboard->setrpm(packageADV3[0]);
        m_dashboard->setIntakepress(packageADV3[1]);
        m_dashboard->setPressureV(packageADV3[2]);
        m_dashboard->setThrottleV(packageADV3[3]);
        m_dashboard->setPrimaryinp(packageADV3[4]);
        m_dashboard->setFuelc(packageADV3[5]);
        m_dashboard->setLeadingign(packageADV3[6]);
        m_dashboard->setTrailingign(packageADV3[7]);
        m_dashboard->setpim(advboost);
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
    packageAux[1] = mul[29] * info->AN2 + add[29];
    packageAux[2] = mul[29] * info->AN3 + add[29];
    packageAux[3] = mul[29] * info->AN4 + add[29];
    
    //qDebug()<< "AN1" << packageAux[0] ;
    //qDebug()<< "AN2" << packageAux[1] ;
    //qDebug()<< "AN3" << packageAux[2] ;
    //qDebug()<< "AN4" << packageAux[3] ;
    //Analog1
    AN1AN2calc = (((((auxval2-auxval1)*0.2) * (packageAux[0] - packageAux[1]))) + auxval1);
    AN3AN4calc = ((((auxval4-auxval3)*0.2) * (packageAux[2] - packageAux[3])) + auxval3);
    m_dashboard->setauxcalc1(AN1AN2calc);
    m_dashboard->setauxcalc2(AN3AN4calc);
    //qDebug()<< "AN1-AN2" << AN1AN2calc ;
    //qDebug()<< "AN1-AN2" << AN3AN4calc ;
    
}


void Apexi::decodeMap(QByteArray rawmessagedata)
{
    fc_map_info_t* info=reinterpret_cast<fc_map_info_t*>(rawmessagedata.data());
    
    packageMap[0] = mul[0] * info->Map_N + add[0];
    packageMap[1] = mul[0] * info->Map_P + add[0];
    
}
void Apexi::decodeBasic(QByteArray rawmessagedata)
{
    fc_Basic_info_t* info=reinterpret_cast<fc_Basic_info_t*>(rawmessagedata.data());
    
    qreal Boost;
    int checkboost = (unsigned char)rawmessagedata[13];
    packageBasic[0] = mul[15] * info->Basic_Injduty + add[0];
    packageBasic[1] = info->Basic_IGL;
    packageBasic[2] = info->Basic_IGT;
    packageBasic[3] = mul[0] * info->Basic_RPM + add[0];
    packageBasic[4] = mul[0] * info->Basic_KPH + add[0];
    packageBasic[5] = mul[0] * info->Basic_Boost;
    packageBasic[6] = mul[0] * info->Basic_Knock + add[0];
    packageBasic[7] = mul[0] * info->Basic_Watert + add[8];
    packageBasic[8] = mul[0] * info->Basic_Airt + add[8];
    packageBasic[9] = mul[15] * info->Basic_BattV + add[0];

        if (checkboost == 128)
        {
            int test = (unsigned char)rawmessagedata[12];
            Boost = test * 0.01;
            kpaboost = test * 0.980665;
         }
        else{
            Boost = (packageBasic[5] -760);
            kpaboost = Boost * 0.133322;
        }


    //m_dashboard->setInjDuty(packageBasic[0]);
    m_dashboard->setLeadingign(packageBasic[1]);
    m_dashboard->setTrailingign(packageBasic[2]);
    m_dashboard->setrpm(packageBasic[3]);
    m_dashboard->setSpeed(packageBasic[4]);
    m_dashboard->setBoostPres(Boost);
    m_dashboard->setBoostPreskpa(kpaboost);
    m_dashboard->setKnock(packageBasic[6]);
    m_dashboard->setWatertemp(packageBasic[7]);
    m_dashboard->setIntaketemp(packageBasic[8]);
    m_dashboard->setBatteryV(packageBasic[9]);
/*
    QString fileName = "Basic.txt";
    QFile mFile(fileName);
    if(!mFile.open(QFile::Append | QFile::Text)){
    }
    QTextStream out(&mFile);
    out << rawmessagedata.toHex() <<endl;
    mFile.close();
*/    
}

/*
  
void Apexi::decodeVersion(QByteArray rawmessagedata)
{
    //    ui->lineVersion->setText (QString(rawmessagedata).mid(2,5));
}
*/
void Apexi::decodeInit(QByteArray rawmessagedata)
{
    Modelname = QString(rawmessagedata).mid(2,8);
    //Mazda
    if (Modelname == "13B1    " || Modelname == "13B-REW " || Modelname == "13B-REW2" || Modelname == "13B-REW3" || Modelname == "13BT1PRO" || Modelname == "13BR1PRO" || Modelname == "13BR2PRO" || Modelname == "13BR3PRO")
    {
        Model =1;
    }   
    //Nissan
    if (Modelname == "NISSAN-L" || Modelname == "CA18DET " || Modelname == "SR20DE1 " || Modelname == "SR20DE2 " || Modelname == "SR20DE3 " || Modelname == "SR20DE4 " || Modelname == "SR20DET1" || Modelname == "SR20DET2" || Modelname == "SR20DET3" || Modelname == "SR20DET4" || Modelname == "SR20DET5" || Modelname == "SR20DET6" || Modelname == "SR20T1-D" || Modelname == "SR20T2-D" || Modelname == "SR20T5-D" ||Modelname == "RB20DET " || Modelname == "RB25DET " || Modelname == "RB25DET2" || Modelname == "RB26DETT" || Modelname == "VG30DETT" || Modelname == "CA181PRO" || Modelname == "SR2N1PRO" || Modelname == "SR2N2PRO" || Modelname == "SR2N3PRO" || Modelname == "SR2N4PRO" || Modelname == "SR201PRO" || Modelname == "SR202PRO" || Modelname == "SR203PRO" || Modelname == "SR204PRO" || Modelname == "SR205PRO" || Modelname == "SR206PRO" || Modelname == "RB201PRO" || Modelname == "RB251PRO" || Modelname == "RB252PRO" || Modelname == "RB261PRO" || Modelname == "RB262PRO" || Modelname == "RB26Pro " || Modelname == "RB26PRO " || Modelname == "RB26PRO1" || Modelname == "RB25PRO2" || Modelname == "CA18T1-D" || Modelname == "SR20T1-D" || Modelname == "SR20T2-D" || Modelname == "SR20T3-D" || Modelname == "SR20T4-D" || Modelname == "SR20T5-D" || Modelname == "RB26_1-D" || Modelname == "RB26_2-D" || Modelname == "VG30TT-D")
    {
        Model =2;
    }
    //Toyota
    if (Modelname == "TOYOTA-L" || Modelname == "1ZZ-FE  " || Modelname == "1ZZ-FET " || Modelname == "2ZZ-GE  " || Modelname == "3S-GE   " || Modelname == "3SGET   " || Modelname == "1JZ-GTE " || Modelname == "1JZGT-AT" || Modelname == "4A-G1   " || Modelname == "4A-G2   " || Modelname == "1JGT1PRO" || Modelname == "TOYOTA-D" || Modelname == "4A-GE   " || Modelname == "4A-GE1  " || Modelname == "4A-GE2  " || Modelname == "4A-GE3  " || Modelname == "4AGE1-TH" || Modelname == "4AGE2-TH" || Modelname == "4AGE3-TH" || Modelname == "4E-FTE1 " || Modelname == "4E-FTE2 " || Modelname == "1JZGT-D " || Modelname == "3S-GE1  " || Modelname == "3S-GE2  " || Modelname == "3S-GTE  " || Modelname == "3S-GTE2 " || Modelname == "3S-GTE3 " || Modelname == "1JZ-GTE2" || Modelname == "1JZ-GTE3" || Modelname == "2JZ-GTE1" || Modelname == "2JZ-GTE2" || Modelname == "4AGE1PRO" || Modelname == "4AGE2PRO" || Modelname == "4AGE3PRO" || Modelname == "4EFT1PRO" || Modelname == "4EFT2PRO" || Modelname == "3SGE1PRO" || Modelname == "3SGT1PRO" || Modelname == "3SGT2PRO" || Modelname == "3SGT3PRO" || Modelname == "1JGT2PRO" || Modelname == "1JGT3PRO" || Modelname == "2JGT1PRO" || Modelname == "2JGT2PRO")
    {
        Model =3;
    }
    //Subaru
    if (Modelname == "EJ20G   " || Modelname == "EJ20K   " || Modelname == "EJ207   " || Modelname == "EJ20R   " || Modelname == "EJ20GPRO")
    {
        Model =2;
    }
    //Honda
    if (Modelname == "D15B    " || Modelname == "B16A1   " || Modelname == "B16A-US " || Modelname == "B16A2   " || Modelname == "B16A1-TH" || Modelname == "B16B    " || Modelname == "B16B2   " || Modelname == "B16BT   " || Modelname == "B16B1-TH" || Modelname == "B16B2-TH" || Modelname == "B18C    " || Modelname == "B18C-US " || Modelname == "B18C2   " || Modelname == "B18CT   " || Modelname == "B18C1-TH" || Modelname == "B16A1PRO" || Modelname == "B16A2PRO" || Modelname == "B16B1PRO" || Modelname == "B16B2PRO" || Modelname == "B18C1PRO" || Modelname == "H22A    " )
    {
        Model =2;
    }
    //Mitsubishi
    if (Modelname == "4G63    " || Modelname == "4G63-US " || Modelname == "4G63-3  " || Modelname == "4G63-5  " || Modelname == "4G63-6  " || Modelname == "4G63-7  " ||  Modelname == "4G63D_US" || Modelname == "4G63-D  " || Modelname == "4G63-D3 " || Modelname == "4G63-D4 " || Modelname == "4G63-D5 " || Modelname == "4G63-D6 " || Modelname == "4G63-D7 ")
    {
        Model =3;
    }    
    m_dashboard->setPlatform(QString(rawmessagedata).mid(2,8) + QString::number(Model));
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

void Apexi::calculatorAux(float aux1min,float aux2max,float aux3min,float aux4max,QString Auxunit1,QString Auxunit2)
{
    auxval1 = aux1min;
    auxval2 = aux2max;
    auxval3 = aux3min;
    auxval4 = aux4max;
    Auxname1 = Auxunit1;
    Auxname2 = Auxunit2;
    qDebug() << Auxunit1<<auxval1 <<auxval2 <<Auxunit2 << auxval3<<auxval4;
}

void Apexi::writeDashfile(const QString &gauge1,const QString &gauge2,const QString &gauge3,const QString &gauge4,const QString &gauge5,const QString &gauge6)
{
//Creates the dashboard file for the Apexi Dash

    QString filename="UserDashApexi.txt";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text) )

    {
        QTextStream stream( &file );
        stream << gauge1 << endl;
        stream << gauge2 << endl;
        stream << gauge3 << endl;
        stream << gauge4 << endl;
        stream << gauge5 << endl;
        stream << gauge6 << endl;
    }

    QString filename2="/home/pi/UserDashboards/UserDashApexi.txt";
    QFile file2( filename2 );
    if ( file2.open(QIODevice::ReadWrite  | QIODevice::Truncate | QIODevice::Text) )

    {
        QTextStream stream( &file2 );
        stream << gauge1 << endl;
        stream << gauge2 << endl;
        stream << gauge3 << endl;
        stream << gauge4 << endl;
        stream << gauge5 << endl;
        stream << gauge6 << endl;
    }


}
