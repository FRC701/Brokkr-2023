// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ControllerChassisRotationReal.h"

ControllerChassisRotationReal::ControllerChassisRotationReal(Chassis& chassis, Turret& turret)
: mChassis(chassis)
, mTurret(turret)
, controllerChassisRot{0.1, 0, 0}
{
  AddRequirements(&mChassis);
}

// Called when the command is initially scheduled.
void ControllerChassisRotationReal::Initialize() 
{
controllerChassisRot.SetTolerance(1);
}

// Called repeatedly when this Command is scheduled to run
void ControllerChassisRotationReal::Execute() {
  double output = controllerChassisRot.Calculate(mChassis.GetYawNavX(), mTurret.GetYawIMU());
  mChassis.ArcadeDrive(0, output);
}

// Called once the command ends or is interrupted.
void ControllerChassisRotationReal::End(bool interrupted) {
  mChassis.ArcadeDrive(0, 0);
}

// Returns true when the command should end.
bool ControllerChassisRotationReal::IsFinished() {
  return controllerChassisRot.AtSetpoint();
}
