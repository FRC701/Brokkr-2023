// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Arm.h"
#include "frc/smartdashboard/SmartDashboard.h"

using namespace std::numbers;
namespace
{
    constexpr double kArmGearRatioExtension(16/24);
    constexpr double kTicksInRotation(2048);
    constexpr double kArmCircumfrence(3 * pi); //9.42
    constexpr double kDistancePerTick{(kArmCircumfrence * kArmGearRatioExtension) / kTicksInRotation};

    double ticksToArmDistance(double ticks)
    {
        double distance = 0;
        return distance = kDistancePerTick * ticks;
    }

    double armDistanceToTicks(double distance)
    {
        double ticks = 0;
        return ticks = distance / kDistancePerTick;
    }

    template <typename T>
    bool inRange(const T upper, const T lower, const T value)
    {
        return (value >= lower && value < upper);
    }
    const double kArmAngle_P = 10.0;
    const double kArmAngle_I = 0;
    const double kArmAngle_D = 0;
    const double kArmExtend_P = 3.0;
    const double kArmExtend_I = 0;
    const double kArmExtend_D = 0;
}


Arm::Arm(
        WPI_TalonFX& armM2,
        WPI_TalonFX& teleArm, WPI_CANCoder& canCoder
)
: mArmMotor2(armM2)
, mTelescopingArm(teleArm)
, mCanCoder(canCoder)
{
    mArmMotor2.SetNeutralMode(Brake);
    mTelescopingArm.SetNeutralMode(Brake);

    mArmMotor2.Config_kP(0, kArmAngle_P);
    mArmMotor2.Config_kI(0, kArmAngle_I);
    mArmMotor2.Config_kD(0, kArmAngle_D);
    mTelescopingArm.SetNeutralMode(Brake);
    mTelescopingArm.Config_kP(0, kArmExtend_P);
    mTelescopingArm.Config_kI(0, kArmExtend_I);
    mTelescopingArm.Config_kD(0, kArmExtend_D);
    mCanCoder.ConfigAbsoluteSensorRange(ctre::phoenix::sensors::AbsoluteSensorRange::Unsigned_0_to_360);
    mCanCoder.ConfigMagnetOffset(9);
}
// This method will be called once per scheduler run
void Arm::Periodic()
{
    frc::SmartDashboard::PutString("ArmHeightStatus", AsString(GetArmStatus()));
    frc::SmartDashboard::PutNumber("ArmAngleStatus", CANCoderArmStatus());
    frc::SmartDashboard::PutNumber("ArmDistance", ticksToArmDistance(GetExtendTicks()));

    frc::SmartDashboard::PutBoolean("ArmExtensionMaxLimitSwitch", ArmMaxLimitSwitch());
    frc::SmartDashboard::PutBoolean("ArmExtensionMinLimitSwitch", ArmMinLimitSwitch());
    frc::SmartDashboard::PutBoolean("ArmUpAndDownMaxLimitSwitch", PivotMaxLimitSwitch());
    frc::SmartDashboard::PutBoolean("ArmUpAndDownMinLimitSwitch", PivotMinLimitSwitch());
}
double Arm::DistanceToTicks(double distance)
{
    return armDistanceToTicks(distance);
}

double Arm::GetExtendTicks()
{
    return mTelescopingArm.GetSelectedSensorPosition();
}

double Arm::GetArmSpeed()
{
    return mArmMotor2.Get();
}

double Arm::ArmExtend(double speed)
{
    mTelescopingArm.Set(speed);
    return speed;
}

double Arm::SetArmSpeed(double speed)
{
    mArmMotor2.Set(ControlMode::PercentOutput, speed);
    return speed;
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

bool Arm::ArmMaxLimitSwitch()
{
    return mTelescopingArm.IsFwdLimitSwitchClosed();
}

bool Arm::ArmMinLimitSwitch()
{
    return mTelescopingArm.IsRevLimitSwitchClosed();
}
bool Arm::PivotMaxLimitSwitch()
{
    return mArmMotor2.IsFwdLimitSwitchClosed();
}

bool Arm::PivotMinLimitSwitch()
{
    return mArmMotor2.IsRevLimitSwitchClosed();
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

