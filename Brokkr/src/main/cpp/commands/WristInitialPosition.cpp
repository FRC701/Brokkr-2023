// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/WristInitialPosition.h"
#include "frc/smartdashboard/SmartDashboard.h"

WristInitialPosition::WristInitialPosition(Wrist& wrist, double pose) 
: GetWristInitialPosition(wrist)
, mPose(pose)
{
}

double WristInitialPosition::GetWristAngle()
{
  return mPose;
}
