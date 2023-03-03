// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/SetNeutralModeToBrake.h"

SetNeutralModeToBrake::SetNeutralModeToBrake(Chassis& chassis) 
: mChassis(chassis)
{
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void SetNeutralModeToBrake::Initialize() 
{
  mChassis.SetNeutralMode(NeutralMode::Brake);
}

// Called repeatedly when this Command is scheduled to run
void SetNeutralModeToBrake::Execute() {}

// Called once the command ends or is interrupted.
void SetNeutralModeToBrake::End(bool interrupted) 
{
  mChassis.SetNeutralMode(NeutralMode::Coast);
}

// Returns true when the command should end.
bool SetNeutralModeToBrake::IsFinished() {
  return false;
}
