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
