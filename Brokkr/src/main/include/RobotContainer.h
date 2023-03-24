// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/button/CommandXboxController.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/button/Button.h>
#include <frc/Joystick.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/button/CommandJoystick.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc2/command/button/CommandGenericHID.h>

#include "Constants.h"
#include "subsystems/ExampleSubsystem.h"
#include "subsystems/Arm.h"
#include "subsystems/Chassis.h"
#include "subsystems/Claw.h"
#include "subsystems/Turret.h"
#include "subsystems/Wrist.h"
#include "commands/AutoTwoPieceTaxi.h"
#include "commands/AutoBalanceDrive.h"
#include "commands/AutoDriveOntoRamp.h"
#include "commands/AutoHighMidNodeTaxi.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and trigger mappings) should be declared here.
 */
class RobotContainer 
{
 public:
  RobotContainer();

  static constexpr  int kArmMotor2{2};
  static constexpr  int kTelescope{3};
  static constexpr  int kArmCoder{14};


  static constexpr  int kLeftFrontChassis{4};
  static constexpr  int kLeftRearChassis{5};
  static constexpr  int kRightFrontChassis{6};
  static constexpr  int kRightRearChassis{7};
  
  static constexpr  int kIntakeMotor{9};
  static constexpr  int kWristCoder{13};
  
  static constexpr  int kTurretMotor{10};
  static constexpr  int kGyroTurret{11};
  
  static constexpr  int kWristMotor{12};

  double kCommunityZoneDepth = 16.0 * 12.0;
  double kAllianceGridDepth = (4.0 * 12.0) + 6.25;
  double kCommunityZoneDriveDepth = kCommunityZoneDepth - kAllianceGridDepth;

  frc2::Command* GetAutonomousCommand();

 private:

 frc::SendableChooser<frc2::Command*> mChooser;
 //frc::Joystick driver{0};
 //frc::XboxController driver1{0};
 frc2::CommandJoystick driver{0};
 frc2::CommandXboxController coDriver{1};
 frc2::CommandGenericHID coDriver2{1};

 frc2::Trigger trigger = driver.Trigger();
 frc2::Trigger button3 = driver.Button(3);
 frc2::Trigger button4 = driver.Button(4);
 frc2::Trigger button5 = driver.Button(5);
 frc2::Trigger button6 = driver.Button(6);
 frc2::Trigger button7 = driver.Button(7);
 frc2::Trigger button8 = driver.Button(8);
 frc2::Trigger button9 = driver.Button(9);
 frc2::Trigger button10 = driver.Button(10);
 frc2::Trigger button11 = driver.Button(11);
 frc2::Trigger button12 = driver.Button(12);


 frc2::Trigger xButton = coDriver.X();
 frc2::Trigger yButton = coDriver.Y();
 frc2::Trigger aButton = coDriver.A();
 frc2::Trigger bButton = coDriver.B();
 frc2::Trigger lBumperButton = coDriver.LeftBumper();
 frc2::Trigger rBumperButton = coDriver.RightBumper();
 frc2::Trigger lTrigger = coDriver.LeftTrigger();
 frc2::Trigger rTrigger = coDriver.RightTrigger();
 frc2::Trigger Middle = coDriver.Button(6);
 frc2::Trigger upDPAD = coDriver2.POVUp();
 frc2::Trigger downDPAD = coDriver2.POVDown();

  // Replace with CommandPS4Controller or CommandJoystick if needed
  frc2::CommandXboxController m_driverController{
      OperatorConstants::kDriverControllerPort};

  // The robot's subsystems are defined here...
  ExampleSubsystem m_subsystem;
  WPI_TalonFX ArmMotor2{kArmMotor2};
  WPI_TalonFX TelescopingArm{kTelescope};
  WPI_CANCoder CanCoder{kArmCoder};
  Arm mArm{ArmMotor2, TelescopingArm, CanCoder};

  WPI_TalonFX leftFront{kLeftFrontChassis};
  WPI_TalonFX leftRear{kLeftRearChassis};
  WPI_TalonFX rightFront{kRightFrontChassis};
  WPI_TalonFX rightRear{kRightRearChassis};
  Chassis mChassis{leftFront, leftRear, rightFront, rightRear};

  WPI_TalonFX mIntakeMotor{kIntakeMotor};
  Claw mClaw{mIntakeMotor};

  WPI_TalonFX TurretMotor{kTurretMotor};
  WPI_PigeonIMU gyro{kGyroTurret};
  Turret mTurret{TurretMotor, gyro};

  WPI_TalonFX mWristMotor{kWristMotor};
  WPI_CANCoder mWristCoder{kWristCoder};
  Wrist mWrist{mWristMotor, mWristCoder}; 

 //AutoTwoPieceTaxi mAutoTwoPieceTaxi{mArm, mChassis, mClaw, mWrist, mTurret};

  //AutoBalanceDrive mAutoBalanceDrive{mChassis, mArm, mClaw, mTurret, mWrist};

  AutoDriveOntoRamp mAutoDriveOntoRamp{mChassis, 0.25, 86500};

  AutoDriveOntoRamp mAutoTaxi{mChassis, -0.25, -Chassis::DistanceToTicks(110.0 /* 99.0 - 16.0 */)};

  AutoHighMidNodeTaxi mAutoMidNodeTaxi{mArm, mTurret, mWrist, mChassis, mClaw, Chassis::DistanceToTicks(kCommunityZoneDepth)};

  AutoHighMidNodeTaxi mAutoMidNodeBalance{mArm, mTurret,mWrist, mChassis, mClaw, 86500};

  void ConfigureBindings();
};
