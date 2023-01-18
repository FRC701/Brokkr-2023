// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Turret.h"
#include <frc/smartdashboard/SmartDashboard.h>

Turret::Turret(WPI_TalonFX& mTurret, WPI_PigeonIMU& mGyro)
: TurretMotor(mTurret)
, gyro(mGyro)
{}

// This method will be called once per scheduler run
void Turret::Periodic() {}