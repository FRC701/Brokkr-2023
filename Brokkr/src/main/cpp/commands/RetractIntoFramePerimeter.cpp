// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/RetractIntoFramePerimeter.h"
#include "commands/ArmPosition.h"
#include "commands/RetractPartOne.h"
#include "commands/WristInitialPosition.h"
#include <frc2/command/WaitCommand.h>

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
RetractIntoFramePerimeter::RetractIntoFramePerimeter(Arm& arm, Wrist& wrist, double armAngle, double wristAngle) 
:CommandHelper{frc2::WaitCommand(units::second_t(0.75))}
{
  AddCommands
  (
    WristInitialPosition(wrist, wristAngle),
    ArmPosition(arm, armAngle)
  );
}
