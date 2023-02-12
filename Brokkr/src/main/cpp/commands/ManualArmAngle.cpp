// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ManualArmAngle.h"

ManualArmAngle::ManualArmAngle(Arm& arm, double speed)
 : mArm(arm)
 , mSpeed(speed)
 {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(&mArm);
}

// Called when the command is initially scheduled.
void ManualArmAngle::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ManualArmAngle::Execute() {
  mArm.SetArmSpeed(mSpeed);
}

// Called once the command ends or is interrupted.
void ManualArmAngle::End(bool interrupted) {
  mArm.SetArmSpeed(0);
}

// Returns true when the command should end.
bool ManualArmAngle::IsFinished() {
  return false;
}
