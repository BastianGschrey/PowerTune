#include "gps.h"
#include "dashboard.h"
#include "connect.h"
#include "QStringList"


int connected;
GPS::GPS(QObject *parent)
    : QObject(parent)
    , m_dashboard(Q_NULLPTR)

{

}
GPS::GPS(DashBoard *dashboard, QObject *parent)
    : QObject(parent)
    , m_dashboard(dashboard)
{
}

void GPS::readSerial()
{
    QRegExp sep("(\n|\r)");
    QStringList buffer_split = serialBuffer.split(sep,QString::SkipEmptyParts); //  split the serialBuffer string, parsing with ',' as the separator


    if(buffer_split.length() < 5){
        serialData = com->readAll();
        serialBuffer = serialBuffer + QString::fromStdString(serialData.toStdString());
        serialData.clear();
    }else{
        serialBuffer.clear();
        decode(buffer_split);
        //qDebug() <<"Invalid Packages:" << packages_invalidos;
        //qDebug() <<"Available bytes:" << com->bytesAvailable();

    }

}



bool GPS::checksum(QString package){
    short start = 0;
    while (package.at(start) != '*') {
        start++;
        if(start >= package.size()){
            packages_invalidos++;
            return false;
        }
    }
    QString to_chk = package.mid(1,start-1);
    package.remove(0,start+1);
    int cksm = 0;

    foreach (QChar letra, to_chk) {
        cksm = cksm ^ letra.toLatin1();
    }

    if(cksm == package.toInt(nullptr,16)){
        return true;
    }
    packages_invalidos++;
    return false;


}

void GPS::GPGGA(QString package){
    QRegExp sep("(\\,|\\*)");
    QStringList pkt_data = package.split(sep);
    gpgga_data package_data;


    package_data.A_hora = pkt_data[1];
    package_data.B_latitude = pkt_data[2];
    package_data.C_latitude_dir = pkt_data[3].toStdString()[0];
    package_data.D_longitude = pkt_data[4];
    package_data.E_longitude_dir = pkt_data[5].toStdString()[0];
    package_data.F_qualidade_fixa = pkt_data[6].toInt();
    package_data.G_quantidade_satelites = pkt_data[7].toInt();
    package_data.H_diluicao_da_precisao_horizontal = pkt_data[8].toFloat();
    package_data.I_altitude = pkt_data[9].toFloat();
    package_data.J_unidade_medida_altura = pkt_data[10].toStdString()[0];
    package_data.K_altura_geoide_acima_elipsoide = pkt_data[11].toFloat();
    package_data.L_unidade_medida_geoide = pkt_data[12].toStdString()[0];
    package_data.M_idade_ultima_atualizacao_dgps = pkt_data[13].toFloat();
    package_data.N_dgps_id = pkt_data[14].toInt();


    QString hora;
    hora = package_data.A_hora.mid(0,6);
    int inserts = 0;
    for (int var = 1; var < hora.size()-inserts; ++var) {
        if(var % 2 == 0){
            hora.insert(var+inserts,':');
            inserts++;
        }
    }
    //qDebug()<< "time " << hora;
    m_dashboard->setgpsTime(hora);
    //qDebug()<< "horizontal precision" << (QString::number(package_data.H_diluicao_da_precisao_horizontal));
    //qDebug()<< "altitude" << (QString::number(package_data.I_altitude));
    m_dashboard->setgpsAltitude(QString::number(package_data.I_altitude));
    //    ui->hora->setText(hora);
    //    ui->precisao->setText(QString::number(package_data.H_diluicao_da_precisao_horizontal));
    //    ui->altitude->setText(QString::number(package_data.I_altitude));


    int inteiro;
    double real;
    QString val;
    while (package_data.B_latitude[0] == '0') {
        package_data.B_latitude.remove(0,1);
    }
    val = package_data.B_latitude.mid(0,2);
    package_data.B_latitude = package_data.B_latitude.remove(0,2);
    inteiro = val.toInt();
    val = package_data.B_latitude;
    real = val.toDouble();


    if(package_data.C_latitude_dir == 'S' || package_data.C_latitude_dir == 's')
    { //  ui->latitude->setText(QString::number(((real/60)+inteiro)*-1,'g',9));
        //qDebug()<< "latitude" << (QString::number(((real/60)+inteiro)*-1,'g',9));
        m_dashboard->setgpsLatitude(QString::number(((real/60)+inteiro)*-1,'g',9));
    }
    else
    {
        // ui->latitude->setText(QString::number(((real/60)+inteiro),'g',9));
        //qDebug()<< "latitude" << (QString::number(((real/60)+inteiro),'g',9));
        m_dashboard->setgpsLatitude(QString::number(((real/60)+inteiro),'g',9));
    }


    while (package_data.D_longitude[0] == '0') {
        package_data.D_longitude.remove(0,1);
    }

    val = package_data.D_longitude.mid(0,2);
    package_data.D_longitude = package_data.D_longitude.remove(0,2);
    inteiro = val.toInt();
    val = package_data.D_longitude;
    real = val.toDouble();

    //qDebug()<< "latitude dir" << package_data.C_latitude_dir;
            //qDebug()<< "longitude dir" << package_data.E_longitude_dir;
         //qDebug()<< " C latitude dir" << package_data.C_latitude_dir;

    if(package_data.E_longitude_dir == 'W' || package_data.E_longitude_dir == 'w')
    {
        //   ui->longitude->setText(QString::number(((real/60)+inteiro)*-1,'g',9));
        ////qDebug()<< "longitude" << (QString::number(((real/60)+inteiro)*-1,'g',9));
        m_dashboard->setgpsLongitude(QString::number(((real/60)+inteiro)*-1,'g',9));
    }
    else
    {
        //   ui->longitude->setText(QString::number(((real/60)+inteiro),'g',9));
      //  //qDebug()<< "longitude" << (QString::number(((real/60)+inteiro),'g',9));
        m_dashboard->setgpsLongitude(QString::number(((real/60)+inteiro),'g',9));
    }




}

