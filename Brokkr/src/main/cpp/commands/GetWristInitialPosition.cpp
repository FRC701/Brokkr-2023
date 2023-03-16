// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "frc/smartdashboard/SmartDashboard.h"

#include "commands/GetWristInitialPosition.h"
#include <iostream>

namespace
{
  const double kWrist_P = 0.045;
  const double kWrist_I = 0.0;
  const double kWrist_D = 0.0;
  const double kWrist_S = 0.0;
  const double kWrist_G = 0.0;
  const double kWrist_V = 0.0;
  const double kWrist_A = 0.0;
}

using Angle = units::radians;

using Acceleration = units::compound_unit<units::radians_per_second,
                                          units::inverse<units::second>>;
using kv_unit =
    units::compound_unit<units::volts,
                         units::inverse<units::radians_per_second>>;
using ka_unit =
    units::compound_unit<units::volts, units::inverse<Acceleration>>;

GetWristInitialPosition::GetWristInitialPosition(Wrist &wrist)
    : mWrist(wrist), mWristControl{kWrist_P, kWrist_I, kWrist_D},
      mFeedForward{units::volt_t(kWrist_S), units::volt_t(kWrist_G), units::unit_t<kv_unit>(kWrist_V), units::unit_t<ka_unit>(kWrist_A)}
{
  AddRequirements(&mWrist);
}

// Called when the command is initially scheduled.
void GetWristInitialPosition::Initialize()
{
  mWristControl.SetTolerance(0);
  mWristControl.EnableContinuousInput(180, 358);
}

// Called repeatedly when this Command is scheduled to run
void GetWristInitialPosition::Execute()
{

  double WristAngle = GetWristAngle();
  double feedforward = mFeedForward.Calculate(units::unit_t<Angle>(WristAngle * 0.0174533), 2_rad_per_s).value();
  frc::SmartDashboard::PutNumber("Read Wrist Angle", WristAngle);
  double output = mWristControl.Calculate(mWrist.GetWristPosition(), WristAngle) + feedforward;
  frc::SmartDashboard::PutNumber("output", output);
  // TODO: Reverse the motor rather than multiply by -1
  mWrist.TurnWristPO(-1 * output);
}

double GetWristInitialPosition::GetWristAngle()
{
  return frc::SmartDashboard::GetNumber("WristAngle", 0);
}

// Called once the command ends or is interrupted.
void GetWristInitialPosition::End(bool interrupted)
{
}

// Returns true when the command should end.
bool GetWristInitialPosition::IsFinished()
{
  return mWristControl.AtSetpoint();
}
