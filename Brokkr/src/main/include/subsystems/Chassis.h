// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <frc/drive/DifferentialDrive.h>

#if ! __APPLE__
#include <AHRS.h>
#endif

#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/geometry/Translation2d.h>
#include <units/length.h>
#include "frc/Joystick.h"
#include "frc/XboxController.h"
#include <frc2/command/button/CommandJoystick.h>


class Chassis : public frc2::SubsystemBase {
 public:
  Chassis(WPI_TalonFX& leftFront, WPI_TalonFX& leftRear, WPI_TalonFX& rightFront, WPI_TalonFX& rightRear);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void ArcadeDrive(double speed, double rotation);
  double GetYawNavX();
  double GetPitchNavX();
  double EncoderTicksLeft();
  double EncoderTicksRight();
  void TankDriveVoltage(double left, double right);
  double GetRightMPS();
  double GetLeftMPS();
  void SetMaxOutput(double maxOutput);
  double GyroTurnRate();
  units::degree_t GetHeading() const;
  frc::DifferentialDriveWheelSpeeds GetWheelSpeeds();
  frc::Pose2d GetPose();
  void ResetOdometry(frc::Pose2d pose);
  void SetNeutralMode(NeutralMode mode);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  WPI_TalonFX& mLeftFront;
  WPI_TalonFX& mLeftRear;
  WPI_TalonFX& mRightFront;
  WPI_TalonFX& mRightRear;
  #if ! __APPLE__
  AHRS mGyroX{frc::SPI::kMXP};
  #endif
  frc::DifferentialDrive mDrive;
  frc2::CommandJoystick driver{0};
  frc::XboxController coDriver{1};

  frc::DifferentialDriveOdometry mOdometry;
  frc::DifferentialDriveKinematics mDriveKinematics;

  /*
  frc::Translation2d mLocationFrontRight{+12_in, +12.5_in};
  frc::Translation2d mLocationRearRight{+12_in, -12.5_in};
  frc::Translation2d mLocationFrontLeft{+12_in, -12.5_in};
  frc::Translation2d mLocationRearLeft{-12_in, -12.5_in};
  */
  //frc::DifferentialDriveKinematics mKinematics{25_in};
  //frc::DifferentialDriveOdometry mOdometry{mGyroX.GetRotation2d(), units::meter_t{0.0254* ticksToDistance(6)}, units::meter_t{0.0254* ticksToDistance(6)}, frc::Pose2d{5_m, 13.5_m, 0_rad}};
};
