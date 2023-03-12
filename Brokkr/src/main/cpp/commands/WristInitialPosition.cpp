// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <iostream>
#include "commands/WristInitialPosition.h"
#include "frc/smartdashboard/SmartDashboard.h"

WristInitialPosition::WristInitialPosition(Wrist &wrist, double pose)
    : GetWristInitialPosition(wrist), mPose(pose)
{
}

frc2::CommandPtr WristInitialPosition::ToPtr() &&
{
  return frc2::CommandPtr(make_unique());
}

std::unique_ptr<frc2::Command> WristInitialPosition::TransferOwnership() &&
{
  return make_unique();
}

double WristInitialPosition::GetWristAngle()
{
  return mPose;
}

std::unique_ptr<WristInitialPosition> WristInitialPosition::make_unique()
{
  return std::make_unique<WristInitialPosition>(*std::move(this));
}
