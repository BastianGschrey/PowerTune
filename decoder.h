#ifndef DECODER_H
#define DECODER_H

#include <QObject>

class DashBoard;

class Decoder : public QObject
{
    Q_OBJECT

private:
//FD3S Definition
    #define FC_INFO_MUL		{1, 0.0001, 1, 1, 1.0/256, 1.0/256, 1, 1, 1, 212.0/256, 0.4, 0.4, 1, 1, 1, 0.1, 1, 0.1, 0.02, 1, 1.0/256, 1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 5.0/255, 5.0/255, 5.0/255, 5.0/255, 0.01, 0.001, 0.019, 40, 0.05, 0.004 , 256, -0.00390625, 1.0/128,100}
    #define FC_INFO_ADD		{0,-1.0332, 0, 0, 0, 0, -25, -25, -80, 0, 0, 0, -80, -80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -128}

    double packageADV[33];

    struct fc_adv_info_t{

        quint16 requesttype;
        quint16 RPM;
        quint16 Intakepress;
        //quint16 Boostcal;
        quint16 PressureV;
        quint16 ThrottleV;
        quint16 Primaryinp;
        quint16 Fuelc;
        quint8 Leadingign;
        quint8 Trailingign;
        quint8 Fueltemp;
        quint8 Moilp;
        quint8 Boosttp;
        quint8 Boostwg;
        quint8 Watertemp;
        quint8 Intaketemp;
        quint8 Knock;
        quint8 BatteryV;
        quint16 Speed;
        quint16 Iscvduty;
        quint8 O2volt;
        quint8 na1;
        quint16 Secinjpulse;
        quint8 na2;
        quint8 checksum;
        fc_adv_info_t parse(const QByteArray &);
    };

    double packageSens[20];

    struct fc_sens_info_t{

        quint16 requesttype;
        quint16 pim;
        quint16 vta1;
        quint16 vta2;
        quint16 vmop;
        quint16 wtrt;
        quint16 airt;
        quint16 fuelt;
        quint16 O2S;
        quint16 flags;
        quint8  checksum;

        fc_sens_info_t parse(const QByteArray &);

    };

    double packageMap[2];

    struct fc_map_info_t{

        quint16 requesttype;
        quint8 Map_N;
        quint8 Map_P;
        quint8 checksum;

        fc_map_info_t parse(const QByteArray &);
    };

    double packageAux[4];

    struct fc_aux_info_t{

        quint16 requesttype;
        quint8 AN1;
        quint8 AN2;
        quint8 AN3;
        quint8 AN4;
        quint8 checksum;

        fc_aux_info_t parse(const QByteArray &);
    };

    double packageBasic[22];

    struct fc_Basic_info_t{

        quint16 requesttype;
        quint16 Basic_Injduty;
        quint16 Basic_IGL;
        quint16 Basic_IGT;
        quint16 Basic_RPM;
        quint16 Basic_KPH;
        quint16 Basic_Boost;
        quint16 Basic_Knock;
        quint16 Basic_Watert;
        quint16 Basic_Airt;
        quint16 Basic_BattV;
        quint8 checksum;

        fc_Basic_info_t parse(const QByteArray &);
    };

     double packageRevIdle[16];

     struct fc_RevIdle_info_t{

        quint16 requesttype;
        quint16 RevLIM;
        quint16 FCAE;
        quint16 FCEL;
        quint16 FCAC;
        quint16 IdleAE;
        quint16 IdleEL;
        quint16 IdleAC;
        quint8 checksum;

        fc_RevIdle_info_t parse(const QByteArray &);
    };

     double packageTurboTrans[12];

     struct fc_TurboTrans_info_t{

        quint16 requesttype;
        quint8 TPS01;
        quint8 TPS02;
        quint8 TPS03;
        quint8 LowRPM1;
        quint8 LowRPM2;
        quint8 LowRPM3;
        quint8 HighRPM1;
        quint8 HighRPM2;
        quint8 HighRPM3;
        quint8 checksum;

        fc_TurboTrans_info_t parse(const QByteArray &);
    };

     double packageBoostControl[12];

     struct fc_BoostCont_info_t{

        quint16 requesttype;
        quint8 Setting1;
        quint8 Setting2;
        quint8 Setting3;
        quint8 BoostPrimary1;
        quint8 BoostSecondary1;
        quint8 BoostPrimary2;
        quint8 BoostSecondary2;
        quint8 DutyPrimary1;
        quint8 DutySecondary1;
        quint8 DutyPrimary2;
        quint8 DutySecondary2;
        quint8 checksum;

