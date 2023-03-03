// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/IntakeSpin.h"

IntakeSpin::IntakeSpin(Claw& claw, double speed)
: mHelper(claw, speed) 
{
}

// Called when the command is initially scheduled.
void IntakeSpin::Initialize() 
{
  mHelper.Initialize();
}

// Called repeatedly when this Command is scheduled to run
void IntakeSpin::Execute() 
{
  mHelper.Execute();
}

// Called once the command ends or is interrupted.
void IntakeSpin::End(bool interrupted) 
{
  mHelper.End(interrupted);
}

// Returns true when the command should end.
bool IntakeSpin::IsFinished() 
{
  return mHelper.IsFinished();
}
