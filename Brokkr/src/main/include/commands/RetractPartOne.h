// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelRaceGroup.h>

#include "subsystems/Arm.h"
#include "subsystems/Claw.h"
#include "subsystems/Turret.h"
#include "subsystems/Wrist.h"

class RetractPartOne
    : public frc2::CommandHelper<frc2::ParallelRaceGroup,
                                 RetractPartOne> {
 public:
  RetractPartOne(Arm& arm, Claw& claw, Turret& turret, Wrist& wrist);
  
};
