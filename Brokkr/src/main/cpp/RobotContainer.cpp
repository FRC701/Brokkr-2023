// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "commands/Autos.h"
#include "commands/ExampleCommand.h"
#include "commands/ArcadeDrive.h"
#include "commands/ArmPosition.h"
#include "commands/WristLevel.h"
#include "commands/RunTurret.h"
#include "commands/ExtendArm.h"
#include "commands/ArmInitialPosition.h"
#include "commands/WristInitialPosition.h"
#include "commands/SetArmPostitionForDistance.h"
#include "commands/TurretManualControl.h"
#include "commands/MoveArmIntake.h"
#include "commands/IntakeSpin.h"
#include "commands/IntakeEjectObject.h"
#include "commands/PivotWrist.h"
#include "commands/ManualArmAngle.h"
#include "commands/RetractIntoFramePerimeter.h"
#include "commands/TurnTurretAndExtendToNode.h"


RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
 frc::SmartDashboard::PutData("ArmPosition Hybrid", new ArmPosition(mArm, 0)); //Placeholder values
 frc::SmartDashboard::PutData("InitClaw", new WristInitialPosition(mWrist, 0));
 frc::SmartDashboard::PutData("ArmPosition Mid", new ArmPosition(mArm, 0));
 frc::SmartDashboard::PutData("ArmPosition High", new ArmPosition(mArm, 0));
 frc::SmartDashboard::PutData("ArmPosition Shelf", new ArmPosition(mArm, 0));
 frc::SmartDashboard::PutData("SetArmPosition", new ArmInitialPosition(mArm, 0));
 frc::SmartDashboard::PutData("Wow", new SetArmPostitionForDistance(mArm, mTurret, NodeLevel::HybridLevel));



  mWrist.SetDefaultCommand(WristLevel(mWrist, mArm));
  // Configure the button bindings
  ConfigureBindings();

  mChassis.SetDefaultCommand
  (
    ArcadeDrive
    (
      mChassis,
      [this] {return -1.0*driver.GetY(); },
      [this] {return -1.0*driver.GetTwist(); }
    )
  );
  /*mWrist.SetDefaultCommand
  (
    PivotWrist
    (
      mWrist,
      [this] {return -0.4*coDriver.GetRightY();}
    )
  );*/
}
void RobotContainer::ConfigureBindings() 
{
  trigger.ToggleOnTrue(MoveArmIntake(mArm, mClaw, 135).ToPtr()); //placeholder
  button7.ToggleOnTrue(TurnTurretAndExtendToNode(mArm, mTurret, NodeLevel::UpperNodeLevel).ToPtr()); //placeholder
  button9.ToggleOnTrue(TurnTurretAndExtendToNode(mArm, mTurret, NodeLevel::MiddleNodeLevel).ToPtr()); //placeholder
  button11.ToggleOnTrue(TurnTurretAndExtendToNode(mArm, mTurret, NodeLevel::HybridLevel).ToPtr()); //placeholder
  

  xButton.ToggleOnTrue(MoveArmIntake(mArm, mClaw, 45).ToPtr()); //Select arm height and run intake
  yButton.WhileTrue(ExtendArm(mArm, 0.3).ToPtr()); // Extend arm
  aButton.WhileTrue(ExtendArm(mArm, -0.3).ToPtr()); // Retract arm
  bButton.ToggleOnTrue(IntakeEjectObject(mClaw).ToPtr()); //Release Game Object
  lTrigger.WhileTrue(ManualArmAngle(mArm, 0.3).ToPtr()); // Raise Arm
  rTrigger.WhileTrue(ManualArmAngle(mArm, -0.3).ToPtr()); // Lower Arm
  upDPAD.WhileTrue(PivotWrist(mWrist, 0.3).ToPtr()); // Raise Wrist
  downDPAD.WhileTrue(PivotWrist(mWrist, -0.3).ToPtr()); // Lower Wrist 
  lBumperButton.WhileTrue(TurretManualControl(mTurret,-200).ToPtr()); //Turn Turret Left
  rBumperButton.WhileTrue(TurretManualControl(mTurret, 200).ToPtr()); //Turn Turret Right
  Middle.ToggleOnTrue(RetractIntoFramePerimeter(mArm, mWrist, mClaw, mTurret).ToPtr());

  // Configure your trigger bindings here
  // Schedule `ExampleCommand` when `exampleCondition` changes to `true`
  frc2::Trigger([this] {
    return m_subsystem.ExampleCondition();
  }).OnTrue(ExampleCommand(&m_subsystem).ToPtr());

  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
  m_driverController.B().WhileTrue(m_subsystem.ExampleMethodCommand());
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  frc::SmartDashboard::PutData("Autonomous Chooser", &mChooser);

  return mChooser.GetSelected();
}
