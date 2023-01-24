// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Arm.h"
#include "frc/smartdashboard/SmartDashboard.h"

namespace
{
    template <typename T>
    bool inRange(const T upper, const T lower, const T value)
    {
        return (value >= lower && value < upper);
    }
}

Arm::Arm(WPI_TalonFX& armM1, WPI_TalonFX& armM2, WPI_TalonFX& teleArm, WPI_CANCoder& canCoder)
: mArmMotor1(armM1)
, mArmMotor2(armM2)
, mTelescopingArm(teleArm)
, mCanCoder(canCoder)
{
    mArmMotor1.Follow(mArmMotor2);
    mArmMotor2.Config_kP(0, 0, 0);
    mArmMotor2.Config_kI(0, 0, 0);
    mArmMotor2.Config_kD(0, 0, 0);
}
// This method will be called once per scheduler run
void Arm::Periodic()
{
    frc::SmartDashboard::PutString("ArmHeightStatus", AsString(GetArmStatus()));
    frc::SmartDashboard::PutNumber("ArmAngle", CANCoderArmStatus());
}

double Arm::ArmExtend(double pose)
{
    mTelescopingArm.Set(ControlMode::Position, pose);
    return pose;
}

double Arm::SetArmHeight(double pose)
{
    mArmMotor2.Set(ControlMode::Position, pose);
    return pose;
}

double Arm::CANCoderArmStatus()
{
    return mCanCoder.GetAbsolutePosition();
}

Arm::eArmStatus Arm::GetArmStatus()
{
    double position = mArmMotor2.GetSelectedSensorPosition();

    const double kHighLowLimit    = 150.0;
    const double kHighHighLimit   = 160.0;
    const double kMidLowLimit     =  90.0;
    const double kMidHighLimit    = 100.0;
    const double kHybridLowLimit  =  40.0;
    const double kHybridHighLimit =  50.0;

    eArmStatus status { UNKNOWN };
    if (inRange(kHighLowLimit, kHighHighLimit, position))
    {
        status = HIGH;
    }
    else if(inRange(kMidLowLimit, kMidHighLimit, position))
    {
        status = MID;
    }
    else if(inRange(kHybridLowLimit, kHybridHighLimit, position))
    {
        status = HYBRID;
    }
 
    return status;
}

const char* Arm::AsString(const eArmStatus status)
{
    const char* armStatus[3] {"High", "Mid", "Hybrid"};

    switch (status)
    {
        case HIGH:
            return armStatus[0];
            break;
        case MID:
            return armStatus[1];
            break;
        case HYBRID:
            return armStatus[2];
            break;
        default:
            return "error not aligned";
    }
}