        fc_BoostCont_info_t parse(const QByteArray &);
    };
     double packageInjOverlap[12];

     struct fc_InjOverlap_info_t{

        quint16 requesttype;
        quint8 InjOvBoost1;
        quint8 lineInjOvSet1;
        quint8 InjOvBoost2;
        quint8 lineInjOvSet2;
        quint8 InjOvBoost3;
        quint8 lineInjOvSet3;
        quint8 checksum;
        fc_InjOverlap_info_t parse(const QByteArray &);
    };
     double packageInjPriLagvsBattV[12];

     struct fc_InjPriLagvsBattV_info_t{

        quint16 requesttype;
        quint16 InjPriLag16V;
        quint16 InjPriLag14V;
        quint16 InjPriLag12V;
        quint16 InjPriLag10V;
        quint16 InjPriLag8V;
        quint16 InjPriLag6V;
        quint8 checksum;
        fc_InjPriLagvsBattV_info_t parse(const QByteArray &);
    };

     double packageInjScLagvsBattV[12];

     struct fc_InjScLagvsBattV_info_t{

        quint16 requesttype;
        quint16 InjScLag16V;
        quint16 InjScLag14V;
        quint16 InjScLag12V;
        quint16 InjScLag10V;
        quint16 InjScLag8V;
        quint16 InjScLag6V;
        quint8 checksum;
        fc_InjScLagvsBattV_info_t parse(const QByteArray &);
    };
     double packageFuelInjectors[26];

     struct fc_FuelInjectors_info_t{

        quint16 requesttype;
        quint8 empty1;
        quint8 frontpulse; //(for percent multiply by 100 to get percentage)
        quint8 empty2;
        quint8 rearpulse; //(for percent multiply by 100 to get percentage)
        quint8 frntprilag; //(multiply by 0.004)
        quint8 empty3;
        quint8 frntseclag; // (multiply by 0.004)
        quint8 empty4;
        quint8 rearprilag; //  (multiply by 0.004)
        quint8 empty5;
        quint8 rearseclag; // (multiply by 0.004)
        quint8 empty6;
        quint16 prinjsize;
        quint16 secinjsize;
        quint16 prisectransprc; // (divide it by 10to get the percentage)
        quint16 prisectransms;
        quint8 empty7;
        quint8 empty8;
        quint8 empty9;
        quint8 empty10;
        quint8 checksum;
        fc_FuelInjectors_info_t parse(const QByteArray &);
    };

     struct fc_FuelBase_info_t{
         quint16 requesttype;
         quint16 fuelBase[100];
         quint8 checksum;
         fc_FuelBase_info_t parse(const QByteArray &);
     };

     struct fc_fullFuelBase_info_t{
         quint16 fuelBase[800];
     };



     // Adaptronic Streaming Coms Package structure
     double packageAdaptronic[250];

     struct Adaptronic_Streaming_coms{

     quint8 Adress;
     quint8 Command;
     quint8 Length;

