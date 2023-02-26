// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/GetTurretPID.h"
#include "frc/smartdashboard/SmartDashboard.h"

GetTurretPID::GetTurretPID(Turret& turret)
: mTurret(turret)
, TurretControl{0.1, 0, 0} 
 {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(&mTurret);
}

// Called when the command is initially scheduled.
void GetTurretPID::Initialize() {
  TurretControl.SetTolerance(0);
  TurretControl.EnableContinuousInput(-359, 359);
}

// Called repeatedly when this Command is scheduled to run
void GetTurretPID::Execute() {
  double Pose = frc::SmartDashboard::GetNumber("TurretAngle", 0);
  double output = TurretControl.Calculate(mTurret.GetYawIMU(), Pose);
  mTurret.SetTurretSpeed(-1.0 * output);
}

// Called once the command ends or is interrupted.
void GetTurretPID::End(bool interrupted) {}

// Returns true when the command should end.
bool GetTurretPID::IsFinished() {
  return TurretControl.AtSetpoint();
}