void GPS::GPGSA(QString package){
    QRegExp sep("(\\,|\\*)");
    QStringList pkt_data = package.split(sep);
    gpgsa_data package_data;
    package_data.CN_ids_satelites = new int[12];
    for (int var = 0; var < 12; ++var) {
        package_data.CN_ids_satelites[var] = -1;
    }
    package_data.A_modo = pkt_data[1].toStdString()[0];
    package_data.B_modo_dimensional = pkt_data[2].toStdString()[0];
    package_data.CN_ids_satelites[0] = pkt_data[3].toInt();
    package_data.CN_ids_satelites[1] = pkt_data[4].toInt();
    package_data.CN_ids_satelites[2] = pkt_data[5].toInt();
    package_data.CN_ids_satelites[3] = pkt_data[6].toInt();
    package_data.CN_ids_satelites[4] = pkt_data[7].toInt();
    package_data.CN_ids_satelites[5] = pkt_data[8].toInt();
    package_data.CN_ids_satelites[6] = pkt_data[9].toInt();
    package_data.CN_ids_satelites[7] = pkt_data[10].toInt();
    package_data.CN_ids_satelites[8] = pkt_data[11].toInt();
    package_data.CN_ids_satelites[9] = pkt_data[12].toInt();
    package_data.CN_ids_satelites[10] = pkt_data[13].toInt();
    package_data.CN_ids_satelites[11] = pkt_data[14].toInt();
    package_data.O_PDOP = pkt_data[15].toFloat();
    package_data.P_HDOP = pkt_data[16].toFloat();
    package_data.Q_VDOP = pkt_data[17].toFloat();
    //satelites_a.clear();
    int cc = 0;
    for (int var = 0; var < 12; ++var) {
        if(package_data.CN_ids_satelites[var] != 0 && package_data.CN_ids_satelites[var] != -1){
            cc++;
        }
    }
    //qDebug()<< "active Satelites" << (QString::number(cc));




    delete[] package_data.CN_ids_satelites;

}

