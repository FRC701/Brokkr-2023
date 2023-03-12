// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "GetIntakeSpin.h"
#include "subsystems/Claw.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class IntakeSpin
    : public GetIntakeSpin {
 public:
  explicit IntakeSpin(Claw& claw, double mSpeed);

  frc2::CommandPtr ToPtr() && override;

  protected:

  double GetCurrentLimit() override;
  double GetSpeed() override;

  std::unique_ptr<Command> TransferOwnership() && override;
  virtual std::unique_ptr<IntakeSpin> make_unique();

  double mSpeed;
};
