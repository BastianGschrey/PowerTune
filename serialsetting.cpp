#include "serialsetting.h"
#include "ui_serialsetting.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QIntValidator>
#include <QLineEdit>

QT_USE_NAMESPACE

static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

SerialSetting::SerialSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialSetting)
{
    ui->setupUi(this);

    intValidator = new QIntValidator(0, 4000000, this);

    ui->cboBaudRate->setInsertPolicy(QComboBox::NoInsert);

    fillPortsParameters(); //call function to fill comboboxes

    connect(ui->btnApply, SIGNAL(clicked()),this, SLOT(apply()));


    Settings settings; //create variable of struct Settings defined in header
}

SerialSetting::~SerialSetting()
{
    delete ui;
}

void SerialSetting::fillPortsParameters()
{

    //fill cboBaudRate with baudrates
ui->cboBaudRate->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
ui->cboBaudRate->addItem(QStringLiteral("57600"),QSerialPort::Baud57600);
ui->cboBaudRate->addItem(QStringLiteral("115200"),QSerialPort::Baud115200);

foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
    ui->cboComport->addItem(info.portName());
    }

}

void SerialSetting::apply(){

}
