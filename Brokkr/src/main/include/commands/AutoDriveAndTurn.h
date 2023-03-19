// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelCommandGroup.h>

#include "subsystems/Arm.h"
#include "subsystems/Chassis.h"
#include "subsystems/Claw.h"
#include "subsystems/Wrist.h"
#include "subsystems/Turret.h"

class AutoDriveAndTurn
    : public frc2::CommandHelper<frc2::ParallelCommandGroup,
                                 AutoDriveAndTurn> {
 public:
  AutoDriveAndTurn(Chassis& chassis, Turret& turret, Wrist& wrist, Arm& arm, Claw& claw, double turang, double chasdirec, double wrisang, double armang);
};
