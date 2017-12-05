#include "serialobd.h"
#include "dashboard.h"
#include "serial.h"

QString Portnameselect;



SerialOBD::SerialOBD(QObject *parent)
    : QObject(parent)
    , m_dashboard(Q_NULLPTR)
{

}
SerialOBD::SerialOBD(DashBoard *dashboard, QObject *parent)
    : QObject(parent)
    , m_dashboard(dashboard)
{

}

void SerialOBD::SelectPort(const QString &portName)
{
    Portnameselect = portName;
    qDebug() << "Port Connected!"<< portName;

}

void SerialOBD::ConnectToSerialPort()
{
    qDebug() << "OBD ";
    //ParseAndReportClusterData("OPPED\r\r>10C0D2F0511\rS");//For testing purposes

    //triggers if engine has been turned off
    connect(this,SIGNAL(onEngineOff()),this,SLOT(EngineOff()));

    QSerialPortInfo serialInfo;
    QList <QSerialPortInfo> availablePorts;

    QByteArray data;
    QRegExp regExOk(".*OK.*");

    //Set all the port settings
    m_serial.setPortName(Portnameselect);
    m_serial.setBaudRate(QSerialPort::Baud38400);
    m_serial.setDataBits(QSerialPort::Data8);
    m_serial.setParity(QSerialPort::NoParity);
    m_serial.setStopBits(QSerialPort::OneStop);
    m_serial.setFlowControl(QSerialPort::NoFlowControl);
    if(m_serial.open(QIODevice::ReadWrite)){
        qDebug() << "Port Connected!";

        QThread::msleep(250);
        while(data.isEmpty()){

            //Verify OBD Connection, then continue to verify OBD serial port data
            if(data.isEmpty())
            m_serial.write("ATE1\r");
            m_serial.waitForBytesWritten(5000);
            m_serial.waitForReadyRead(5000);
            QThread::msleep(50);
            data = m_serial.readAll();
            if(regExOk.exactMatch(data)){
                while(!data.isEmpty())
                    RequestClusterData();
            }
            else
                data = "";
        }
        qDebug() << "ERROR: UNEXPECTED EXIT...";
    }
    else
        qDebug() << "ERROR: UNABLE TO OPEN PORT.";
}
///this function gets OBD data from ECU by
///requesting the data with PIDs
void SerialOBD::RequestClusterData()
{
    QByteArray data;
    m_tCodeCounter++;

    ///every 100 iterations of m_tCodeCounter
    ///a trouble code is requested
    if(m_tCodeCounter == 100){
        m_serial.write(PID.getMODE03TROUBLECODES() + "\r");
    }
    else{
        m_serial.write(PID.getMODE01CurrentData() +
                       PID.getRPM() +
                       PID.getSpeed() +
                       PID.getFuelTankLevel() +
                       PID.getEngineCoolantTemp() +
                       "11B3" +"\r");
    }

    m_serial.waitForBytesWritten(5000);
    m_serial.waitForReadyRead(5000);
    QThread::msleep(100);
    data = m_serial.readAll();

    qDebug() << data;

    ParseAndReportClusterData(data);
}

