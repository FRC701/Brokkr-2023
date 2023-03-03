// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "frc/smartdashboard/SmartDashboard.h"

#include "commands/GetWristInitialPosition.h"

constexpr double kP = 0.045;
constexpr double kI = 0.0;
constexpr double kD = 0.0;

GetWristInitialPosition::GetWristInitialPosition(Wrist& wrist) 
: mWrist(wrist)
, mWristControl{kP, kI, kD}
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
  frc::SmartDashboard::PutNumber("Read Wrist Angle", WristAngle);
  double output = mWristControl.Calculate(mWrist.GetWristPosition(), WristAngle);
  frc::SmartDashboard::PutNumber("output", output);
  // TODO: Reverse the motor rather than multiply by -1
  mWrist.TurnWristPO(-1 * output);
}

// Called once the command ends or is interrupted.
void GetWristInitialPosition::End(bool interrupted) {}

// Returns true when the command should end.
bool GetWristInitialPosition::IsFinished() {
  return mWristControl.AtSetpoint();
}
