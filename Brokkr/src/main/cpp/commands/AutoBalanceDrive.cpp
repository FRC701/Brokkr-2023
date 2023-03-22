// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoBalanceDrive.h"
#include "commands/AutoForwardAndBackDrive.h"
#include "commands/AutoBalance.h"
#include "commands/ArmPosition.h"
#include "commands/SetExtendtoNode.h"
#include "commands/IntakeEjectObject.h"
#include "commands/RetractIntoFramePerimeter.h"


// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/stable/docs/software/commandbased/convenience-features.html
AutoBalanceDrive::AutoBalanceDrive(Chassis& mChassis, Arm& mArm, Claw& mClaw, Turret& mTurret, Wrist& mWrist) {
  // Add your commands here, e.g.
  // AddCommands(FooCommand{}, BarCommand{});
 AddCommands(ArmPosition(mArm, 75),
             SetExtendtoNode(mArm, mWrist, mTurret, 45),
             IntakeEjectObject(mClaw, -4),
             RetractIntoFramePerimeter(mArm, mWrist, 170, -60),
             AutoForwardAndBackDrive(mChassis, 11.5, 11.5, 2.5),
             AutoForwardAndBackDrive(mChassis, -11.5, -11.5, 1.25),
             AutoBalance(mChassis)
 );
}
