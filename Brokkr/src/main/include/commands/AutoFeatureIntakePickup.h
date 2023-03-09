// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelDeadlineGroup.h>
#include "subsystems/Claw.h"
#include "subsystems/Chassis.h"

class AutoFeatureIntakePickup
    : public frc2::CommandHelper<frc2::ParallelDeadlineGroup,
                                 AutoFeatureIntakePickup> {
 public:
  AutoFeatureIntakePickup(Chassis& chassis, Claw& claw);
};
