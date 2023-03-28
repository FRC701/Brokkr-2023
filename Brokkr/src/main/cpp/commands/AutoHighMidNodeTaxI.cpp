// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoHighMidNodeTaxi.h"
#include "commands/AutoFeatureTurnToNode.h"
#include "commands/AutoDriveOntoRamp.h"
#include "commands/IntakeEjectObject.h"
#include"commands/RetractAndPivot.h"
#include "commands/AutoFeatureTimedWrist.h"
#include <frc2/command/WaitCommand.h>

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
AutoHighMidNodeTaxi::AutoHighMidNodeTaxi(Arm& arm, Turret& turret, Wrist& wrist, Chassis& chassis, Claw& claw, double distance, double turretangle) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand{}, BarCommand{});
  AddCommands(
    //RetractAndPivot(arm, wrist, turret, 180),
    AutoFeatureTurnToNode(wrist, turret, chassis, arm, -5, 45, turretangle), // turret is not used
    frc2::WaitCommand(units::second_t(0.5)),
    //AutoFeatureTimedWrist(wrist, 45),
    IntakeEjectObject(claw, -8),
    RetractAndPivot(arm, wrist, chassis, turret, 0),
    AutoDriveOntoRamp(chassis, 0.25, distance)
  );
}
