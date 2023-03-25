// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "GetTurretPID.h"

class TurretPID : public GetTurretPID
{
 public:
  TurretPID(Turret& turret, Chassis & chassis, double setPoint);

  frc2::CommandPtr ToPtr() && override;

protected:
  virtual double GetPosition();

  std::unique_ptr<Command> TransferOwnership() && override;
  virtual std::unique_ptr<TurretPID> make_unique();

  double mSetPoint;
};
