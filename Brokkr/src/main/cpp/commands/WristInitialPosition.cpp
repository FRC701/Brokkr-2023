// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/WristInitialPosition.h"
#include "frc/smartdashboard/SmartDashboard.h"

WristInitialPosition::WristInitialPosition(Wrist& wrist, double pose) 
:mWrist(wrist)
,mPose(pose)
{
  AddRequirements(&mWrist);
}

// Called when the command is initially scheduled.
void WristInitialPosition::Initialize() {
  mWristControl.SetTolerance(0);
 // mWristControl.EnableContinuousInput(180,358);
}

// Called repeatedly when this Command is scheduled to run
void WristInitialPosition::Execute() {
  double output = mWristControl.Calculate(mWrist.GetWristPosition(), mPose);
  frc::SmartDashboard::PutNumber("output", output);
  mWrist.TurnWristPO(output);
}

// Called once the command ends or is interrupted.
void WristInitialPosition::End(bool interrupted) {}

// Returns true when the command should end.
bool WristInitialPosition::IsFinished() {
  return mWristControl.AtSetpoint();
}
  