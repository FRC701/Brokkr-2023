// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#include <frc2/command/WaitCommand.h>

#include "commands/IntakeEjectObject.h"
#include "commands/IntakeSpinSimple.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
IntakeEjectObject::IntakeEjectObject(Claw& claw)
    // The deadline command
    : CommandHelper{frc2::WaitCommand(units::second_t(1.0))}
     {
  // Add your commands here, e.g.
  // AddCommands(FooCommand{}, BarCommand{});
  AddCommands(IntakeSpinSimple(claw));
}
