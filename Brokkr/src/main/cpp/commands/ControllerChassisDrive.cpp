// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ControllerChassisDrive.h"

ControllerChassisDrive::ControllerChassisDrive(Chassis& chassis, Turret& turret)
: mChassis(chassis)
, mTurret(turret)
, controllerChassisDr{0.1, 0, 0} 
{
  AddRequirements(&mChassis);
}

// Called when the command is initially scheduled.
void ControllerChassisDrive::Initialize() 
{
  controllerChassisDr.SetTolerance(1);
}

// Called repeatedly when this Command is scheduled to run
void ControllerChassisDrive::Execute() 
{
  double output = controllerChassisDr.Calculate(mTurret.GetVisionArea(), 100);
  mChassis.ArcadeDrive(output, 0);
}

// Called once the command ends or is interrupted.
void ControllerChassisDrive::End(bool interrupted) 
{
  mChassis.ArcadeDrive(0, 0);
}

// Returns true when the command should end.
bool ControllerChassisDrive::IsFinished() {
  return controllerChassisDr.AtSetpoint();
}
