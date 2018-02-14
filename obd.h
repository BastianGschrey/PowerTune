#ifndef OBD_H
#define OBD_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QtSerialPort/QSerialPort>



namespace APEXI {
    namespace DATA {
        enum ENUM {
            Advance=0xF0,
            MapIndex=0xDB,
            SensorData=0xDE,
            BaiscData=0xDA,
            AuxData=0x00

       };
    }
}


class SerialPort;
class DashBoard;




class OBD : public QObject
{
    Q_OBJECT
public:


    explicit OBD(QObject *parent = 0);
    explicit OBD(DashBoard *dashboard, QObject *parent = 0);

    Q_INVOKABLE void clear() const;
    Q_INVOKABLE void initSerialPort();
    Q_INVOKABLE void openConnection(const QString &portName);
    Q_INVOKABLE void closeConnection();

public slots:


public:
    void writeRequest(QByteArray);

private:
    DashBoard *m_dashboard;
    SerialPort *m_serial;
    QStringList *m_ecuList;
    qint64      m_bytesWritten;
    QByteArray  m_readData;
    QTimer      m_timer;
    QByteArray  m_buffer;
    QByteArray  m_message;
    QByteArray  m_writeData;

signals:
    void sig_finished();
    void sig_error(QString err);
    void sig_ApexiDataAvailable(QByteArray);



public slots:
    void readyToRead();
    void handleTimeout();
    void handleBytesWritten(qint64 bytes);
    void handleError(QSerialPort::SerialPortError error);
    void messageconstructor(const QByteArray &buffer);
    void sendRequest(int requestIndex);
    void readData(QByteArray serialdata);

};

#endif // OBD_H
