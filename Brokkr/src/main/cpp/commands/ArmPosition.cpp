// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ArmPosition.h"
#include <frc/smartdashboard/SmartDashboard.h>

ArmPosition::ArmPosition(Arm& arm, double armHeight) 
: GetArmPosition(arm)
, mArmHeight(armHeight)
{
}

double ArmPosition::GetArmAngle()
{
  return mArmHeight;
}

