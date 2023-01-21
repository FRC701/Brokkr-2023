// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/smartdashboard/SmartDashboard.h>

#include "commands/WristLevel.h"

WristLevel::WristLevel(Wrist& wrist, Arm& arm)
: mWrist(wrist)
, mArm(arm)
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(&mWrist);
}

// Called when the command is initially scheduled.
void WristLevel::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void WristLevel::Execute() 
{
  double armAngle = mArm.CANCoderArmStatus();
  double wristAngle = mWrist.GetWristPosition();

  if(armAngle + 90 > wristAngle)
  {
    mWrist.TurnWristPO(-0.2);
  }
  else if(armAngle + 90 < wristAngle)
  {
    mWrist.TurnWristPO(0.2);
  }
}

// Called once the command ends or is interrupted.
void WristLevel::End(bool interrupted) {}

// Returns true when the command should end.
bool WristLevel::IsFinished() {
  return false;
}
