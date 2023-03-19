// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoHighMidNodeTaxi.h"
#include "commands/AutoFeatureTurnToNode.h"
#include "commands/AutoDriveOntoRamp.h"
#include "commands/IntakeEjectObject.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
AutoHighMidNodeTaxi::AutoHighMidNodeTaxi(Arm& arm, Turret& turret, Wrist& wrist, Chassis& chassis, Claw& claw) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand{}, BarCommand{});
  AddCommands(
    AutoFeatureTurnToNode(wrist, turret, arm, 50, 180, 10), // turret is not used
    IntakeEjectObject(claw, -6),
    AutoDriveOntoRamp(chassis, .8, Chassis::DistanceToTicks(99.0 - 16.0)) // 99 inches - half the length of the robot
  );
}
