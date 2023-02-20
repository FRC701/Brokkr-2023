// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/IntakeSpin.h"

IntakeSpin::IntakeSpin(Claw& claw, double speed)
: mClaw(claw) 
, mSpeed(speed)
{
  AddRequirements(&mClaw);
}

// Called when the command is initially scheduled.
void IntakeSpin::Initialize() 
{
    static const units::second_t kInrushTimer{2};

  mTimer.Start();
  if (mTimer.HasElapsed(kInrushTimer))
  {
    mIsInRushOver = true;
    mTimer.Stop();
    mTimer.Reset();
  }
}

// Called repeatedly when this Command is scheduled to run
void IntakeSpin::Execute() 
{
  mClaw.IntakeSpin(mSpeed);
  if (mIsInRushOver)
  {
    if(mClaw.IsConeOrCubeIn(100)) //placeholder
    {
      mTimer.Start();
      if (mTimer.HasElapsed(units::millisecond_t(300)) && mClaw.IsConeOrCubeIn(100))
      {
        mIsMotorStalling = true;
      }
      else
      {
        mTimer.Stop();
        mTimer.Reset();
      }
    }
    else
    {
      mTimer.Stop();
      mTimer.Reset();
    }
  }
}

// Called once the command ends or is interrupted.
void IntakeSpin::End(bool interrupted) 
{
  mClaw.IntakeSpin(0);
  mTimer.Stop();
  mTimer.Reset();
}

// Returns true when the command should end.
bool IntakeSpin::IsFinished() 
{
  return false || mIsMotorStalling;
}
