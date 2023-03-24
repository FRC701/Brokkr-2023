// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelDeadlineGroup.h>
#include "subsystems/Wrist.h"
#include "subsystems/Turret.h"
#include "subsystems/Arm.h"

class AutoFeatureTurnToNode
    : public frc2::CommandHelper<frc2::ParallelDeadlineGroup,
                                 AutoFeatureTurnToNode> {
 public:
  AutoFeatureTurnToNode(Wrist& mWrist, Turret& mTurret, Arm& mArm, double armangle, double wristangle, double turretangle);
};
