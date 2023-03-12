// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ArmPosition.h"

ArmPosition::ArmPosition(Arm& arm, double armHeight) 
: GetArmPosition(arm)
, mArmHeight(armHeight)
{
}

double ArmPosition::GetArmAngle()
{
  return mArmHeight;
}

frc2::CommandPtr ArmPosition::ToPtr() && 
{
return frc2::CommandPtr(make_unique());
}

std::unique_ptr<frc2::Command> ArmPosition::TransferOwnership() &&
{
  return make_unique();
}

std::unique_ptr<ArmPosition> ArmPosition::make_unique()
{
  return std::make_unique<ArmPosition>(*std::move(this));
}
