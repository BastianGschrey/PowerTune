#include "adaptronic_decoder.h"
#include <QDebug>
#include <QBitArray>



adaptronic_decoder::adaptronic_decoder()
{

}


/*void adaptronic_decoder::decodeAdaptronic(QByteArray serialdata)
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
}*/
