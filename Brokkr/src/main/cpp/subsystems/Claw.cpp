// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Claw.h"
#include <frc/smartdashboard/SmartDashboard.h>

Claw::Claw( WPI_TalonFX& intakeMotor)
: mIntakeMotor(intakeMotor)
{
    mIntakeMotor.SetNeutralMode(Brake);
}

void Claw::Periodic() 
{
    frc::SmartDashboard::PutBoolean("Is Claw Open", IsClawOpen());
    frc::SmartDashboard::PutNumber("IntakeStator", mIntakeMotor.GetStatorCurrent());
}

bool Claw::IsClawOpen() const
{
    const double kClawOpenLimit = 100;
    return mIntakeMotor.GetSelectedSensorPosition() >= kClawOpenLimit;
}

bool Claw::IsConeOrCubeIn(double CurrentThreshold) 
{
    return mIntakeMotor.GetStatorCurrent() >= CurrentThreshold;
}

double Claw::IntakeSpin(double speed)
{
    mIntakeMotor.Set(ControlMode::PercentOutput, speed);
    return speed;
}

double Claw::GetControllerCurrent()
{
    return mIntakeMotor.GetStatorCurrent();
}