// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "frc/smartdashboard/SmartDashboard.h"

#include "commands/GetWristInitialPosition.h"
namespace
{
  const double kWrist_P = 0.17;
  const double kWrist_I = 0.0;
  const double kWrist_D = 0.0;
}
GetWristInitialPosition::GetWristInitialPosition(Wrist& wrist) 
: mWrist(wrist)
, mWristControl{kWrist_P, kWrist_I, kWrist_D}
{
  AddRequirements(&mWrist);
}

// Called when the command is initially scheduled.
void GetWristInitialPosition::Initialize() {
  mWristControl.SetTolerance(0);
  mWristControl.EnableContinuousInput(180, 358);
}

// Called repeatedly when this Command is scheduled to run
void GetWristInitialPosition::Execute() {
  double WristAngle = frc::SmartDashboard::GetNumber("WristAngle", 0);
  double output = mWristControl.Calculate(mWrist.GetWristPosition(), WristAngle);
  mWrist.TurnWristPO(-1 * output);
}

// Called once the command ends or is interrupted.
void GetWristInitialPosition::End(bool interrupted) {}

// Returns true when the command should end.
bool GetWristInitialPosition::IsFinished() {
  return mWristControl.AtSetpoint();
}
 