// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/PivotCompleteRetract.h"
#include "commands/RetractAndPivot.h"
#include "commands/MoveArmIntake.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
PivotCompleteRetract::PivotCompleteRetract(Arm& arm, Turret& turret, Chassis& chassis, Wrist& wrist, Claw& claw, double turan, double armang) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand{}, BarCommand{});
  AddCommands(RetractAndPivot(arm, wrist, chassis, turret, turan),
  MoveArmIntake(0, arm, wrist, claw, armang, 143, 0)
  );
}




