// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ArcadeDrive.h"

ArcadeDrive::ArcadeDrive(Chassis& chassis, std::function<double()> speed, std::function<double()> rotation)
: mChassis(chassis)
, mSpeed(speed)
, mRotation(rotation)
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(&mChassis);
}

// Called when the command is initially scheduled.
void ArcadeDrive::Initialize() 
{
  
}

// Called repeatedly when this Command is scheduled to run
void ArcadeDrive::Execute() 
{
  mChassis.ArcadeDrive(mSpeed(), mRotation());
}

// Called once the command ends or is interrupted.
void ArcadeDrive::End(bool interrupted) {}

// Returns true when the command should end.
bool ArcadeDrive::IsFinished() {
  return false;
}
