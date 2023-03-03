// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "frc/smartdashboard/SmartDashboard.h"

#include "commands/GetIntakeSpin.h"

GetIntakeSpin::GetIntakeSpin(Claw& claw)
: mClaw(claw)
, mIsInRushOver(false) 
, mCouldBeStalled(false)
, mIsMotorStalling(false)

{
  AddRequirements(&mClaw);
}

// Called when the command is initially scheduled.
void GetIntakeSpin::Initialize() 
{
  mIsInRushOver = false;
  mCouldBeStalled = false;
  mIsMotorStalling = false;
  mTimer.Reset();
  mTimer.Start();
}

// Called repeatedly when this Command is scheduled to run
void GetIntakeSpin::Execute() 
{
  static const units::second_t kInrushTimer{1};

  double IntakeCurrentLimit = frc::SmartDashboard::GetNumber("IntakeCurrentLimit", 0);
  mClaw.IntakeSpin(3);
  if (mIsInRushOver)
  {
    if(mClaw.IsConeOrCubeIn(IntakeCurrentLimit))
    {
      if (mCouldBeStalled)
      {
        if (mTimer.HasElapsed(units::millisecond_t(300)))
        {
          mIsMotorStalling = true;
          mTimer.Stop();
          mTimer.Reset();
        }
      }
      else
      {
        mTimer.Start();
        mCouldBeStalled = true;
      }
    }
    else
    {
      mCouldBeStalled = false;
    }
  }
  else
  {
    if (mTimer.HasElapsed(kInrushTimer))
    {
      mIsInRushOver = true;
      mTimer.Stop();
      mTimer.Reset();
    }
  }
}

// Called once the command ends or is interrupted.
void GetIntakeSpin::End(bool interrupted) 
{
  mClaw.IntakeSpin(0);
  mTimer.Stop();
  mTimer.Reset();
}

// Returns true when the command should end.
bool GetIntakeSpin::IsFinished() 
{
  return mIsMotorStalling;
}
