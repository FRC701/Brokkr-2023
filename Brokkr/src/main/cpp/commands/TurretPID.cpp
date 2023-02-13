// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TurretPID.h"

namespace
{
  const double kTurretPosition_P = 10.0;
  const double kTurretPosition_I = 0.0;
  const double kTurretPosition_D = 0.0;
}


// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
TurretPID::TurretPID(Turret& turret, double yawSetPoint)
    : CommandHelper{frc2::PIDController{kTurretPosition_P, kTurretPosition_I, kTurretPosition_D},
                    // This should return the measurement
                    [this] { return setPoint(); },
                    // This should return the setpoint (can also be a constant)
                    [yawSetPoint] { return yawSetPoint; },
                    // This uses the output
                    [this](double output) {
                      setSpeed(output);
                    }},
      mTurret(turret)
{
  GetController().EnableContinuousInput(0, 180);
  GetController().SetTolerance(3.0);
  AddRequirements(&mTurret);
}
 double TurretPID::setPoint()
 {
   return mTurret.GetYawIMU();
 }
 
 void TurretPID::setSpeed(double speed)
 {
   mTurret.SetTurretSpeed(speed);
 }


// Returns true when the command should end.
bool TurretPID::IsFinished() {
  return GetController().AtSetpoint();
}
