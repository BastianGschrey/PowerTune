#include "serialsetting.h"
//#include "ui_serialsetting.h"
//#include <QLineEdit>
#include <QtSerialPort/QSerialPortInfo>
#include <QIntValidator>


QT_USE_NAMESPACE

static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

SerialSetting::SerialSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialSetting)
{
    ui->setupUi(this);

    intValidator = new QIntValidator(0, 4000000, this);

    //ui->cboBaudRate->setInsertPolicy(QComboBox::NoInsert);

    fillPortsParameters(); //call function to fill comboboxes

    connect(ui->btnApply, SIGNAL(clicked()),this, SLOT(apply()));
}

SerialSetting::~SerialSetting()
{
    delete ui;
}

void SerialSetting::fillPortsParameters()
{

//fill cboComport with all available comports
foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
    ui->cboComport->addItem(info.portName());
    }

}

void SerialSetting::apply()
{ //Slot when apply button is clicked, stores selected settings
    SerialSetting::currentSettings.portName = ui->cboComport->currentText();
    //SerialSetting::currentSettings.baudRate = ui->cboBaudRate->currentText().toInt();
    hide();
}

SerialSetting::Settings SerialSetting::settings()
{
    return SerialSetting::currentSettings;
}

void SerialSetting::on_btnApply_clicked()
{

}
