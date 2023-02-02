// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <gtest/gtest.h>
#include <frc/simulation/PWMSim.h>

#include "subsystems/Arm.h"
#include "commands/SetArmPostitionForDistance.h"

class ArmPositionForDistanceCommandTest : public testing::Test {
 protected:
  WPI_TalonFX armM1{1};
  WPI_TalonFX armM2{2};
  WPI_TalonFX teleArm{3};
  WPI_TalonFX turretMotor{11};
  WPI_CANCoder canCoder{13};
  WPI_PigeonIMU gyro{10};

  Arm mArm {armM1, armM2, teleArm, canCoder};
  Turret mTurret {turretMotor, gyro};

  SetArmPostitionForDistance mCommand {mArm, mTurret, NodeLevel::MiddleNodeLevel};
};
