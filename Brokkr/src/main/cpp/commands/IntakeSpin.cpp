// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/IntakeSpin.h"

IntakeSpin::IntakeSpin(Claw& claw)
: mClaw(claw) 
{
  AddRequirements(&mClaw);
}

// Called when the command is initially scheduled.
void IntakeSpin::Initialize() 
{
  mTimer.Reset();
  mTimer.Start();
}

// Called repeatedly when this Command is scheduled to run
void IntakeSpin::Execute() 
{
  mClaw.IntakeSpin(0.5);
}

// Called once the command ends or is interrupted.
void IntakeSpin::End(bool interrupted) 
{
  mClaw.IntakeSpin(0);
  mTimer.Stop();
}

// Returns true when the command should end.
bool IntakeSpin::IsFinished() 
{
  static const units::second_t kSpinTime{5};
  return mTimer.HasElapsed(kSpinTime);
}
