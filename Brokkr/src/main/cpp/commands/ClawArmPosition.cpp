// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ClawArmPosition.h"
#include "commands/IntakeSpin.h"
#include "commands/WristLevel.h"


// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
ClawArmPosition::ClawArmPosition(Arm& arm, Wrist& wrist, Claw& claw) 
: mArm(arm)
, mWrist(wrist)
, mClaw(claw)
{
  // Add your commands here, e.g.
  // AddCommands(FooCommand{}, BarCommand{});
  AddCommands(
    IntakeSpin(mClaw, [](){return Claw::kCurrentLimit;},[](){ return Claw::kMotorSpeed;}),
    WristLevel(mWrist, mArm)
  );
}
