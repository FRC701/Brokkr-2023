// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/Turret.h"
#include <frc/controller/PIDController.h>
#include <frc/Timer.h>
#include "subsystems/Chassis.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class GetTurretPID
    : public frc2::CommandHelper<frc2::CommandBase, GetTurretPID> {
 public:
  GetTurretPID(Turret& turret, Chassis& chassis);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

protected:
  virtual double GetPosition();

frc::Timer timer;
Turret& mTurret;
Chassis& mChassis;

frc::PIDController TurretControl;
};
