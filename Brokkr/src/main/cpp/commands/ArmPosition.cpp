// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ArmPosition.h"
#include <frc/smartdashboard/SmartDashboard.h>

ArmPosition::ArmPosition(Arm& arm, double armHeight) 
: mArm(arm)
, mArmControl{0.8, 0, 0}
, mArmHeight(armHeight)
{
  AddRequirements(&mArm);
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void ArmPosition::Initialize() 
{
  mArmControl.SetTolerance(1.0);
  mArmControl.EnableContinuousInput(2, 80);
}

// Called repeatedly when this Command is scheduled to run
void ArmPosition::Execute() 
{
  double output = mArmControl.Calculate(mArm.CANCoderArmStatus(), mArmHeight);
  mArm.SetArmSpeed(-1 * output);
}

// Called once the command ends or is interrupted.
void ArmPosition::End(bool interrupted) {}

// Returns true when the command should end.
bool ArmPosition::IsFinished() {
  return mArmControl.AtSetpoint();
}
