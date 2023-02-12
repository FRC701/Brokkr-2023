// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/IntakeSpinSimple.h"

IntakeSpinSimple::IntakeSpinSimple(Claw& claw)
: mClaw(claw)
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(&mClaw);
}

// Called when the command is initially scheduled.
void IntakeSpinSimple::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void IntakeSpinSimple::Execute() {
  mClaw.IntakeSpin(-0.2);
}

// Called once the command ends or is interrupted.
void IntakeSpinSimple::End(bool interrupted) {}

// Returns true when the command should end.
bool IntakeSpinSimple::IsFinished() {
  return false;
}
