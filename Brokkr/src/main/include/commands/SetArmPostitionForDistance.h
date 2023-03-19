// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/controller/PIDController.h>

#include "subsystems/Arm.h"
#include "subsystems/Turret.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
  enum class NodeLevel {HybridLevel, MiddleNodeLevel, UpperNodeLevel};

class SetArmPostitionForDistance
    : public frc2::CommandHelper<frc2::CommandBase, SetArmPostitionForDistance> {
 public:
  SetArmPostitionForDistance(Arm& arm, Turret& turret, const NodeLevel& Level);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
Arm& mArm;
Turret& mTurret;
const NodeLevel& mLevel;
frc2::PIDController mArmPosition;
};
