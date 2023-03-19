// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoFeatureTurnToNode.h"
#include "commands/ArmPosition.h"
#include "commands/WristInitialPosition.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
AutoFeatureTurnToNode::AutoFeatureTurnToNode(Wrist& wrist, Turret& turret, Arm& arm, double armangle, double wristangle, double turretangle) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand{}, BarCommand{});
  AddCommands(
    ArmPosition(arm, armangle),
    WristInitialPosition(wrist, wristangle)
  );
}
