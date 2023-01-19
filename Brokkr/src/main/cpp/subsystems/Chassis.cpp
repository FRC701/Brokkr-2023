// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Chassis.h"
#include <frc/smartdashboard/SmartDashboard.h>

using ControlMode = ctre::phoenix::motorcontrol::ControlMode;
using WPI_TalonFX = ctre::phoenix::motorcontrol::can::WPI_TalonFX;

Chassis::Chassis(WPI_TalonFX& leftFront, WPI_TalonFX& leftRear, WPI_TalonFX& rightFront, WPI_TalonFX& rightRear)
:leftFront(leftFront)
,leftRear(leftRear)
,rightFront(rightFront)
,rightRear(rightRear)
,mDrive(leftFront, rightFront)
{
    gyroX.ZeroYaw();
    leftFront.Config_kP(0, 0, 0);
    leftFront.Config_kI(0, 0, 0);
    leftFront.Config_kD(0, 0, 0);
    leftFront.Config_kF(0, 0, 0);

    rightFront.Config_kP(0, 0, 0);
    rightFront.Config_kI(0, 0, 0);
    rightFront.Config_kD(0, 0, 0);
    rightFront.Config_kF(0, 0, 0);

    leftRear.Follow(leftFront);
    rightRear.Follow(rightFront);
}

// This method will be called once per scheduler run
void Chassis::Periodic() {
    frc::SmartDashboard::PutNumber("Chassis Yaw", GetYawNavX());
    frc::SmartDashboard::PutNumber("Chassis Pitch", GetPitchNavX());
}

void Chassis::ArcadeDrive(double speed, double rotation) 
{
    mDrive.ArcadeDrive(speed, rotation);
}
 double Chassis::GetYawNavX(){
    return gyroX.GetYaw();
 }

 double Chassis::GetPitchNavX(){
    return gyroX.GetPitch();
 }