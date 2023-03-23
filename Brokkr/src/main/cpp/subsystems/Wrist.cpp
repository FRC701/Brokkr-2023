// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Wrist.h"
#include <frc/smartdashboard/SmartDashboard.h>

namespace
{
  const double kWrist_P = 0.0;
  const double kWrist_I = 0.0;
  const double kWrist_D = 0.0;
  const double kWrist_F = 0.0;
}

Wrist::Wrist(WPI_TalonFX& wristMotor, WPI_CANCoder& wristCoder)
: mWristMotor(wristMotor)
, mWristCoder(wristCoder)
{
    mWristMotor.SetInverted(false);
    mWristMotor.ConfigPeakOutputForward(0.3);
    mWristMotor.ConfigPeakOutputReverse(-0.3);
    mWristMotor.SetNeutralMode(Brake);
    mWristMotor.ConfigOpenloopRamp(0.5);
    mWristMotor.Config_kP(0, kWrist_P);
    mWristMotor.Config_kI(0, kWrist_I);
    mWristMotor.Config_kD(0, kWrist_D);
    mWristMotor.Config_kF(0, kWrist_F);
    mWristCoder.ConfigAbsoluteSensorRange(ctre::phoenix::sensors::AbsoluteSensorRange::Signed_PlusMinus180);
    mWristCoder.ConfigMagnetOffset(-100);
    mWristCoder.ConfigSensorDirection(false);
}
// This method will be called once per scheduler run
void Wrist::Periodic()  
{
    frc::SmartDashboard::PutNumber("WristCancoder", GetWristPosition());
    frc::SmartDashboard::PutNumber("WristCancoder1", GetWristPosition());
    frc::SmartDashboard::PutBoolean("IsWristFlicked", IsWristFlicked());
    frc::SmartDashboard::PutBoolean("WristMaxLimitSwitch", WristMaxLimitSwitch());
    frc::SmartDashboard::PutBoolean("WristMinLimitSwitch", WristMinLimitSwitch());
}

double Wrist::TurnWrist(double pos) 
{
    mWristMotor.Set(ControlMode::Position, pos);
    return pos;
}

bool Wrist::IsWristFlicked() const 
{
    const double kWristFlickedLimit{ 100 }; // placeholder
    return mWristMotor.GetSelectedSensorPosition() <= kWristFlickedLimit;
}

double Wrist::GetWristPosition()
{
    return mWristCoder.GetAbsolutePosition();
}

double Wrist::TurnWristPO(double speed)
{
    mWristMotor.SetVoltage(units::volt_t(speed));
    return speed;
}

bool Wrist::WristMaxLimitSwitch()
{
    return mWristMotor.IsFwdLimitSwitchClosed();
}

bool Wrist::WristMinLimitSwitch()
{
    return mWristMotor.IsRevLimitSwitchClosed();
}
