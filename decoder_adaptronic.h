/*
#ifndef DECODER_ADAPTRONIC_H
#define DECODER_ADAPTRONIC_H

#include <QObject>

class DashBoard;

class DecoderAdaptronic : public QObject
{
    Q_OBJECT

private:

//Multipication and Addition values used to process the message  from raw to human readable format
#define Adaptronic_MUL		{1,}
#define Adaptronic_ADD		{0,}



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
quint16 Flex_fuel_2;
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

;
public:
    explicit DecoderAdaptronic(QObject *parent = 0);
     explicit DecoderAdaptronic(DashBoard *dashboard, QObject *parent = 0);

private:
     DashBoard *m_dashboard;

public slots:
     void decodeAdaptronic(QByteArray serialdata);


};

#endif // DECODER_ADAPTRONIC_H

*/
