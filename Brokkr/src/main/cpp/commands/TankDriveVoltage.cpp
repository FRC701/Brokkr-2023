// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TankDriveVoltage.h"

TankDriveVoltage::TankDriveVoltage(Chassis& chassis, double left, double right) 
: mChassis(chassis)
, mLeft(left)
, mRight(right)
{
  AddRequirements(&mChassis);
}

// Called when the command is initially scheduled.
void TankDriveVoltage::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TankDriveVoltage::Execute() 
{
  mChassis.TankDriveVoltage(mLeft, mRight);
}

// Called once the command ends or is interrupted.
void TankDriveVoltage::End(bool interrupted) {}

// Returns true when the command should end.
bool TankDriveVoltage::IsFinished() {
  return false;
}
