// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <frc/drive/DifferentialDrive.h>

class Chassis : public frc2::SubsystemBase {
 public:
  Chassis(WPI_TalonFX& leftFront, WPI_TalonFX& leftRear, WPI_TalonFX& rightFront, WPI_TalonFX& rightRear);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void ArcadeDrive(double speed, double rotation);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  WPI_TalonFX& leftFront;
  WPI_TalonFX& leftRear;
  WPI_TalonFX& rightFront;
  WPI_TalonFX& rightRear;
  frc::DifferentialDrive mDrive;
};