// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoTwoPieceTaxi.h"
#include "commands/ArmPosition.h"
#include "commands/SetExtendtoNode.h"
#include "commands/SetObjectPickUpWhileDrive.h"
#include "commands/IntakeEjectObject.h"
#include "commands/WristLevel.h"
#include "commands/SetExtendtoNodeDrive.h"
#include "commands/AutoForwardAndBackDrive.h"
#include "commands/IntakeSpin.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
AutoTwoPieceTaxi::AutoTwoPieceTaxi(Arm& arm, Chassis& chassis, Claw& claw, Wrist& wrist, Turret& turret) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand{}, BarCommand{});
  AddCommands(
    ArmPosition(arm, 75),
    SetExtendtoNode(arm, wrist, turret, 45),
    IntakeEjectObject(claw, -4),
    SetObjectPickUpWhileDrive(arm, chassis, claw, turret),
    WristLevel(wrist, arm),
    IntakeSpin(claw, 4, 0),
    SetExtendtoNodeDrive(arm, chassis, wrist, turret),
    IntakeEjectObject(claw, -4)
  );
}
