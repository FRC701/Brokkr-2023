// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <photonlib/PhotonCamera.h>

class Turret : public frc2::SubsystemBase {
 public:
  Turret(WPI_TalonFX& turretMotor, WPI_PigeonIMU& gyro);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  double SetVelocity(double rpm);
  double SetTurretPose(double pose);
  double SetTurretSpeed(double speed);
  double GetTurretPose();
  double GetVisionYaw();
  double GetVisionPitch();
  double GetVisionArea();
  bool HasTargets();
  void SetVisionLED(photonlib::LEDMode index);
  int SetPipeline(int pipeIndex);
  void Periodic() override;
  double GetYawIMU();

 private:
 WPI_TalonFX& mTurretMotor;
 WPI_PigeonIMU& mGyro;

  photonlib::PhotonCamera mCamera{"photonvision"}; 
    // It is recommended to Build Robot Code at least once when connected 
    // to the Internet before heading to an area where Internet connectivity 
    // is limited (for example, a competition). This ensures that the relevant 
    // files are downloaded to your filesystem.*

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
