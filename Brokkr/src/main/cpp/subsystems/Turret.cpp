// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Turret.h"
#include <frc/smartdashboard/SmartDashboard.h>

Turret::Turret(WPI_TalonFX& mTurret)
:TurretMotor(mTurret)
{
}

// This method will be called once per scheduler run
void Turret::Periodic() {
    frc::SmartDashboard::PutBoolean("HasTargets?", HasTargets());
    frc::SmartDashboard::PutNumber("GetYawVision", GetVisionYaw());
    frc::SmartDashboard::PutNumber("GetPitchVision", GetVisionPitch());
    frc::SmartDashboard::PutNumber("GetAreaision", GetVisionArea());
    frc::SmartDashboard::PutNumber("GetVision", camera.GetPipelineIndex());
}

double Turret::GetTurretPose(){
    return TurretMotor.GetSelectedSensorPosition();
}

double Turret::GetVisionArea(){
     photonlib::PhotonPipelineResult result = camera.GetLatestResult();
        return result.GetBestTarget().GetArea();
}

double Turret::GetVisionYaw(){
    photonlib::PhotonPipelineResult result = camera.GetLatestResult();
        return result.GetBestTarget().GetYaw();
}

double Turret::GetVisionPitch(){
    photonlib::PhotonPipelineResult result = camera.GetLatestResult();
        return result.GetBestTarget().GetPitch();
}
bool Turret::HasTargets(){
    photonlib::PhotonPipelineResult result = camera.GetLatestResult();
        return result.HasTargets();
}

void Turret::SetVisionLED(photonlib::LEDMode index){
    camera.SetLEDMode(index);
}

int Turret::SetPipeline(int pipeIndex){
    camera.SetPipelineIndex(pipeIndex);
        return pipeIndex;
}

double Turret::SetTurretPose(double pose){
    TurretMotor.Set(pose);
        return pose;
}
