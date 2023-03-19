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
#include "commands/IntakeSpinSimple.h"
#include "commands/IntakeEjectObject.h"
#include "commands/PivotWrist.h"
#include "commands/ManualArmAngle.h"
#include "commands/RetractIntoFramePerimeter.h"
#include "commands/TurnTurretAndExtendToNode.h"
#include "commands/AutoForwardAndBackDrive.h"
#include "commands/TurretPID.h"
#include "commands/ControllerTurret.h"
#include "commands/ControllerChassisRotationReal.h"
#include "commands/ControllerChassisDrive.h"
#include "commands/GetArmPosition.h"
#include "commands/GetArmInitialPosition.h"
#include "commands/GetWristInitialPosition.h"
#include "commands/GetIntakeSpin.h"
#include "commands/GetTurretPID.h"
#include "commands/SetNeutralModeToBrake.h"

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
 frc::SmartDashboard::SetDefaultNumber("ArmAngle", 5);
 frc::SmartDashboard::SetDefaultNumber("ExtensionLength", 0);
 frc::SmartDashboard::SetDefaultNumber("WristAngle", 0);
 frc::SmartDashboard::SetDefaultNumber("IntakeCurrentLimit", 0);
 frc::SmartDashboard::SetDefaultNumber("TurretAngle", 0);

 frc::SmartDashboard::PutData("Get Turret Positin", new GetTurretPID(mTurret));
 frc::SmartDashboard::PutData("Get Arm Position", new GetArmPosition(mArm));
 frc::SmartDashboard::PutData("Get Arm Extension", new GetArmInitialPosition(mArm));
 frc::SmartDashboard::PutData("Get Wrist Position", new GetWristInitialPosition(mWrist));
 frc::SmartDashboard::PutData("Get Intake Current Limit", new GetIntakeSpin(mClaw));

 frc::SmartDashboard::PutData("ArmPosition Hybrid", new ArmPosition(mArm, 0)); //Placeholder values
 frc::SmartDashboard::PutData("InitClaw", new WristInitialPosition(mWrist, 0));

 frc::SmartDashboard::PutData("spin", new IntakeSpinSimple(mClaw, 7));

 frc::SmartDashboard::PutData("Turret pose 80 degree", new TurretPID(mTurret, 80));
 frc::SmartDashboard::PutData("ArmPosition 20 degree", new ArmPosition(mArm, 20));
 frc::SmartDashboard::PutData("ArmPosition 40 degree", new ArmPosition(mArm, 40));
 frc::SmartDashboard::PutData("ArmPosition 60 degree", new ArmPosition(mArm, 60));
 frc::SmartDashboard::PutData("ArmPosition 80 degree", new ArmPosition(mArm, 80));
 frc::SmartDashboard::PutData("ArmExtension", new ArmInitialPosition(mArm, 4));
 frc::SmartDashboard::PutData("Wrist angle 300 degree", new WristInitialPosition(mWrist, 300));
 
 frc::SmartDashboard::PutData("SetArmPosition", new ArmInitialPosition(mArm, 0));
 frc::SmartDashboard::PutData("Wow", new SetArmPostitionForDistance(mArm, mTurret, NodeLevel::HybridLevel));
 frc::SmartDashboard::PutData("Auto Forward for 2.5 sec", new AutoForwardAndBackDrive(mChassis, 11.5, 11.5, 2.5));
 frc::SmartDashboard::PutData("Auto Back for 1.25 sec", new AutoForwardAndBackDrive(mChassis, -11.5, -11.5, 1.25));

 frc::SmartDashboard::PutData("Turret Lock Onto Object", new ControllerTurret(mTurret));
 frc::SmartDashboard::PutData("Chassis Lock with Turret Yaw", new ControllerChassisRotationReal(mChassis, mTurret));
 frc::SmartDashboard::PutData("Chassis Drive to object", new ControllerChassisDrive(mChassis, mTurret));
 frc::SmartDashboard::PutData("Transsform", new RetractIntoFramePerimeter(mArm, mWrist));

mChooser.AddOption("Auto Balance Drive", &mAutoBalanceDrive);
mChooser.AddOption("Auto 2 Piece", &mAutoTwoPieceTaxi);
mChooser.AddOption("Auto (Ramp) Drive", &mAutoDriveOntoRamp);
mChooser.AddOption("Auto Score and Drive", &mAutoHighMidNodeTaxi);

