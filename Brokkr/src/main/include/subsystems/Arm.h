// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>

class Arm : public frc2::SubsystemBase {
 public:
  Arm(WPI_TalonFX& mArmM1, WPI_TalonFX& mArmM2, WPI_TalonFX& mTeleArm);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  double SetArmHeight(double pose);
  double ArmExtend(double pose);

  enum eArmStatus {
    UNKNOWN = -1,
    HIGH = 0,
    MID,
    HYBRID
  };

  eArmStatus GetArmStatus();

  static const char* AsString(const eArmStatus status);

 private:

 WPI_TalonFX& ArmMotor1;
 WPI_TalonFX& ArmMotor2;
 WPI_TalonFX& TelescopingArm;

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
