// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ExtendArm.h"

ExtendArm::ExtendArm(Arm& mArm, double mMotorSpeed)
: mArm(mArm)
{
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void ExtendArm::Initialize()
{
  bool ReachLimit = false;
}

// Called repeatedly when this Command is scheduled to run
void ExtendArm::Execute() 
{
  if (mMotorSpeed < 0 && mArm.ArmMaxLimitSwitch() == true)
  {
    mArm.ArmExtend(0);
  }
  else
  {
    mArm.ArmExtend(mMotorSpeed);
  }

  if (mMotorSpeed > 0 && mArm.ArmMinLimitSwitch() == true)
  {
    mArm.ArmExtend(0);
  }
  else
  {
    mArm.ArmExtend(mMotorSpeed);
  }
}

// Called once the command ends or is interrupted.
void ExtendArm::End(bool interrupted)
{
  mArm.ArmExtend(0);
}

// Returns true when the command should end.
bool ExtendArm::IsFinished()
{
  return ReachLimit;
}
