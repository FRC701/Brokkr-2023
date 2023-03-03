// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "subsystems/Claw.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class IntakeSpinHelper
 {
 public:
  IntakeSpinHelper(Claw& claw);

  void Initialize();

  void Execute();

  void End(bool interrupted);

  bool IsFinished();

  protected:

  virtual double GetCurrentLimit();

  virtual double GetMotorSpeed();

  Claw& mClaw;
  frc::Timer mTimer;
  double mSpeed;

  bool mIsInRushOver;
  bool mCouldBeStalled;
  bool mIsMotorStalling;
};
