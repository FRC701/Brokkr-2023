// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "frc/smartdashboard/SmartDashboard.h"

#include "commands/IntakeSpinHelper.h"

IntakeSpinHelper::IntakeSpinHelper(Claw& claw)
: mClaw(claw)
, mIsInRushOver(false) 
, mCouldBeStalled(false)
, mIsMotorStalling(false)
{
}

// Called when the command is initially scheduled.
void IntakeSpinHelper::Initialize() 
{
  mIsInRushOver = false;
  mCouldBeStalled = false;
  mIsMotorStalling = false;
  mTimer.Reset();
  mTimer.Start();
}

// Called repeatedly when this Command is scheduled to run
void IntakeSpinHelper::Execute() 
{
  static const units::second_t kInrushTimer{1};

  double IntakeCurrentLimit = GetCurrentLimit();
  mClaw.IntakeSpin(GetMotorSpeed());
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
void IntakeSpinHelper::End(bool interrupted) 
{
  mClaw.IntakeSpin(0);
  mTimer.Stop();
  mTimer.Reset();
}

// Returns true when the command should end.
bool IntakeSpinHelper::IsFinished() 
{
  return mIsMotorStalling;
}

double IntakeSpinHelper::GetCurrentLimit()
{
  double IntakeCurrentLimit = frc::SmartDashboard::GetNumber("IntakeCurrentLimit", 0);
  return IntakeCurrentLimit;
}

double IntakeSpinHelper::GetMotorSpeed()
{
  return 3.0;
}