// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/SetArmPostitionForDistance.h"
#include <cmath>

namespace{
  
  double GetDistance(double height, double distance)
  {
    double armDistance = 0;
    return armDistance = sqrt(pow(height, 2) + pow(distance, 2));
  }
  double GetAngle(double height, double distance)
  {
    double angle = 0;
    return angle = atan(height/distance);
  }

  double GetNodeDistance(const NodeLevel& NodeLevel, double distance)
  {
    switch (NodeLevel)
    {
    case NodeLevel::HybridLevel:
      return GetDistance(0, distance);
      break;
    
    case NodeLevel::MiddleNodeLevel:
      return GetDistance(34, distance);
      break;
    
    case NodeLevel::UpperNodeLevel:
      return GetDistance(46, distance);
      break;
    }
  }

  double GetNodeAngle(const NodeLevel& NodeLevel, double distance)
  {
    switch (NodeLevel)
    {
    case NodeLevel::HybridLevel:
      return GetAngle(0, distance);
      break;
      
    case NodeLevel::MiddleNodeLevel:
      return GetAngle(34, distance);
      break;
    
    case NodeLevel::UpperNodeLevel:
      return GetAngle(46, distance);
      break;
    }
  }
  
}
SetArmPostitionForDistance::SetArmPostitionForDistance(Arm& arm, const NodeLevel& Level)
: mArm(arm)
, mLevel(Level)
 {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void SetArmPostitionForDistance::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SetArmPostitionForDistance::Execute() {
  GetNodeDistance(mLevel, 50);
  GetNodeAngle(mLevel, 50);
}

// Called once the command ends or is interrupted.
void SetArmPostitionForDistance::End(bool interrupted) {}

// Returns true when the command should end.
bool SetArmPostitionForDistance::IsFinished() {
  return false;
}
