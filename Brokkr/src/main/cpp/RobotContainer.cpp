// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "commands/Autos.h"
#include "commands/ExampleCommand.h"
#include "commands/ArmPosition.h"
#include "commands/WristLevel.h"
#include "commands/RunTurret.h"


RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
 frc::SmartDashboard::PutData("ArmPosition Hybrid", new ArmPosition(mArm, 0)); //Placeholder values
 frc::SmartDashboard::PutData("ArmPosition Mid", new ArmPosition(mArm, 0));
 frc::SmartDashboard::PutData("ArmPosition High", new ArmPosition(mArm, 0));
 frc::SmartDashboard::PutData("ArmPosition Shelf", new ArmPosition(mArm, 0));

  mArm.SetDefaultCommand(WristLevel(mWrist, mArm));
  // Configure the button bindings
  ConfigureBindings();


}

void RobotContainer::ConfigureBindings() 
{
<<<<<<< Updated upstream
  frc2::Button driverTrigger{[this]{return driver.GetRawButton(1);}};
  frc2::Button driverThumbButton{[this]{return driver.GetRawButton(2);}};
  frc2::Button driverTopButton3{[this]{return driver.GetRawButton(3);}};
  frc2::Button driverTopButton4{[this]{return driver.GetRawButton(4);}};
  frc2::Button driverTopButton5{[this]{return driver.GetRawButton(5);}};
  frc2::Button driverTopButton6{[this]{return driver.GetRawButton(6);}};

  frc2::Button codriverA{[this]{return coDriver.GetRawButton(1);}};
  frc2::Button codriverB{[this]{return coDriver.GetRawButton(2);}};
  frc2::Button codriverX{[this]{return coDriver.GetRawButton(3);}};
  frc2::Button codriverY{[this]{return coDriver.GetRawButton(4);}};
=======
  trigger.ToggleOnTrue(RunTurret(mTurret, 0.5).ToPtr()); //placeholder
  button1.ToggleOnTrue(RunTurret(mTurret,0.5).ToPtr()); //placeholder
  button2.ToggleOnTrue(RunTurret(mTurret, 0.5).ToPtr()); //placeholder
  button3.ToggleOnTrue(RunTurret(mTurret, 0.5).ToPtr()); //placeholder
  button4.ToggleOnTrue(RunTurret(mTurret, 0.5).ToPtr()); //placeholder
  button5.ToggleOnTrue(RunTurret(mTurret, 0.5).ToPtr()); //placeholder


  xButton.WhileTrue(RunTurret(mTurret, 0.5).ToPtr());
  yButton.WhileTrue(RunTurret(mTurret, 0.5).ToPtr()); //placeholder
  aButton.WhileTrue(RunTurret(mTurret, 0.5).ToPtr()); //placeholder
  bButton.WhileTrue(RunTurret(mTurret, 0.5).ToPtr()); //placeholder
>>>>>>> Stashed changes

  codriverA.WhileHeld(RunTurret(mTurret, 0.5)); //placeholder
  codriverB.WhileHeld(RunTurret(mTurret, -0.5)); //placeholder

  // Configure your trigger bindings here
  // Schedule `ExampleCommand` when `exampleCondition` changes to `true`
  frc2::Trigger([this] {
    return m_subsystem.ExampleCondition();
  }).OnTrue(ExampleCommand(&m_subsystem).ToPtr());

  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
  m_driverController.B().WhileTrue(m_subsystem.ExampleMethodCommand());
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return autos::ExampleAuto(&m_subsystem);
}