frc::SmartDashboard::PutData("Autonomous Chooser", &mChooser);


  //mClaw.SetDefaultCommand(IntakeSpinSimple(mClaw, 0.0));
  // Disable while testing. 18
   mWrist.SetDefaultCommand(PivotWrist(mWrist, 0));
  // Configure the button bindings
  ConfigureBindings();

  #define CHASSIS_ENABLE
  #ifdef CHASSIS_ENABLE
  mChassis.SetDefaultCommand
  (
    ArcadeDrive
    (
      mChassis,
      [this] {return -(-driver.GetThrottle()+1)/2 * driver.GetY(); },
      [this] {return -0.95*((-driver.GetThrottle()+1)/2) * driver.GetTwist(); }
    )
  );
#endif

  //mTurret.SetDefaultCommand(TurretManualControl(mTurret, 0.0));

  mArm.SetDefaultCommand(ManualArmAngle(mArm, 0.0));

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
  trigger.ToggleOnTrue(RetractIntoFramePerimeter(mArm, mWrist).ToPtr()); //placeholder
  //button5.WhileTrue(IntakeSpinSimple(mClaw, 6).ToPtr());
  button5.ToggleOnTrue(IntakeSpin(mClaw, 7.5).ToPtr());
  button6.ToggleOnTrue(IntakeSpin(mClaw, -7.5).ToPtr());
  
  //button6.WhileTrue(IntakeSpinSimple(mClaw, -6).ToPtr());
  button7.ToggleOnTrue(TurnTurretAndExtendToNode(mArm, mWrist, mTurret, NodeLevel::UpperNodeLevel, 45).ToPtr()); //placeholder
  button8.ToggleOnTrue(IntakeEjectObject(mClaw, -6).ToPtr());
  button9.ToggleOnTrue(TurnTurretAndExtendToNode(mArm, mWrist, mTurret, NodeLevel::MiddleNodeLevel, 100).ToPtr()); //placeholder
  button10.ToggleOnTrue(IntakeEjectObject(mClaw, 6).ToPtr());
  button11.ToggleOnTrue(TurnTurretAndExtendToNode(mArm, mWrist, mTurret, NodeLevel::HybridLevel, 120).ToPtr()); //placeholder
  

  xButton.ToggleOnTrue(MoveArmIntake(-5.5, mArm,mWrist, mClaw, -7, 45).ToPtr()); // sky cone
  yButton.ToggleOnTrue(MoveArmIntake(-6.5, mArm, mWrist, mClaw, -60, 80).ToPtr()); // floor cone
  bButton.ToggleOnTrue(MoveArmIntake(5.5, mArm, mWrist, mClaw, -70, 120).ToPtr()); // sky cube
  aButton.ToggleOnTrue(MoveArmIntake(5.5, mArm, mWrist, mClaw, -70, 120).ToPtr()); // floor cube
  //xButton.ToggleOnFalse(RetractIntoFramePerimeter(mArm, mWrist).ToPtr());
  //yButton.ToggleOnFalse(RetractIntoFramePerimeter(mArm, mWrist).ToPtr());
  //aButton.WhileTrue(ExtendArm(mArm, -8).ToPtr())[]\; // Retract arm
  lTrigger.WhileTrue(ManualArmAngle(mArm, 3).ToPtr()); // Raise Arm
  rTrigger.WhileTrue(ManualArmAngle(mArm, -3).ToPtr()); // Lower Arm
  upDPAD.WhileTrue(PivotWrist(mWrist, -3).ToPtr()); // Raise Wrist
  downDPAD.WhileTrue(PivotWrist(mWrist, 3).ToPtr()); // Lower Wrist 
  lBumperButton.WhileTrue(TurretManualControl(mTurret, 6).ToPtr()); //Turn Turret Left
  rBumperButton.WhileTrue(TurretManualControl(mTurret, -6).ToPtr()); //Turn Turret Right
  Middle.ToggleOnTrue(RetractIntoFramePerimeter(mArm, mWrist).ToPtr());

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
  return mChooser.GetSelected();
}
