// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/MoveArmIntake.h"
#include "commands/IntakeSpin.h"
#include "commands/ArmPosition.h"
#include "commands/WristInitialPosition.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
MoveArmIntake::MoveArmIntake(double intdir, Arm& arm, Wrist& wrist, Claw& claw, double armAngle, double wrisang, double limit) 
{
  AddCommands
  (
    IntakeSpin(claw, intdir, limit),
    WristInitialPosition(wrist, wrisang),
    ArmPosition(arm, armAngle)
  );
}
