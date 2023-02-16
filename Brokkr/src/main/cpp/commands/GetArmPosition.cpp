// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/smartdashboard/SmartDashboard.h>

#include "commands/GetArmPosition.h"


GetArmPosition::GetArmPosition(Arm& arm) 
: mArm(arm)
{
  AddRequirements(&mArm);
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void GetArmPosition::Initialize() 
{
  mArmControl.SetTolerance(1);
  mArmControl.EnableContinuousInput(9, 86);
}

// Called repeatedly when this Command is scheduled to run
void GetArmPosition::Execute() 
{
  double ArmAngle = frc::SmartDashboard::GetNumber("ArmAngle", 0);
  double output = mArmControl.Calculate(mArm.CANCoderArmStatus(), ArmAngle);
  mArm.SetArmSpeed(output);
}

// Called once the command ends or is interrupted.
void GetArmPosition::End(bool interrupted) {}

// Returns true when the command should end.
bool GetArmPosition::IsFinished() {
  return mArmControl.AtSetpoint();
}
