#include "decoder_adaptronic.h"
#include <QDebug>
#include <QBitArray>
/*
QByteArray serialdata;





DecoderAdaptronic::DecoderAdaptronic(QObject *parent)
    : QObject(parent)
    , m_dashboard(Q_NULLPTR)
{
}

DecoderAdaptronic::DecoderAdaptronic(DashBoard *dashboard, QObject *parent)
    : QObject(parent)
    , m_dashboard(dashboard)
{
}


    void DecoderAdaptronic::decodeAdaptronic(QByteArray serialdata)
    {
        Adaptronic_Streaming_coms* info=reinterpret_cast<Adaptronic_Streaming_coms*>(serialdata.data());

        packageAdaptronic[0] = info->RPM;
        packageAdaptronic[1] = info->MAP;
        packageAdaptronic[2] = info->MAT;
        packageAdaptronic[3] = info->WT;
        packageAdaptronic[4] = info->AuxT;
        packageAdaptronic[5] = info->AFR;
        packageAdaptronic[6] = info->KnockValue;
        packageAdaptronic[7] = info->TPS;
        packageAdaptronic[8] = info->IdleValue;
        packageAdaptronic[9] = info->Battery;
        packageAdaptronic[10] = info->MVSS;
        packageAdaptronic[11] = info->SVSS;
        packageAdaptronic[12] = info->Inj1;
        packageAdaptronic[13] = info->Inj2;
        packageAdaptronic[12] = info->Inj3;
        packageAdaptronic[13] = info->Inj4;
        packageAdaptronic[14] = info->Ign1;
        packageAdaptronic[15] = info->Ign2;
        packageAdaptronic[16] = info->Ign3;
        packageAdaptronic[17] = info->Ign4;
        packageAdaptronic[18] = info->Trim;
        packageAdaptronic[19] = info->Updates1;
        packageAdaptronic[20] = info->Updates2;
        packageAdaptronic[21] = info->Updates3;
        packageAdaptronic[22] = info->Updates4;
        packageAdaptronic[23] = info->Updates5;
        packageAdaptronic[24] = info->Updates6;
        packageAdaptronic[25] = info->Updates7;
        packageAdaptronic[26] = info->Updates8;
        packageAdaptronic[27] = info->Updates9;
        packageAdaptronic[28] = info->Updates10;
        packageAdaptronic[29] = info->Updates11;
        packageAdaptronic[30] = info->Updates12;
        packageAdaptronic[31] = info->Updates13;
        packageAdaptronic[32] = info->Updates14;
        packageAdaptronic[33] = info->Updates15;
        packageAdaptronic[34] = info->Updates16;
        packageAdaptronic[35] = info->Updates17;
        packageAdaptronic[36] = info->Updates18;
        packageAdaptronic[37] = info->Updates19;
        packageAdaptronic[38] = info->dTPSdt;
        packageAdaptronic[39] = info->dMAPdt;
        packageAdaptronic[40] = info->TargetIdle;
        packageAdaptronic[41] = info->TargetMAP;
        packageAdaptronic[42] = info->TargetAFR;
        packageAdaptronic[43] = info->BOVStateGear;
        packageAdaptronic[44] = info->CuttingState;
        packageAdaptronic[45] = info->Flags;
        packageAdaptronic[46] = info->DigIns;
        packageAdaptronic[47] = info->DigOuts;
        packageAdaptronic[48] = info->LearningState;
        packageAdaptronic[49] = info->RawFuelMapValue;
        packageAdaptronic[50] = info->RawIgnMapValue;
        packageAdaptronic[51] = info->MainLoopSpeed;
        packageAdaptronic[52] = info->SecSerialPortStatus;
        packageAdaptronic[53] = info->WastegateDCRaw;
        packageAdaptronic[54] = info->WastegateDCFinal;
        packageAdaptronic[55] = info->ADCChan0;
        packageAdaptronic[56] = info->ADCChan1;
        packageAdaptronic[57] = info->ADCChan2;
        packageAdaptronic[58] = info->ADCChan3;
        packageAdaptronic[59] = info->ADCChan4;
        packageAdaptronic[60] = info->ADCChan5;
        packageAdaptronic[61] = info->ADCChan6;
        packageAdaptronic[62] = info->ADCChan7;
        packageAdaptronic[63] = info->ADCChan8;
        packageAdaptronic[64] = info->ADCChan9;
        packageAdaptronic[65] = info->ADCChan10;
        packageAdaptronic[66] = info->ADCChan11;
        packageAdaptronic[67] = info->ADCChan12;
        packageAdaptronic[68] = info->ADCChan13;
        packageAdaptronic[69] = info->ADCChan14;
        packageAdaptronic[70] = info->ADCChan15;
        packageAdaptronic[71] = info->ADCChan16;
        packageAdaptronic[72] = info->ADCChan17;
        packageAdaptronic[73] = info->ADCChan18;
        packageAdaptronic[74] = info->Serial_number_0_1;
        packageAdaptronic[75] = info->Serial_number_2_3;
        packageAdaptronic[76] = info->Serial_number_4_5;
        packageAdaptronic[77] = info->Serial_number_6_7;
        packageAdaptronic[78] = info->Serial_number_8_9;
        packageAdaptronic[79] = info->Serial_number_10_11;
        packageAdaptronic[80] = info->Serial_number_12_13;
        packageAdaptronic[81] = info->Serial_number_14_15;
        packageAdaptronic[82] = info->Serial_number_16_17;
        packageAdaptronic[83] = info->Serial_number_18_19;
        packageAdaptronic[84] = info->Serial_number_20_21;
        packageAdaptronic[85] = info->Serial_number_22_23;
        packageAdaptronic[86] = info->VVT1_1;
        packageAdaptronic[87] = info->AsyncPump;
        packageAdaptronic[88] = info->MasterVSSDiff;
        packageAdaptronic[89] = info->SlaveVSSDiff;
        packageAdaptronic[90] = info->MVSS1Raw;
        packageAdaptronic[91] = info->SVSS1Raw;
        packageAdaptronic[92] = info->MVSS2Raw;
        packageAdaptronic[93] = info->SVSS2Raw;
        packageAdaptronic[94] = info->VVT2;
        packageAdaptronic[95] = info->VVT1;
        packageAdaptronic[96] = info->VVT2Set;
        packageAdaptronic[97] = info->VVT1Set;
        packageAdaptronic[98] = info->ExtIn;
        packageAdaptronic[99] = info->EGT1;
        packageAdaptronic[100] = info->EGT2;
        packageAdaptronic[101] = info->EGT3;
        packageAdaptronic[102] = info->DigInRaw_inj_test1;
        packageAdaptronic[103] = info->RTInRaw_inj_test2;
        packageAdaptronic[104] = info->AuxOut_override;
        packageAdaptronic[105] = info->EGT4;
        packageAdaptronic[106] = info->LED_output_override;
        packageAdaptronic[107] = info->Actual_Dwell_time;
        packageAdaptronic[108] = info->FW_Version;
        packageAdaptronic[109] = info->Actual_ECU_ID;
        packageAdaptronic[110] = info->Flex_fuel_1;
        packageAdaptronic[111] = info->Flex_fuel_2;
        packageAdaptronic[112] = info->MOP;
        packageAdaptronic[113] = info->CrankInt;
        packageAdaptronic[114] = info->Diginputs_2;
        packageAdaptronic[115] = info->Ignition_Cut;
        packageAdaptronic[116] = info->Slip;
        packageAdaptronic[117] = info->Oil_pressure_kPa;
        packageAdaptronic[118] = info->Fuel_pressure_kPa;
        packageAdaptronic[119] = info->Ch1_0_5V;
        packageAdaptronic[120] = info->Aux_pressure_kPa;
        packageAdaptronic[121] = info->Safety_cut_functions;
        packageAdaptronic[122] = info->Injection_angle;
        packageAdaptronic[123] = info->CRC16;



    }


*/
