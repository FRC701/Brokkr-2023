// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TurretManualControl.h"

TurretManualControl::TurretManualControl(Turret& turret, double rpm) 
: mTurret(turret)
, rpm(rpm)
{
  AddRequirements(&turret);
}

// Called when the command is initially scheduled.
void TurretManualControl::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TurretManualControl::Execute() 
{
  mTurret.SetVelocity(rpm);
}

// Called once the command ends or is interrupted.
void TurretManualControl::End(bool interrupted) {}

// Returns true when the command should end.
bool TurretManualControl::IsFinished() {
  return false;
}
