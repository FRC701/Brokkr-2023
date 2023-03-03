// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Chassis.h"
#include <frc/smartdashboard/SmartDashboard.h>

namespace{
    constexpr double kGearRatio{7.35/1};
    constexpr double kTicksInRotation{2048};
    constexpr double kWheelCircumfrence{18.85};
    constexpr double kWheelDiameter{6.};
//    constexpr double kDistancePerTick{(kWheelCircumfrence / kGearRatio) / kTicksInRotation};
    constexpr double kDistancePerTick{0.0012522881};
    constexpr double kTicksPerDistance{798.538};
    
    [[maybe_unused]] 
    double ticksToDistance(double ticks)
    {
        double distance = 0;
        return distance = kDistancePerTick * ticks;
        // .0012522881
    }
    
    double RPMtoMetersPerSec(double rpm)
    {
        return (rpm / 60) * 0.95758;
    }
}
using ControlMode = ctre::phoenix::motorcontrol::ControlMode;
using WPI_TalonFX = ctre::phoenix::motorcontrol::can::WPI_TalonFX;

double Chassis::DistanceToTicks(double distance)
    {
        double ticks = 0;
        return ticks = kTicksPerDistance * distance;
        // .0012522881
    }

Chassis::Chassis(WPI_TalonFX& leftFront, WPI_TalonFX& leftRear, WPI_TalonFX& rightFront, WPI_TalonFX& rightRear)
: mLeftFront(leftFront)
, mLeftRear(leftRear)
, mRightFront(rightFront)
, mRightRear(rightRear)
, mDrive(leftFront, rightFront)
, mOdometry{mGyroX.GetRotation2d(), units::meter_t{0}, units::meter_t{0}}
, mDriveKinematics{units::meter_t{24}}
{
    SetNeutralMode(NeutralMode::Coast);
    
#if ! __APPLE__
    mGyroX.ZeroYaw();
#endif
    mLeftFront.Config_kP(0, 0, 0);
    mLeftFront.Config_kI(0, 0, 0);
    mLeftFront.Config_kD(0, 0, 0);
    mLeftFront.Config_kF(0, 0, 0);

    mRightFront.Config_kP(0, 0, 0);
    mRightFront.Config_kI(0, 0, 0);
    mRightFront.Config_kD(0, 0, 0);
    mRightFront.Config_kF(0, 0, 0);

    mRightFront.SetInverted(true);
    mRightRear.SetInverted(true);

    mLeftRear.Follow(mLeftFront);
    mRightRear.Follow(mRightFront);
    mLeftFront.ConfigOpenloopRamp(0.75);
    mRightFront.ConfigOpenloopRamp(0.75);
}

// This method will be called once per scheduler run
void Chassis::Periodic() {
     mOdometry.Update(mGyroX.GetRotation2d(),
                            units::meter_t{ticksToDistance(EncoderTicksLeft())},
                            units::meter_t{ticksToDistance(EncoderTicksRight())});
    frc::SmartDashboard::PutNumber("Chassis Yaw", GetYawNavX());
    frc::SmartDashboard::PutNumber("Chassis Pitch", GetPitchNavX());
    frc::SmartDashboard::PutNumber("Yaxis", driver.GetY());
    frc::SmartDashboard::PutNumber("Left Front Motor Voltage", mLeftFront.GetMotorOutputVoltage());
    frc::SmartDashboard::PutNumber("Right Front Motor Voltage", mRightFront.GetMotorOutputVoltage());

    double rightTicks = EncoderTicksLeft();
    double leftTicks = EncoderTicksLeft();
    frc::SmartDashboard::PutNumber("Right Distance Ticks", rightTicks);
    frc::SmartDashboard::PutNumber("Right Distance Inches", ticksToDistance(rightTicks));
    frc::SmartDashboard::PutNumber("Left Distance Ticks", leftTicks);
    frc::SmartDashboard::PutNumber("Left Distance Inches", ticksToDistance(leftTicks));
}

void Chassis::TankDriveVoltage(double left, double right)
{
    mLeftFront.SetVoltage(units::volt_t(left));
    mRightFront.SetVoltage(units::volt_t(right));
    mDrive.Feed();
}

double Chassis::GyroTurnRate()
{
    return -mGyroX.GetRate();
}

double Chassis::GetLeftMPS()
{
   return mLeftFront.GetSelectedSensorVelocity(); 
}

double Chassis::GetRightMPS()
{
    return mRightFront.GetSelectedSensorVelocity();
}

frc::DifferentialDriveWheelSpeeds Chassis::GetWheelSpeeds() {
    return {units::meters_per_second_t{RPMtoMetersPerSec(GetLeftMPS())},
            units::meters_per_second_t{RPMtoMetersPerSec(GetRightMPS())}};  
}

units::degree_t Chassis::GetHeading() const
{
    return mGyroX.GetRotation2d().Degrees();
}

void Chassis::SetMaxOutput(double MaxOutput)
{
    mDrive.SetMaxOutput(MaxOutput);
}

void Chassis::ArcadeDrive(double speed, double rotation) 
{
    mDrive.ArcadeDrive(speed, rotation);
}

frc::Pose2d Chassis::GetPose()
{
    return mOdometry.GetPose();
}

void Chassis::ResetOdometry(frc::Pose2d pose)
{
    mOdometry.ResetPosition(mGyroX.GetRotation2d(),
                            units::meter_t{ticksToDistance(EncoderTicksLeft())},
                            units::meter_t{ticksToDistance(EncoderTicksRight())},
                            pose);
}

double Chassis::GetYawNavX() {
#if ! __APPLE__
   return mGyroX.GetYaw();
#else
    return 0;
#endif
 }

double Chassis::GetPitchNavX() {
#if ! __APPLE__
    return mGyroX.GetPitch();
#else
    return 0;
#endif
 }

double Chassis::EncoderTicksLeft() 
{
    double Ticks = 0;
    return Ticks = mLeftFront.GetSelectedSensorPosition();
}

double Chassis::EncoderTicksRight()
{
    double Ticks = 0;
    return Ticks = mRightFront.GetSelectedSensorPosition();
}

void Chassis::SetNeutralMode(NeutralMode mode)
{
    mLeftFront.SetNeutralMode(mode);
    mLeftRear.SetNeutralMode(mode);
    mRightFront.SetNeutralMode(mode);
    mRightRear.SetNeutralMode(mode);
}