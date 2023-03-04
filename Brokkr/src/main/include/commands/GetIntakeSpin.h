// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <functional>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/Timer.h>

#include "subsystems/Claw.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class GetIntakeSpin
    : public frc2::CommandHelper<frc2::CommandBase, GetIntakeSpin> {
 public:
  GetIntakeSpin(Claw& claw, std::function<double()> currentLimit, std::function<double()> motorSpeed);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  Claw& mClaw;
  std::function<double()> mCurrentLimit;
  std::function<double()> mMotorSpeed;

  frc::Timer mTimer;
  bool mIsInRushOver;
  bool mCouldBeStalled;
  bool mIsMotorStalling;

};
