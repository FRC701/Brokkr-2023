// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Claw.h"
#include <frc/smartdashboard/SmartDashboard.h>

Claw::Claw(WPI_TalonFX& clawMotor, WPI_TalonFX& intakeMotor)
: mClawMotor(clawMotor)
, mIntakeMotor(intakeMotor)
{
    mClawMotor.SetInverted(false);
    mClawMotor.Config_kP(0, 0, 0);
    mClawMotor.Config_kI(0, 0, 0);
    mClawMotor.Config_kD(0, 0, 0);
    mClawMotor.Config_kF(0, 0, 0);
    mIntakeMotor.SetNeutralMode(Brake);
}

void Claw::Periodic() 
{
    frc::SmartDashboard::PutBoolean("Is Claw Open", IsClawOpen());
}

bool Claw::IsClawOpen() const
{
    const double kClawOpenLimit = 100;
    return mClawMotor.GetSelectedSensorPosition() >= kClawOpenLimit;
}

bool Claw::IsConeOrCubeIn() 
{
    const double kCurrentThreshold = 0;
    return mIntakeMotor.GetStatorCurrent() >= kCurrentThreshold;
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