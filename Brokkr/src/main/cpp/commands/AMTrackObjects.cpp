// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AMTrackObjects.h"

AMTrackObjects::AMTrackObjects(Turret& turret, Chassis& chassis, int pipelineIndex)
: mTurret(turret)
, mChassis(chassis)
, mPipelineIndex(pipelineIndex)
{
  AddRequirements(&mChassis);// Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void AMTrackObjects::Initialize() {
  mTurret.SetPipeline(mPipelineIndex);  //Set what game object u want to drive towards
  mTrackState = HasTarget;
        controllerT.SetTolerance(0.0); //placeholder values
        controllerCD.SetTolerance(0.0);
        controllerC.SetTolerance(0.0);
}

// Called repeatedly when this Command is scheduled to run
void AMTrackObjects::Execute() {
  double outputT = 0;
  double outputC = 0;
  double outputCD = 0;
  switch (mTrackState)
  {
  case HasTarget:
      if(mTurret.HasTargets())
      {
        mTrackState = TurretFacingTarget; //Sees if limelight has targets
      }
      else
      {
        NoTargets = true;
      }
    break; 
  case TurretFacingTarget:
      outputT = controllerT.Calculate(mTurret.GetVisionYaw(), 0); //Trys to align turret to get vision target to 0 yaw(I think is equivalent of 0 on x axis)
      if(controllerT.AtSetpoint())
      {
        mTurret.SetTurretSpeed(0);
        mTrackState = ChassisAlignDrive;
      }
      else{
        mTurret.SetTurretSpeed(outputT);
      }
    break;

  case ChassisAlignDrive:
      outputC = controllerC.Calculate(mChassis.GetYawNavX(), mTurret.GetYawIMU()); //Assuming heading is the same on both gyros
      outputCD = controllerCD.Calculate(mTurret.GetVisionArea(), 100); //Drives until gameobject is in precalculated distance represented by vision area
      mChassis.ArcadeDrive(outputCD, outputC); //Drives forward whilst turning to realign with turret
      if(controllerCD.AtSetpoint()){ //not sure if code here is ideal
        mChassis.ArcadeDrive(0, outputC);
        outputC = 0;
      }
      if(controllerC.AtSetpoint()){
        mChassis.ArcadeDrive(outputCD, 0);
        outputCD = 0;
      } 
      break;
  }
}

// Called once the command ends or is interrupted.
void AMTrackObjects::End(bool interrupted) {}

// Returns true when the command should end.
bool AMTrackObjects::IsFinished() {
  return (controllerCD.AtSetpoint() && controllerC.AtSetpoint())|| NoTargets; //Ends whether robot is at the setpoint or has no targets
}
