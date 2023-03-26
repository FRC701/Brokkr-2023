// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/Arm.h"
#include "subsystems/Turret.h"
#include "subsystems/Wrist.h"
#include "subsystems/Claw.h"

#include "subsystems/Chassis.h"

class PivotCompleteRetract
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 PivotCompleteRetract> {
 public:
  PivotCompleteRetract(Arm& mArm, Turret& mTurret, Chassis& mChassis, Wrist& mWrist, Claw& mClaw, double turan, double armang);
};
