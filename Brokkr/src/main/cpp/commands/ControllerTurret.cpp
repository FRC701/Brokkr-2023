// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ControllerTurret.h"

ControllerTurret::ControllerTurret(Turret& turret) 
: mTurret(turret)
, controllerTrrt{0.1, 0, 0}
{
  AddRequirements(&mTurret);
}

// Called when the command is initially scheduled.
void ControllerTurret::Initialize() 
{
  controllerTrrt.SetTolerance(1);
}

// Called repeatedly when this Command is scheduled to run
void ControllerTurret::Execute() 
{
  double output = controllerTrrt.Calculate(mTurret.GetVisionYaw(), 0);
  mTurret.SetTurretSpeed(output);
}

// Called once the command ends or is interrupted.
void ControllerTurret::End(bool interrupted) 
{
  mTurret.SetTurretSpeed(0);
}

// Returns true when the command should end.
bool ControllerTurret::IsFinished() {
  return controllerTrrt.AtSetpoint();
}
