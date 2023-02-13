// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelCommandGroup.h>
#include "subsystems/Chassis.h"
#include "subsystems/Arm.h"
#include "subsystems/Turret.h"
#include "subsystems/Claw.h"

class SetObjectPickUpWhileDrive
    : public frc2::CommandHelper<frc2::ParallelCommandGroup,
                                 SetObjectPickUpWhileDrive> {
 public:
  SetObjectPickUpWhileDrive(Arm& arm, Chassis& chassis, Claw& claw, Turret& turret);
};
