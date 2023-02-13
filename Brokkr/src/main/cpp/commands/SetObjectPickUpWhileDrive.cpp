// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/SetObjectPickUpWhileDrive.h"
#include "commands/IntakeSpin.h"
#include "commands/ArmInitialPosition.h"
#include "commands/ArmPosition.h"
#include "commands/TurretPID.h"
// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
SetObjectPickUpWhileDrive::SetObjectPickUpWhileDrive(Arm& arm, Chassis& chassis, Claw& claw, Turret& turret) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand{}, BarCommand{});s
  AddCommands(
    IntakeSpin(claw),
    ArmInitialPosition(arm, 3),
    ArmPosition(arm, 20),
    TurretPID(turret, 15)
  );
}
