// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Turret.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/SmartDashboard.h>

namespace{
    constexpr double RPMToTicks(double rpm)
  {
    double ticks = (rpm * 2048) / 10 / 60;
    return ticks;
  }
}

Turret::Turret(WPI_TalonFX& turret, WPI_PigeonIMU& gyro)
: mTurretMotor(turret)
, mGyro(gyro)
{
    mGyro.SetYaw(0);
    mTurretMotor.SetNeutralMode(Brake);}

 const double kTurretRotRestraint{20000};
// This method will be called once per scheduler run
void Turret::Periodic() {
    
 
  if (GetTurretPose() >= kTurretRotRestraint  && GetMotorSpeed() > 0)
  {
   SetTurretSpeed(0);
  }
  else if(GetTurretPose() <= -kTurretRotRestraint  && GetMotorSpeed() < 0)
  {
    SetTurretSpeed(0);
  }

    frc::SmartDashboard::PutBoolean("HasTargets?", HasTargets());
    frc::SmartDashboard::PutNumber("GetYawVision", GetVisionYaw());
    frc::SmartDashboard::PutNumber("GetPitchVision", GetVisionPitch());
    frc::SmartDashboard::PutNumber("GetAreaision", GetVisionArea());
    frc::SmartDashboard::PutNumber("GetVision", mCamera.GetPipelineIndex());
    frc::SmartDashboard::PutNumber("GetYawIMU", GetYawIMU());
    frc::SmartDashboard::PutNumber("GetTurretEncoderTicks", GetTurretPose());
}

double Turret::SetVelocity(double rpm)
{
    double speed = RPMToTicks(rpm);
    mTurretMotor.Set(ControlMode::Velocity, speed);
    return speed;
}

double Turret::SetTurretPose(double pose){
    mTurretMotor.Set(ControlMode::Position, pose);
        return pose;
}

double Turret::SetTurretSpeed(double speed){
    mTurretMotor.SetVoltage(units::volt_t(speed));
        return speed;
}

double Turret::GetTurretPose(){
    return mTurretMotor.GetSelectedSensorPosition();
}

double Turret::GetVisionArea(){
     photonlib::PhotonPipelineResult result = mCamera.GetLatestResult();
        return result.GetBestTarget().GetArea();
}

double Turret::GetVisionYaw(){
    photonlib::PhotonPipelineResult result = mCamera.GetLatestResult();
        return result.GetBestTarget().GetYaw();
}

double Turret::GetVisionPitch(){
    photonlib::PhotonPipelineResult result = mCamera.GetLatestResult();
        return result.GetBestTarget().GetPitch();
}
bool Turret::HasTargets(){
    photonlib::PhotonPipelineResult result = mCamera.GetLatestResult();
        return result.HasTargets();
}

void Turret::SetVisionLED(photonlib::LEDMode index){
    mCamera.SetLEDMode(index);
}

int Turret::SetPipeline(int pipeIndex){
    mCamera.SetPipelineIndex(pipeIndex);
        return pipeIndex;
}

double Turret::GetYawIMU(){
    return mGyro.GetYaw();
}


 double Turret::GetMotorSpeed(){
    return mTurretMotor.Get();
 }
    
