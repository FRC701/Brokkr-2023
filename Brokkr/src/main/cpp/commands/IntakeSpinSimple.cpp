// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/IntakeSpinSimple.h"

IntakeSpinSimple::IntakeSpinSimple(Claw& claw, double speed)
: mClaw(claw)
, mSpeed(speed)
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(&mClaw);
}

// Called when the command is initially scheduled.
void IntakeSpinSimple::Initialize() {
  mClaw.IntakeSpin(mSpeed);
}

// Called repeatedly when this Command is scheduled to run
void IntakeSpinSimple::Execute() {
}

// Called once the command ends or is interrupted.
void IntakeSpinSimple::End(bool interrupted) {
  mClaw.IntakeSpin(0);
}

// Returns true when the command should end.
bool IntakeSpinSimple::IsFinished() {
  return false;
}
