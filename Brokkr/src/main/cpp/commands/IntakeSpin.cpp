// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/IntakeSpin.h"

IntakeSpin::IntakeSpin(Claw& claw, double speed)
: GetIntakeSpin(claw) 
, mSpeed(speed)
{
}

double IntakeSpin::GetCurrentLimit()
{
  double intakeCurrentLimit = 80.0;
  return intakeCurrentLimit;
}

double IntakeSpin::GetSpeed()
{
  return mSpeed;
}

frc2::CommandPtr IntakeSpin::ToPtr() && {
  return frc2::CommandPtr(make_unique());
}

std::unique_ptr<frc2::Command> IntakeSpin::TransferOwnership() && {
  return make_unique();
}

std::unique_ptr<IntakeSpin> IntakeSpin::make_unique() {
  return std::make_unique<IntakeSpin>(*std::move(this));
}
