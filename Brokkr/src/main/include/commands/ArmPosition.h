// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "GetArmPosition.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ArmPosition
    : public GetArmPosition {
 public:
  ArmPosition(Arm& arm, double armHeight);

 protected:
  virtual double GetArmAngle() override;

  double mArmHeight;
};
