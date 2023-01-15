// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>

class Wrist : public frc2::SubsystemBase {
 public:
  Wrist(WPI_TalonFX& wristMotor);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  double TurnWrist(double pos);
  bool IsWristFlicked() const;


 private:
 WPI_TalonFX& mWristMotor;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