void GPS::GPGSV(QString package){
    QRegExp sep("(\\,|\\*)");
    QStringList pkt_data = package.split(sep);
    gpgsv_data package_data;

    package_data.A_total_mensagens = pkt_data.at(1).toInt();
    package_data.B_numero_desta_mensagem  = pkt_data.at(2).toInt();
    package_data.C_satelites_visiveis  = pkt_data.at(3).toInt();
    package_data.DS_sats[0].A_sv_prn = pkt_data.at(4).toInt();
    package_data.DS_sats[0].B_elevacao_graus = pkt_data.at(5).toInt();
    package_data.DS_sats[0].C_azimuth = pkt_data.at(6).toInt();
    package_data.DS_sats[0].D_snr = pkt_data.at(7).toInt();
    package_data.DS_sats[1].A_sv_prn = pkt_data.at(8).toInt();
    package_data.DS_sats[1].B_elevacao_graus = pkt_data.at(9).toInt();
    package_data.DS_sats[1].C_azimuth = pkt_data.at(10).toInt();
    package_data.DS_sats[1].D_snr = pkt_data.at(11).toInt();
    package_data.DS_sats[2].A_sv_prn = pkt_data.at(12).toInt();
    package_data.DS_sats[2].B_elevacao_graus = pkt_data.at(13).toInt();
    package_data.DS_sats[2].C_azimuth = pkt_data.at(14).toInt();
    package_data.DS_sats[2].D_snr = pkt_data.at(15).toInt();
    package_data.DS_sats[3].A_sv_prn = pkt_data.at(16).toInt();
    package_data.DS_sats[3].B_elevacao_graus = pkt_data.at(17).toInt();
    package_data.DS_sats[3].C_azimuth = pkt_data.at(18).toInt();
    package_data.DS_sats[3].D_snr = pkt_data.at(19).toInt();

    //qDebug()<< "satelites_visible" << (QString::number(package_data.C_satelites_visiveis));
    m_dashboard->setgpsVisibleSatelites(QString::number(package_data.C_satelites_visiveis));

}

