// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/RunTurret.h"

RunTurret::RunTurret(Turret& turret, double motorSpeed)
: mTurret(turret)
, mMotorSpeed(motorSpeed)
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(&mTurret);
}

// Called when the command is initially scheduled.
void RunTurret::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunTurret::Execute() 
{
  mTurret.SetTurretSpeed(mMotorSpeed);
}

// Called once the command ends or is interrupted.
void RunTurret::End(bool interrupted) {
  mTurret.SetTurretSpeed(0);
}

// Returns true when the command should end.
bool RunTurret::IsFinished() {
  return false;
}
