// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>

class Claw : public frc2::SubsystemBase {
 public:
  Claw(WPI_TalonFX& intakeMotor);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  bool IsClawOpen() const;

  bool IsConeOrCubeIn(double CurrentThreshold);

  double GetControllerCurrent();

  double IntakeSpin(double speed);

 private:
  WPI_TalonFX& mIntakeMotor;

};
