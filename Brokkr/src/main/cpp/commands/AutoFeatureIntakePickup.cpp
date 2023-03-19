// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#include <frc2/command/WaitCommand.h>

#include "commands/AutoFeatureIntakePickup.h"
#include "commands/IntakeSpin.h"
#include "commands/AutoDriveOntoRamp.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
AutoFeatureIntakePickup::AutoFeatureIntakePickup(Chassis& chassis, Claw& claw)
    // The deadline command
    : CommandHelper{IntakeSpin(claw, [](){ return Claw::kCurrentLimit;}, [](){return Claw::kMotorSpeed;})}
     {
  // Add your commands here, e.g.
  // AddCommands(FooCommand{}, BarCommand{});
  AddCommands(AutoDriveOntoRamp(chassis, 10, 20));
}
