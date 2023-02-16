// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "frc/smartdashboard/SmartDashboard.h"

#include "commands/GetIntakeSpin.h"

GetIntakeSpin::GetIntakeSpin(Claw& claw)
: mClaw(claw) 
{
  AddRequirements(&mClaw);
}

// Called when the command is initially scheduled.
void GetIntakeSpin::Initialize() 
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
void GetIntakeSpin::Execute() 
{
  double IntakeCurrentLimit = frc::SmartDashboard::GetNumber("IntakeCurrentLimit", 0);
  mClaw.IntakeSpin(1);
  if (mIsInRushOver)
  {
    if(mClaw.IsConeOrCubeIn(IntakeCurrentLimit)) //placeholder
    {
      mTimer.Start();
      if (mTimer.HasElapsed(units::millisecond_t(300)) && mClaw.IsConeOrCubeIn(IntakeCurrentLimit))
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
void GetIntakeSpin::End(bool interrupted) 
{
  mClaw.IntakeSpin(0);
  mTimer.Stop();
  mTimer.Reset();
}

// Returns true when the command should end.
bool GetIntakeSpin::IsFinished() 
{
  return false || mIsMotorStalling;
}