void GPS::GPRMC(QString package){
    QRegExp sep("(\\,|\\*)");
    QStringList pkt_data = package.split(sep);
    gprmc_data package_data;

    package_data.A_hora = (int)pkt_data[1].toFloat();
    package_data.B_warning = pkt_data[2].toStdString()[0];
    package_data.C_latitude = pkt_data[3].toFloat();
    package_data.D_latitude_coord = pkt_data[4].toStdString()[0];
    package_data.E_longitude = pkt_data[5].toFloat();
    package_data.F_longitude_coord = pkt_data[6].toStdString()[0];
    package_data.G_velocidade_nos = pkt_data[7].toFloat();
    package_data.H_CMG = pkt_data[8].toFloat();
    package_data.I_data = pkt_data[9].toInt();
    package_data.J_variacao_magnetica = pkt_data[10].toFloat();
    package_data.K_variacao_magnetica_coord = pkt_data[11].toStdString()[0];

    //qDebug()<< "velocity" <<(QString::number(package_data.G_velocidade_nos * 1.852));
    m_dashboard->setgpsSpeed(QString::number(package_data.G_velocidade_nos * 1.852));
    //   ui->velocidade->setText(QString::number(package_data.G_velocidade_nos * 1.852));

}
/*
void GPS::sat_but_clicked(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    static QBrush* last;
    static int last_sat=-1;
    QString aaa(button->text());
    int inx=0;



    for(auto e : sat_ref.keys())
    {
        if(e == aaa.toInt())
            inx = sat_ref.value(e);
    }


    if(last_sat != -1){
        sats_grap[last_sat]->setBrush(*last);
    }



    if(sats_grap[inx]->brush() == *brush_preto){
        last = brush_preto;
    }else if(sats_grap[inx]->brush() == *brush_amarelo){
        last=brush_amarelo;
    }
    last_sat = inx;
    sats_grap[inx]->setBrush(*brush_azul);


    for (unsigned var = 0; var < satelites_v.size(); ++var) {
        for (int vara = 0; vara < 4; ++vara) {
            if (QString::number(satelites_v[var][vara].A_sv_prn) == button->text() ) {
                ui->svprn->setText(QString::number( satelites_v[var][vara].A_sv_prn));
                ui->elevacao->setText(QString::number(satelites_v[var][vara].B_elevacao_graus));
                ui->azimuth->setText(QString::number(satelites_v[var][vara].C_azimuth));
                ui->sinal->setText(QString::number(satelites_v[var][vara].D_snr));


            }

        }
    }



}
*/
void GPS::decode(QStringList packages){
    QString tipo;
    int starting_point;

    foreach (QString package, packages) {
        starting_point=0;
        if(package == "")
            break;
        while (package.at(starting_point) != '$') {
            starting_point++;
            if (starting_point >= package.size()) {
                goto bail;
            }
        }

        package.remove(0,starting_point);

        tipo = package.mid(1,5);

        if(tipo == "GPGSV"){
            if(checksum(package)){
                GPGSV(package);
            }
        }else if(tipo == "GPGGA"){
            if(checksum(package)){
                GPGGA(package);
            }
        }else if(tipo == "GPGSA"){
            if(checksum(package)){
                GPGSA(package);
            }
        }else if(tipo == "GPRMC"){
            if(checksum(package)){
                GPRMC(package);
            }

        }else {
            packages_invalidos++;
        }

        ////qDebug() << tipo;

        continue;
bail:
        packages_invalidos++;
        continue;
    }


}


void GPS::startGPScom(const QString &portName)
{

    com = new QSerialPort(this);
    serialBuffer = "";
    //qDebug() <<"StartGPS"<< portName ;



    com->setPortName(portName);
    com->open(QSerialPort::ReadOnly);
    com->setBaudRate(QSerialPort::Baud4800);
    com->setDataBits(QSerialPort::Data8);
    com->setFlowControl(QSerialPort::NoFlowControl);
    com->setParity(QSerialPort::NoParity);
    com->setStopBits(QSerialPort::OneStop);
   // QObject::connect(com, SIGNAL(readyRead()), this, SLOT(readSerial()));
    connect(this->com,SIGNAL(readyRead()),this, SLOT(readSerial()));
    connected =1;


    for (int var = 0; var < 1000; ++var) {
        QString buffer("$GPRMC,232803.000,A,2709.5426,S,05131.4711,W,0.14,6.67,110416,,,A*64\n"
                       "$GPGSV,5,1,20,03,69,085,26,23,55,181,32,09,42,233,21,22,35,057,43*78\n"
                       "$GPGGA,232803.000,2709.5426,S,05131.4711,W,1,8,0.96,697.8,M,3.1,M,,*62\n"
                       "$GPGSA,A,3,03,23,09,22,07,16,01,26,,,,,1.32,0.96,0.90*0A\n"
                       "$GPGSV,5,2,20,07,35,319,19,16,29,090,24,06,24,235,17,01,23,357,33*79\n"
                       "$GPGSV,5,3,20,49,21,073,39,26,19,120,24,11,07,001,,30,07,321,29*7A\n"
                       "$GPGSV,5,4,20,07,35,319,19,16,29,090,24,06,24,235,17,01,23,357,33*79\n"
                       "$GPGSV,5,5,20,49,21,073,39,26,19,120,24,11,07,001,,30,07,321,29*7A\n"
                       );



        decode(buffer.split("\n",QString::SkipEmptyParts));
    }





}

void GPS::stopGPScom()
{
    if (connected == 1)
    {
     connected =0;
     com->close();
    }
}

