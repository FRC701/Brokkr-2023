// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Wrist.h"
#include <frc/smartdashboard/SmartDashboard.h>

Wrist::Wrist(WPI_TalonFX& wristMotor)
: mWristMotor(wristMotor)
{
    mWristMotor.Config_kP(0, 0, 0);
    mWristMotor.Config_kI(0, 0, 0);
    mWristMotor.Config_kD(0, 0, 0);
    mWristMotor.Config_kF(0, 0, 0);
}
// This method will be called once per scheduler run
void Wrist::Periodic() 
{
    frc::SmartDashboard::PutBoolean("IsWristFlicked", IsWristFlicked());
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
