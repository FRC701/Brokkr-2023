// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoDriveAndTurn.h"
#include "commands/AutoDriveOntoRamp.h"
#include "commands/AutoFeatureTurnToNode.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
AutoDriveAndTurn::AutoDriveAndTurn(Chassis& chassis, Turret& turret, Wrist& wrist, Arm& arm, Claw& claw, double turang, double chasdirec, double wrisang, double armang) 
{
  AddCommands
  (
  AutoDriveOntoRamp(chassis, 9, Chassis::DistanceToTicks(chasdirec)),
  AutoFeatureTurnToNode(wrist, turret, arm, armang, wrisang, turang)
  );
}