     quint16	RPM;
     quint16	MAP;
     quint16	MAT;
     quint16	WT;
     quint16	AuxT;
     quint16	AFR;
     quint16	KnockValue;
     quint16	TPS;
     quint16	IdleValue;
     quint16	Battery;
     quint16	MVSS;
     quint16	SVSS;
     quint16	Inj1;
     quint16	Inj2;
     quint16	Inj3;
     quint16	Inj4;
     quint16	Ign1;
     quint16	Ign2;
     quint16	Ign3;
     quint16	Ign4;
     quint16	Trim;
     quint16	Updates1;
     quint16	Updates2;
     quint16	Updates3;
     quint16	Updates4;
     quint16	Updates5;
     quint16	Updates6;
     quint16	Updates7;
     quint16	Updates8;
     quint16	Updates9;
     quint16	Updates10;
     quint16	Updates11;
     quint16	Updates12;
     quint16	Updates13;
     quint16	Updates14;
     quint16	Updates15;
     quint16	Updates16;
     quint16	Updates17;
     quint16	Updates18;
     quint16	Updates19;
     quint16	dTPSdt;
     quint16	dMAPdt;
     quint16	TargetIdle;
     quint16	TargetMAP;
     quint16	TargetAFR;
     quint16	BOVStateGear;
     quint16	CuttingState;
     quint16	Flags;
     quint16	DigIns;
     quint16	DigOuts;
     quint16	LearningState;
     quint16	RawFuelMapValue;
     quint16	RawIgnMapValue;
     quint16	MainLoopSpeed;
     quint16	SecSerialPortStatus;
     quint16	WastegateDCRaw;
     quint16	WastegateDCFinal;
     quint16	ADCChan0;
     quint16	ADCChan1;
     quint16	ADCChan2;
     quint16	ADCChan3;
     quint16	ADCChan4;
     quint16	ADCChan5;
     quint16	ADCChan6;
     quint16	ADCChan7;
     quint16	ADCChan8;
     quint16	ADCChan9;
     quint16	ADCChan10;
     quint16	ADCChan11;
     quint16	ADCChan12;
     quint16	ADCChan13;
     quint16	ADCChan14;
     quint16	ADCChan15;
     quint16	ADCChan16;
     quint16	ADCChan17;
     quint16	ADCChan18;
     quint16	Serial_number_0_1;
     quint16	Serial_number_2_3;
     quint16	Serial_number_4_5;
     quint16	Serial_number_6_7;
     quint16	Serial_number_8_9;
     quint16	Serial_number_10_11;
     quint16	Serial_number_12_13;
     quint16	Serial_number_14_15;
     quint16	Serial_number_16_17;
     quint16	Serial_number_18_19;
     quint16	Serial_number_20_21;
     quint16	Serial_number_22_23;
     quint16	VVT1_1;
     quint16	AsyncPump;
     quint16	MasterVSSDiff;
     quint16	SlaveVSSDiff;
     quint16	MVSS1Raw;
     quint16	SVSS1Raw;
     quint16	MVSS2Raw;
     quint16	SVSS2Raw;
     quint16	VVT2;
     quint16	VVT1;
     quint16	VVT2Set;
     quint16	VVT1Set;
     quint16	ExtIn;
     quint16	EGT1;
     quint16	EGT2;
     quint16	EGT3;
     quint16	DigInRaw_inj_test1;
     quint16	RTInRaw_inj_test2;
     quint16	AuxOut_override;
     quint16	EGT4;
     quint16	LED_output_override;
     quint16	Actual_Dwell_time;
     quint16	FW_Version;
     quint16	Actual_ECU_ID;
     quint16	Flex_fuel_1;
     quint16    Flex_fuel_2;
     quint16	MOP;
     quint16	CrankInt;
     quint16	Diginputs_2;
     quint16	Ignition_Cut;
     quint16	Slip;
     quint16	Oil_pressure_kPa;
     quint16	Fuel_pressure_kPa;
     quint16	Ch1_0_5V;
     quint16	Aux_pressure_kPa;
     quint16	Safety_cut_functions;
     quint16	Injection_angle;
     quint16	CRC16;



         Adaptronic_Streaming_coms parse(const QByteArray &);
      };

public:
    explicit Decoder(QObject *parent = 0);
     explicit Decoder(DashBoard *dashboard, QObject *parent = 0);

private:
     DashBoard *m_dashboard;
public slots:     
     void decodeAdv(QByteArray serialdata);
     void decodeSensor(QByteArray serialdata);
     void decodeAux(QByteArray serialdata);
     void decodeMap(QByteArray serialdata);
     void decodeBasic(QByteArray serialdata);
     void decodeRevIdle(QByteArray serialdata);
     void decodeTurboTrans(QByteArray serialdata);
     void decodeVersion(QByteArray serialdata);
     void decodeInit(QByteArray serialdata);
     void decodeBoostCont(QByteArray serialdata);
     void decodeInjOverlap(QByteArray serialdata);
     void decodeInjPriLagvsBattV(QByteArray serialdata);
     void decodeInjScLagvsBattV(QByteArray serialdata);
     void decodeFuelInjectors(QByteArray serialdata);

     void decodeTrailIgn(QByteArray serialdata, quint8 column);
     void decodeLeadIgn(QByteArray serialdata, quint8 column);
     void decodeInjcorr(QByteArray serialdata, quint8 column);
     void decodeFuelBase(QByteArray serialdata, quint8 package);

     //Adaptronic Streaming Comms
     void decodeAdaptronic(QByteArray serialdata);


};




#endif // DECODER_H
