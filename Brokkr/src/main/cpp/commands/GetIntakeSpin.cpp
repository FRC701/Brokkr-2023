// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "frc/smartdashboard/SmartDashboard.h"

#include "commands/GetIntakeSpin.h"

GetIntakeSpin::GetIntakeSpin(Claw& claw)
: mHelper(claw)
{
  AddRequirements(&claw);
}

// Called when the command is initially scheduled.
void GetIntakeSpin::Initialize() 
{
  mHelper.Initialize();
}

// Called repeatedly when this Command is scheduled to run
void GetIntakeSpin::Execute() 
{
  mHelper.Execute();
}

// Called once the command ends or is interrupted.
void GetIntakeSpin::End(bool interrupted) 
{
  mHelper.End(interrupted);
}

// Returns true when the command should end.
bool GetIntakeSpin::IsFinished() 
{
  return mHelper.IsFinished();
}
