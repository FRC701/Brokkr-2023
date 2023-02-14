// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoBalance.h"

AutoBalance::AutoBalance(Chassis& chassis)
: mChassis(chassis)
, control{0, 0, 0}
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(&mChassis);
}

// Called when the command is initially scheduled.
void AutoBalance::Initialize() {
  control.SetTolerance(0.1);
}

// Called repeatedly when this Command is scheduled to run
void AutoBalance::Execute() 
{
  double output = control.Calculate(mChassis.GetPitchNavX(), 0);
  mChassis.ArcadeDrive(output, 0);
}

// Called once the command ends or is interrupted.
void AutoBalance::End(bool interrupted) {
  mChassis.ArcadeDrive(0, 0);
}

// Returns true when the command should end.
bool AutoBalance::IsFinished() {
  return control.AtSetpoint();
}
