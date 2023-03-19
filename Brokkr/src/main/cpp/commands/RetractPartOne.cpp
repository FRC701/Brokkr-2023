// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/RetractPartOne.h"

#include <frc2/command/InstantCommand.h>

#include "commands/ArmInitialPosition.h"
#include "commands/WristInitialPosition.h"
#include "commands/TurretPID.h"


// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
RetractPartOne::RetractPartOne(Arm& arm, Claw& claw, Turret& turret, Wrist& wrist)
{
  // Add your commands here, e.g.
  // AddCommands(FooCommand{}, BarCommand{});
  AddCommands
  (
    //ArmInitialPosition(arm, 0),
    WristInitialPosition(wrist, 170)
    //TurretPID(turret, 0)
  );
}
