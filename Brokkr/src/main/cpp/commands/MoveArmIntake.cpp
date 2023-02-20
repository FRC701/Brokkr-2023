// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/MoveArmIntake.h"
#include "commands/IntakeSpin.h"
#include "commands/ArmPosition.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
MoveArmIntake::MoveArmIntake(Arm& arm, Claw& claw, double armAngle) 
: CommandHelper(IntakeSpin(claw, 4))
{
  AddCommands
  (
    ArmPosition(arm, armAngle)
  );
}
