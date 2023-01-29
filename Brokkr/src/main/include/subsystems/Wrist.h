// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <frc/DigitalInput.h>

class Wrist : public frc2::SubsystemBase {
 public:
  Wrist(WPI_TalonFX& wristMotor, WPI_CANCoder& wristCoder, frc::DigitalInput& mWristMaxLim, frc::DigitalInput& mWristMinLim);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  double TurnWrist(double pos);
  bool IsWristFlicked() const;
  double GetWristPosition();
  double TurnWristPO(double speed);
  bool WristMaxLimitSwitch();
  bool WristMinLimitSwitch();
  

 
 private:
 WPI_TalonFX& mWristMotor;
 WPI_CANCoder& mWristCoder;
 frc::DigitalInput& mWristMaxLim;
 frc::DigitalInput& mWristMinLim;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