///this function take the data
/// and parses it to determine which info
/// goes where and whats the length of the
/// the requested value
void SerialOBD::ParseAndReportClusterData(QByteArray data)
{
    QByteArray tempData;
    QByteArray sRPM, sSpeed, sFuelStatus, sEngineCoolantTemp, sTroubleCode, sThrottlePosition;
    int k = 0;
    QRegExp TCodeRegEx(".*43.*");
    QRegExp dataTemp(".*\\d:\\s\\w\\w\\s\\w\\w\\s\\w\\w\\s\\w\\w\\s\\w\\w.*");

    if(!dataTemp.exactMatch(data) && !TCodeRegEx.exactMatch(data))
        data = "";

    if(dataTemp.exactMatch(data)){

        int i = 0;

        while(data[i] != ':')
            i++;

        data = data.mid(i + 1,data.length() - i);

        data = data.replace(" ", "").replace("\r1","").replace("\r2", "").replace("\r3", "").replace("\r", "").replace(":","")
                .replace(">", "").replace("r","");

        for(int i = 0; i < data.length(); i++){
            if(data[i] < '0' && data[i] > 'F')
                data.replace(data[i], "");
        }

        if(data.count() % 2 != 0){
            data == data.append("X");
        }
    }

    if(m_tCodeCounter == 20 || TCodeRegEx.exactMatch(data)){
        int i = 0;
        while(data[i] != '4' && data[i + 1] != '3')
            i++;

        data = data.mid(i,data.length() - i);

        data = data.replace(" ", "").replace("\r1","").replace("\r2", "").replace("\r3", "").replace("\r", "").replace(":","")
                .replace(">", "").replace("r","");

        m_tCodeCounter = 0;
    }

    for(int i = 0; i < data.length(); i++){

        if((data[i] >= '0' && data[i] <= '9') || (data[i] >= 'A' && data[i] <= 'F') || (data[i] != 'i')){
            tempData[k] = data[i];

            k++;

            if(tempData.length() == 2){

                if(tempData == PID.getRPM())
                {
                    for(int j = 0; j < 4; j++)
                        sRPM[j] = data[i + 1], i++;
                }
                if(tempData  == PID.getSpeed())
                {
                    for(int j = 0; j < 2; j++)
                        sSpeed[j] = data[i + 1], i++;
                }
                if(tempData == PID.getFuelTankLevel())
                {
                    for(int j = 0; j < 2; j++)
                        sFuelStatus[j] = data[i + 1], i++;
                }
                if(tempData == PID.getEngineCoolantTemp())
                {
                    for(int j = 0; j < 2; j++)
                        sEngineCoolantTemp[j] = data[i + 1], i++;
                }
                if(tempData == PID.getThrottlePosition())
                {
                    for(int j = 0; j < 2; j++)
                        sThrottlePosition[j] = data[i + 1], i++;
                }
                if(tempData == "43")
                {
                    for(int j = 0; j < 4; j++)
                        sTroubleCode[j] = data[i + 1], i++;
                }
                if(tempData == "11B3")
                {
                    for(int j = 0; j < 2; j++)
                        qDebug() << data[i + 1], i++;
                }

                tempData = "";
                k = 0;
            }
        }
    }

    HexToDecimal(sRPM,sSpeed,sFuelStatus,sEngineCoolantTemp,sThrottlePosition, sTroubleCode);
}
///this gets emitted when the engine has
/// not revieved any valid data in 300 milliseconds
void SerialOBD::EngineOff()
{
    emit obdRPM(0);
    emit obdCoolantTemp(300);
    emit obdFuelStatus(-3);
}
///this function turns the data from
/// the Parse function into the corresponding value
/// example: RPM string to an integer
void SerialOBD::HexToDecimal(QByteArray sRPM, QByteArray sSpeed, QByteArray sFuelStatus, QByteArray sECoolantTemp,
                             QByteArray sThrottlePosition, QByteArray sTroubleCode)
{
    int RPM = 0;
    int Speed = 0;
    int FuelStatus = 0;
    int EngineCoolantTemp = 0;
    int ThrottlePosition = 0;
    bool falsebool = false;
    QByteArray TroubleCode;

    RPM = QByteArray::fromHex(sRPM).toHex().toUInt(&falsebool,16) / 4;
    Speed = QByteArray::fromHex(sSpeed).toHex().toUInt(&falsebool,16) * 0.621371;
    FuelStatus = QByteArray::fromHex(sFuelStatus).toHex().toUInt(&falsebool,16) * 0.392156;
    EngineCoolantTemp = (QByteArray::fromHex(sECoolantTemp).toHex().toUInt(&falsebool,16));
    ThrottlePosition = QByteArray::fromHex(sThrottlePosition).toHex().toUInt(&falsebool,16) * 0.392156;

    if(RPM == 0)
        ArrayEngineOff[m_engineOffcount] = true;
    else
        ArrayEngineOff[m_engineOffcount] = false;
    m_engineOffcount++;

    //parse trouble code data
    if(sTroubleCode[0] >= '0' && sTroubleCode[0] <= '3')
        TroubleCode = "P" + sTroubleCode;
    if(sTroubleCode[0] >= '4' && sTroubleCode[0] <= '7')
        TroubleCode = "C" + sTroubleCode;
    if(sTroubleCode[0] == '8' || sTroubleCode[0] == '9' ||
            sTroubleCode[0] == 'A' || sTroubleCode[0] == 'B')
        TroubleCode = "B" + sTroubleCode;
    if(sTroubleCode[0] >= 'C' && sTroubleCode[0] <= 'F')
        TroubleCode = "U" + sTroubleCode;

    //report the values recieved to instrumentcluster class
    if(RPM > 100)
        m_dashboard->setRevs(RPM);
        emit obdRPM(RPM);
    if(Speed > 0)
        m_dashboard->setSpeed(Speed);
        emit obdMPH(Speed);
    if(FuelStatus > 0 )
        emit obdFuelStatus(FuelStatus);
    if(EngineCoolantTemp > 0)
        m_dashboard->setWatertemp(EngineCoolantTemp);
        emit obdCoolantTemp(EngineCoolantTemp);
    if(TroubleCode != "")
        emit obdTroubleCode(TroubleCode);


    //when this array is entirely false, this will set the cluster values to "off" state
    if(ArrayEngineOff[0] == true && ArrayEngineOff[1] == true && ArrayEngineOff[2] == true)
        EngineOff();
    if(m_engineOffcount == 3){
        m_engineOffcount = 0;
        ArrayEngineOff[0] = false;
        ArrayEngineOff[1] = false;
        ArrayEngineOff[2] = false;
    }
}
