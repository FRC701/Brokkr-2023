// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/SetExtendtoNodeDrive.h"
#include "commands/SetExtendtoNode.h"
#include "commands/AutoForwardAndBackDrive.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
SetExtendtoNodeDrive::SetExtendtoNodeDrive(Arm& arm, Chassis& chassis, Wrist& wrist, Turret& turret) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand{}, BarCommand{});
  AddCommands(
    SetExtendtoNode(arm, wrist, turret, 315),
    AutoForwardAndBackDrive(chassis, -11.5, -11.5, 2.5) //2.5 is a placeholder
  );
}
