// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoHighMidNodeTaxi.h"
#include "commands/AutoFeatureTurnToNode.h"
#include "commands/AutoDriveOntoRamp.h"
#include "commands/IntakeEjectObject.h"
#include "commands/AutoDriveAndTurn.h"
#include "commands/IntakeSpin.h"
#include "commands/AutoFeatureIntakePickup.h"
// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
AutoHighMidNodeTaxi::AutoHighMidNodeTaxi(Arm& arm, Turret& turret, Wrist& wrist, Chassis& chassis, Claw& claw) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand{}, BarCommand{});
  AddCommands(
    AutoFeatureTurnToNode(wrist, turret, arm, 50, 180, 10),
    IntakeEjectObject(claw, -6),
    AutoDriveAndTurn(chassis, turret, wrist, arm, claw, 0, 83, 50, 10),
    AutoFeatureIntakePickup(chassis, claw),
    AutoDriveAndTurn(chassis, turret, wrist, arm, claw, 180, -83, 35, 15),
    IntakeEjectObject(claw, -6)
  );
}
