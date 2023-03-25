// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/GetTurretPID.h"
#include "frc/smartdashboard/SmartDashboard.h"
namespace
{
  const double kTurret_P = 0.05;
  const double kTurret_I = 0.0;
  const double kTurret_D = 0.0;
}
GetTurretPID::GetTurretPID(Turret& turret, Chassis& chassis)
: mTurret(turret)
, mChassis(chassis)
, TurretControl{kTurret_P, kTurret_I, kTurret_D} 
 {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(&mTurret);
}

// Called when the command is initially scheduled.
void GetTurretPID::Initialize() {
  timer.Start();
  TurretControl.SetTolerance(0);
  //TurretControl.EnableContinuousInput(-360, 360);
}

// Called repeatedly when this Command is scheduled to run
void GetTurretPID::Execute() {
  double Pose = GetPosition();
  double TurretYaw = mTurret.GetYawIMU(); //+ (mChassis.GetYawNavX() - mTurret.GetYawIMU());
  frc::SmartDashboard::PutNumber("REALTurretYaw", TurretYaw);
  double output = TurretControl.Calculate(TurretYaw, Pose);
  mTurret.SetTurretSpeed(output);
}

// Called once the command ends or is interrupted.
void GetTurretPID::End(bool interrupted) {
  timer.Reset();
  timer.Stop();
}

// Returns true when the command should end.
bool GetTurretPID::IsFinished() {
  return timer.HasElapsed(units::second_t(2.5));
}

double GetTurretPID::GetPosition() {
  double Pose = frc::SmartDashboard::GetNumber("TurretAngle", 0);
  return Pose;
}
