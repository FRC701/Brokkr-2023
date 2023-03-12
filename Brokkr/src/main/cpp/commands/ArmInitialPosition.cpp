// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ArmInitialPosition.h"

ArmInitialPosition::ArmInitialPosition(Arm& arm, double distance)
:GetArmInitialPosition(arm)
,mDistance(distance)
{
}

double ArmInitialPosition::GetExtensionLength()
{
  return mDistance;
}

frc2::CommandPtr ArmInitialPosition::ToPtr() && 
{
return frc2::CommandPtr(make_unique());
}

std::unique_ptr<frc2::Command> ArmInitialPosition::TransferOwnership() &&
{
  return make_unique();
}

std::unique_ptr<ArmInitialPosition> ArmInitialPosition::make_unique()
{
  return std::make_unique<ArmInitialPosition>(*std::move(this));
}
