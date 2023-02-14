// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelCommandGroup.h>
#include "subsystems/Arm.h"
#include "subsystems/Wrist.h"
#include "subsystems/Turret.h"

class SetExtendtoNode
    : public frc2::CommandHelper<frc2::ParallelCommandGroup,
                                 SetExtendtoNode> {
 public:
  SetExtendtoNode(Arm& arm, Wrist& wrist, Turret& turret, double setPoint);
};
