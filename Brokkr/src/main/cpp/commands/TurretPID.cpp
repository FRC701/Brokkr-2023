// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TurretPID.h"

TurretPID::TurretPID(Turret& turret, Chassis& chassis, double yawSetPoint)
: GetTurretPID(turret, chassis)
, mSetPoint(yawSetPoint)
{
}

frc2::CommandPtr TurretPID::ToPtr() &&
{
  return frc2::CommandPtr(make_unique());
}

double TurretPID::GetPosition()
{
  return mSetPoint;
}

std::unique_ptr<frc2::Command> TurretPID::TransferOwnership() &&
{
  return make_unique();
}

std::unique_ptr<TurretPID> TurretPID::make_unique()
{
  return std::make_unique<TurretPID>(*std::move(this));
}
