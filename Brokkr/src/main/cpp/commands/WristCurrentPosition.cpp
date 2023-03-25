// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <iostream>
#include "commands/WristCurrentPosition.h"
#include "frc/smartdashboard/SmartDashboard.h"

WristCurrentPosition::WristCurrentPosition(Wrist &wrist)
    : GetWristInitialPosition(wrist), mPose(mWrist.GetWristPosition())
{
}

void WristCurrentPosition::Initialize()
{
  mPose = mWrist.GetWristPosition();
}

frc2::CommandPtr WristCurrentPosition::ToPtr() &&
{
  return frc2::CommandPtr(make_unique());
}

std::unique_ptr<frc2::Command> WristCurrentPosition::TransferOwnership() &&
{
  return make_unique();
}

double WristCurrentPosition::GetWristAngle()
{
  return mPose;
}

std::unique_ptr<WristCurrentPosition> WristCurrentPosition::make_unique()
{
  return std::make_unique<WristCurrentPosition>(*std::move(this));
}
