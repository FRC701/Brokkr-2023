// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/SetArmPostitionForDistance.h"
#include <cmath>

namespace{

  double GetCameraDistance(double NodeHeight, double AngleTargetOffset)
  {   
    const double kCameraAngle = 45;
    const double kCameraHeight = 36;
  
    double robotDistance = 0;
    return robotDistance = (NodeHeight - kCameraHeight)/tan(/*conversion to radians*/(3.14152653589/180)*(kCameraAngle + AngleTargetOffset));
  } //Trig math to find disance using angle of camera and height of chosen game object
  
  double GetDistance(double height, double distance)
  {
    double armDistance = 0;
    return armDistance = sqrt(pow(height, 2) + pow(distance, 2));
  }//using pythagorean theorem to find ideal arm length
  double GetAngle(double height, double distance)
  {
    double angle = 0;
    return angle = atan(height/distance);
  } //Trig math by sam to find ideal angle when given x and y values

    const double kHybridHeight = 0;
    const double kMiddleNodeHeight = 34;
    const double kUpperNodeHeight = 46;

  double GetNodeDistance(const NodeLevel& NodeLevel, double AngleTargetOffset)
  {
    double distance = 0;
    switch (NodeLevel)
    {
    case NodeLevel::HybridLevel:
      distance = GetCameraDistance(kHybridHeight, AngleTargetOffset);
      return GetDistance(kHybridHeight, distance);
      break;
    
    case NodeLevel::MiddleNodeLevel:
      distance = GetCameraDistance(kMiddleNodeHeight, AngleTargetOffset);
      return GetDistance(kMiddleNodeHeight, distance);
      break;
    
    case NodeLevel::UpperNodeLevel:
      distance = GetCameraDistance(kUpperNodeHeight, AngleTargetOffset);
      return GetDistance(kUpperNodeHeight, distance);
      break;
    }
  }

  double GetNodeAngle(const NodeLevel& NodeLevel, double AngleTargetOffset)
  {
    double distance = 0;
    switch (NodeLevel)
    {
    case NodeLevel::HybridLevel:
      distance = GetCameraDistance(kHybridHeight, AngleTargetOffset);
      return GetAngle(kHybridHeight, distance);
      break;
      
    case NodeLevel::MiddleNodeLevel:
      distance = GetCameraDistance(kMiddleNodeHeight, AngleTargetOffset);
      return GetAngle(kMiddleNodeHeight, distance);
      break;
    
    case NodeLevel::UpperNodeLevel:
      distance = GetCameraDistance(kUpperNodeHeight, AngleTargetOffset);
      return GetAngle(kUpperNodeHeight, distance);
      break;
    }
  }
  
}
SetArmPostitionForDistance::SetArmPostitionForDistance(Arm& arm, Turret& turret, const NodeLevel& Level)
: mArm(arm)
, mTurret(turret)
, mLevel(Level)
 {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(&mArm);
}

// Called when the command is initially scheduled.
void SetArmPostitionForDistance::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void SetArmPostitionForDistance::Execute() {
  double AngleTargetOffset = mTurret.GetVisionPitch();
  GetNodeAngle(mLevel, AngleTargetOffset);
  GetNodeDistance(mLevel, AngleTargetOffset);
  // NEEDS TO BE FINISHED HAVING MOTORS SET TO DESIRED ANGLE
}

// Called once the command ends or is interrupted.
void SetArmPostitionForDistance::End(bool interrupted) {}

// Returns true when the command should end.
bool SetArmPostitionForDistance::IsFinished() {
  return false;
}
