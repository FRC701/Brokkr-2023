// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ArmPosition.h"
#include <frc/smartdashboard/SmartDashboard.h>

ArmPosition::ArmPosition(Arm& mArm, double ArmHeight) 
: mArm(mArm)
{
  AddRequirements(&mArm);
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void ArmPosition::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ArmPosition::Execute() 
{
  mArm.SetArmHeight(ArmHeight);
}

// Called once the command ends or is interrupted.
void ArmPosition::End(bool interrupted) {}

// Returns true when the command should end.
bool ArmPosition::IsFinished() {
  return false;
}