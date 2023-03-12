// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "GetArmInitialPosition.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ArmInitialPosition
    : public GetArmInitialPosition 
{
 public:
  ArmInitialPosition(Arm& arm, double distance);

  frc2::CommandPtr ToPtr() && override;

 protected:
  std::unique_ptr<Command> TransferOwnership() && override;

  virtual std::unique_ptr<ArmInitialPosition> make_unique();

  double GetExtensionLength() override;

  double mDistance;
};