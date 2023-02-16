// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/SetArmPostitionForDistance.h"
#include <cmath>

 
  using namespace std::numbers;
namespace{

  double GetCameraDistance(double NodeHeight, double AngleTargetOffset)
  {   
    const double kCameraAngle = 45;
    const double kCameraHeight = 45;
  
    double robotDistance = 0;
    return robotDistance = (abs(NodeHeight - kCameraHeight))/tan(/*conversion to radians*/(pi/180)*(kCameraAngle + AngleTargetOffset));
  } //Trig math to find disance using angle of camera and height of chosen game object
  
  double GetDistance(double height, double distance)
  {
    const double kIntakeLengthfromPivot = 18.2;
    const double kTelescopeMechLength = 7.75;
    const double kExcessArmLength = 3.5;

    double armDistance = 0;
    return armDistance = sqrt(pow(height, 2) + pow(distance - kIntakeLengthfromPivot, 2)) - kExcessArmLength - kTelescopeMechLength;
  }//using pythagorean theorem to find ideal arm length
  double GetAngle(double height, double distance)
  {
    double angle = 0;
    return angle = atan(height/distance);
  } //Trig math by sam to find ideal angle when given x and y values
    const double kPlaceOffset = 3;
    const double ReflexTapeOffsetUpper = 1.75;
    const double ReflexTapeOffsetMiddle = 10.125;
    const double kHybridHeight = 0 + kPlaceOffset;
    const double kMiddleNodeHeight = 34 + kPlaceOffset - ReflexTapeOffsetMiddle;
    const double kUpperNodeHeight = 46 + kPlaceOffset - ReflexTapeOffsetUpper;

  double GetNodeDistance(const NodeLevel& NodeLevel, double AngleTargetOffset)
  {
    double distance = 0;
    double armDistance = 0;
    switch (NodeLevel)
    {
    case NodeLevel::HybridLevel:
      distance = GetCameraDistance(kHybridHeight, AngleTargetOffset);
      armDistance = GetDistance(kHybridHeight, distance);
      break;
    
    case NodeLevel::MiddleNodeLevel:
      distance = GetCameraDistance(kMiddleNodeHeight, AngleTargetOffset);
      armDistance = GetDistance(kMiddleNodeHeight, distance);
      break;
    
    case NodeLevel::UpperNodeLevel:
      distance = GetCameraDistance(kUpperNodeHeight, AngleTargetOffset);
      armDistance =  GetDistance(kUpperNodeHeight, distance);
      break;
    }
    return armDistance;
  }

  double GetNodeAngle(const NodeLevel& NodeLevel, double AngleTargetOffset)
  {
    double distance = 0;
    double armAngle = 0;
    switch (NodeLevel)
    {
    case NodeLevel::HybridLevel:
      distance = GetCameraDistance(kHybridHeight, AngleTargetOffset);
      armAngle = GetAngle(kHybridHeight, distance);
      break;
      
    case NodeLevel::MiddleNodeLevel:
      distance = GetCameraDistance(kMiddleNodeHeight, AngleTargetOffset);
      armAngle = GetAngle(kMiddleNodeHeight, distance);
      break;
    
    case NodeLevel::UpperNodeLevel:
      distance = GetCameraDistance(kUpperNodeHeight, AngleTargetOffset);
      armAngle = GetAngle(kUpperNodeHeight, distance);
      break;
    }
    return armAngle;
  }
  
}
SetArmPostitionForDistance::SetArmPostitionForDistance(Arm& arm, Turret& turret, const NodeLevel& Level)
: mArm(arm)
, mTurret(turret)
, mLevel(Level)
, mArmExtension{0, 0, 0}
, mArmPosition{0, 0, 0}
 {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(&mArm);
}

// Called when the command is initially scheduled.
void SetArmPostitionForDistance::Initialize() 
{
  mArmExtension.SetTolerance(1);
  mArmExtension.EnableContinuousInput(0, 20.5);
  mArmPosition.SetTolerance(1);
  mArmPosition.EnableContinuousInput(9, 86);
}

// Called repeatedly when this Command is scheduled to run
void SetArmPostitionForDistance::Execute() {
  double AngleTargetOffset = mTurret.GetVisionPitch();
  double desiredAngle = GetNodeAngle(mLevel, AngleTargetOffset);
  double desiredExtension = GetNodeDistance(mLevel, AngleTargetOffset);
  double outputE = mArmExtension.Calculate(mArm.GetExtendTicks(), mArm.DistanceToTicks(desiredExtension));
  double outputP = mArmPosition.Calculate(mArm.CANCoderArmStatus(), desiredAngle);
  mArm.SetArmSpeed(outputP);
  mArm.ArmExtend(outputE);
  // NEEDS TO BE FINISHED HAVING MOTORS SET TO DESIRED ANGLE
}

// Called once the command ends or is interrupted.
void SetArmPostitionForDistance::End(bool interrupted) {}

// Returns true when the command should end.
bool SetArmPostitionForDistance::IsFinished() {
  return mArmExtension.AtSetpoint() && mArmPosition.AtSetpoint();
}
