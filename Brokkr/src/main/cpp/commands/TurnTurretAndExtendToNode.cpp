// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TurnTurretAndExtendToNode.h"
#include "commands/VisionTurretPID.h"
#include "commands/WristInitialPosition.h"
// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
TurnTurretAndExtendToNode::TurnTurretAndExtendToNode(Arm& arm, Wrist& wrist, Turret& turret, const NodeLevel& level, double ang) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand{}, BarCommand{});
  AddCommands(
    WristInitialPosition(wrist, ang),
    SetArmPostitionForDistance(arm, turret, level)
  );
}
