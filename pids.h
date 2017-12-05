#ifndef PIDS_H
#define PIDS_H

#include <QByteArray>

class PIDs
{
public:
    PIDs():
        MODE01("01"),
        MODE02("02"),
        MODE03("03"),
        MODE04("04"),
        MODE07("07"),
        MODE08("08"),
        MODE09("09"),
        MODE0A("0A"),
        Status_Since_DTC_Cleared("01"),
        FreezeDTC("02"),
        FuelTankLevel("2F"),
        EngineLoad("04"),
        EngineCoolantTemp("05"),
        FuelPressure("0A"),
        IntakeManifoldAbsPressure("0B"),
        RPM("0C"),
        Speed("0D"),
        IntakeAirTemp("0F"),
        ThrottlePosition("11"),
        AuxStatus("1E"),
        EngineStartRuntime("1F")
        {}

    //gets ECU data https://en.wikipedia.org/wiki/OBD-II_PIDs
    QByteArray getMODE01CurrentData(){
        return MODE01;
    }

    QByteArray getMODE02FreezeFrameData(){
        return MODE02;
    }
    //checks for trouble codes
    QByteArray getMODE03TROUBLECODES(){
        return MODE03;
    }

    QByteArray getMODE04ClrCodesAndStored(){
        return MODE04;
    }
    //Show pending Diagnostic Trouble Codes
    QByteArray getMODE07PendingCodes(){
        return MODE07;
    }

    QByteArray getMODE08ControlOnboardOps(){
        return MODE08;
    }

    QByteArray getMODE09VehicleInformation(){
        return MODE09;
    }

    QByteArray getMODE0APermanentCodes(){
        return MODE0A;
    }

    QByteArray getStatus_Since_DTC_Cleared(){
        return Status_Since_DTC_Cleared;
    }

    QByteArray getFreezeDTC(){
        return FreezeDTC;
    }

    QByteArray getFuelTankLevel(){
        return FuelTankLevel;
    }

    QByteArray getEngineLoad(){
        return EngineLoad;
    }

    QByteArray getEngineCoolantTemp(){
        return EngineCoolantTemp;
    }

    QByteArray getFuelPressure(){
        return FuelPressure;
    }

    QByteArray getIntakeManifoldAbsPressure(){
        return IntakeManifoldAbsPressure;
    }

    QByteArray getRPM(){
        return RPM;
    }

    QByteArray getSpeed(){
        return Speed;
    }

    QByteArray getIntakeAirTemp(){
        return IntakeAirTemp;
    }

    QByteArray getThrottlePosition(){
        return ThrottlePosition;
    }

    QByteArray getAuxStatus(){
        return AuxStatus;
    }

    QByteArray getEngineStartRunTime(){
        return EngineStartRuntime;
    }

private:

    QByteArray MODE01;
    QByteArray MODE02;
    QByteArray MODE03;
    QByteArray MODE04;
    QByteArray MODE07;
    QByteArray MODE08;
    QByteArray MODE09;
    QByteArray MODE0A;

    QByteArray Status_Since_DTC_Cleared;
    QByteArray FreezeDTC;
    QByteArray FuelTankLevel;
    QByteArray EngineLoad;
    QByteArray EngineCoolantTemp;
    QByteArray FuelPressure;
    QByteArray IntakeManifoldAbsPressure;
    QByteArray RPM;
    QByteArray Speed;
    QByteArray IntakeAirTemp;
    QByteArray ThrottlePosition;
    QByteArray AuxStatus;
    QByteArray EngineStartRuntime;

};

#endif // PIDS_H
