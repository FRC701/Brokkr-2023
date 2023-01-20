// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "commands/Autos.h"
#include "commands/ExampleCommand.h"
#include "commands/ArmPosition.h"

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
 frc::SmartDashboard::PutData("ArmPosition Hybrid", new ArmPosition(mArm, 0)); //Placeholder values
 frc::SmartDashboard::PutData("ArmPosition Mid", new ArmPosition(mArm, 0));
 frc::SmartDashboard::PutData("ArmPosition High", new ArmPosition(mArm, 0));
 frc::SmartDashboard::PutData("ArmPosition Shelf", new ArmPosition(mArm, 0));
  // Configure the button bindings
  ConfigureBindings();
}

void RobotContainer::ConfigureBindings() {
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
