// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/smartdashboard/SmartDashboard.h>

#include "commands/WristLevel.h"

WristLevel::WristLevel(Wrist& wrist, Arm& arm)
: mWrist(wrist)
, mArm(arm)
, mWristControl{0.1, 0, 0}
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(&mWrist);
}

// Called when the command is initially scheduled.
void WristLevel::Initialize() {
  mWristControl.SetTolerance(1);
  mWristControl.EnableContinuousInput(70, 194.25);
}

// Called repeatedly when this Command is scheduled to run
void WristLevel::Execute() 
{
  double armAngle = mArm.CANCoderArmStatus();
  double wristAngle = mWrist.GetWristPosition();
  /*
  if(armAngle + 72 > wristAngle)
  {
    mWrist.TurnWristPO(-0.2);
  }
  else if(armAngle + 72 < wristAngle)
  {
    mWrist.TurnWristPO(0.2);
  } */
  double LevelPose = armAngle + 72;
  double output = mWristControl.Calculate(mWrist.GetWristPosition(), LevelPose);
  mWrist.TurnWristPO(output);
}

// Called once the command ends or is interrupted.
void WristLevel::End(bool interrupted) {}

// Returns true when the command should end.
bool WristLevel::IsFinished() {
  return false;
}
