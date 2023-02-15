// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ArmInitialPosition.h"

ArmInitialPosition::ArmInitialPosition(Arm& arm, double distance)
:mArm(arm)
,mDistance(distance)
, mArmControl{0, 0, 0} 
{
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void ArmInitialPosition::Initialize() 
{
  mArmControl.SetTolerance(1);
}

// Called repeatedly when this Command is scheduled to run
void ArmInitialPosition::Execute() 
{
  double output = mArmControl.Calculate(mArm.GetExtendTicks(), mArm.DistanceToTicks(mDistance));
  mArm.SetArmSpeed(output);
}

// Called once the command ends or is interrupted.
void ArmInitialPosition::End(bool interrupted) 
{}

// Returns true when the command should end.
bool ArmInitialPosition::IsFinished() 
{
  return mArmControl.AtSetpoint();
}
