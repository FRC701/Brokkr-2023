// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc2/command/InstantCommand.h>

#include "commands/AutoForwardAndBackDrive.h"
#include "commands/TankDriveVoltage.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
AutoForwardAndBackDrive::AutoForwardAndBackDrive(Chassis& chassis, double left, double right, double time)
    // The deadline command
    : CommandHelper{frc2::WaitCommand(units::second_t(time))} //2.5 is a placeholder
{
  AddCommands
  (
    TankDriveVoltage(chassis, left, right)
  );
}
