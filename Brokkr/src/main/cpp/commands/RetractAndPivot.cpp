// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/RetractAndPivot.h"
#include "commands/RetractIntoFramePerimeter.h"
#include "commands/TurretPID.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
RetractAndPivot::RetractAndPivot(Arm& arm, Wrist& wrist, Turret& turret, double yaw) 
{
  // Add your commands here, e.g.
  // AddCommands(FooCommand{}, BarCommand{});
  AddCommands(RetractIntoFramePerimeter(arm, wrist, 170, -60),
  TurretPID(turret, yaw));
}
