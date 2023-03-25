// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoFeatureTimedWrist.h"

#include <frc2/command/InstantCommand.h>
#include <frc2/command/Waitcommand.h>

#include "commands/WristInitialPosition.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
AutoFeatureTimedWrist::AutoFeatureTimedWrist(Wrist& wrist, double ang)
    // The deadline command
    : CommandHelper{frc2::WaitCommand(units::second_t(1.25))} {
AddCommands(
WristInitialPosition(wrist, ang));
  // Add your commands here, e.g.
  // AddCommands(FooCommand{}, BarCommand{});
}
