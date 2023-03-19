// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoDriveOntoRamp.h"
#include <frc/smartdashboard/SmartDashboard.h>


AutoDriveOntoRamp::AutoDriveOntoRamp(Chassis& chassis, double motorPower, double ticks) 
: mChassis(chassis)
, mMotorPower(motorPower)
, mTicks(ticks)
, mTargetTicks(0)
{
  AddRequirements(&mChassis);
}

// Called when the command is initially scheduled.
void AutoDriveOntoRamp::Initialize() {
  mChassis.SetNeutralMode(NeutralMode::Brake);
  mTargetTicks = mChassis.EncoderTicksLeft() + mTicks;
}

// Called repeatedly when this Command is scheduled to run
void AutoDriveOntoRamp::Execute() 
{
  frc::SmartDashboard::PutNumber("AutoDrive Ticks", mTicks);
  frc::SmartDashboard::PutNumber("AutoDrive Target Ticks", mTargetTicks);

  // mChassis.ArcadeDrive(mMotorPower, 0.0);
  double motorPowerVoltage = mMotorPower * 12.;
  constexpr double kLeftAdjust = 1.15;
  constexpr double kRightAdjust = 1.0;
  mChassis.TankDriveVoltage(motorPowerVoltage * kLeftAdjust , motorPowerVoltage * kRightAdjust);
}

// Called once the command ends or is interrupted.
void AutoDriveOntoRamp::End(bool interrupted) 
{
  mChassis.ArcadeDrive(0., 0.);
  mChassis.SetNeutralMode(NeutralMode::Coast);
}

// Returns true when the command should end.
bool AutoDriveOntoRamp::IsFinished() 
{
  double tickDiff = mChassis.EncoderTicksLeft() - mTargetTicks;
  frc::SmartDashboard::PutNumber("AutoDrive Ticks Difference", tickDiff);
  if (mTicks >= 0)
  {
    return tickDiff >= 0;
  }
  else
  {
    return tickDiff <= 0;
  }
}

