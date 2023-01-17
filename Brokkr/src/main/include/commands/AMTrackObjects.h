// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Chassis.h"
#include "subsystems/Turret.h"
#include <frc/controller/PIDController.h>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AMTrackObjects
    : public frc2::CommandHelper<frc2::CommandBase, AMTrackObjects> {
 public:
  AMTrackObjects(Turret& mTurret, Chassis& mChassis, int pipelineIndex);

  void Initialize() override;
  void Execute() override;
  void End(bool interrupted) override;
  bool IsFinished() override;

private:

Turret& mTurret;
Chassis& mChassis;
int mPipelineIndex;
enum TrackState
{
  HasTarget = 0,
  TurretFacingTarget = 1,
  ChassisAlignDrive = 2
};

TrackState mTrackState;
bool NoTargets;

frc2::PIDController controllerT{0.1, 0, 0}; //to be tuned!
frc2::PIDController controllerC{0.1, 0, 0};
frc2::PIDController controllerCD{0.1, 0, 0};

};