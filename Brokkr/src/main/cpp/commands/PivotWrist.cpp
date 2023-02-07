// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/PivotWrist.h"

PivotWrist::PivotWrist(Wrist& wrist, std::function<double()> motorspeed) 
: mWrist(wrist)
, mMotorSpeed(motorspeed)
{
    // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void PivotWrist::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void PivotWrist::Execute() 
{
  /*if(mWrist.WristMaxLimitSwitch() && mMotorSpeed > 0)
  {
    mWrist.TurnWristPO(0);
  }
  else if(mWrist.WristMinLimitSwitch() && mMotorSpeed < 0)
  {
    mWrist.TurnWristPO(0);
  }
  else
  {*/
    mWrist.TurnWristPO(mMotorSpeed());

}

// Called once the command ends or is interrupted.
void PivotWrist::End(bool interrupted) {
  mWrist.TurnWristPO(0);
}

// Returns true when the command should end.
bool PivotWrist::IsFinished() {
  return false;
}
