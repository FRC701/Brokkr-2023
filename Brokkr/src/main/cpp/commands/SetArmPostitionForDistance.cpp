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
    const double kIntakeLengthfromPivot = 24.6;
    const double kTelescopeMechLength = 23.875;

    double armDistance = 0;
    return armDistance = sqrt(pow(height, 2) + pow(distance - kIntakeLengthfromPivot, 2)) - kTelescopeMechLength;
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

  [[maybe_unused]]
  double GetNodeDistance(const NodeLevel& NodeLevel, double AngleTargetOffset)
  {
    double distance = 0;
    double armDistance = 0;
    switch (NodeLevel)
    {
    case NodeLevel::HybridLevel:
      distance = GetCameraDistance(kHybridHeight, AngleTargetOffset);
      armDistance = 0;
      break;
    
    case NodeLevel::MiddleNodeLevel:
      distance = GetCameraDistance(kMiddleNodeHeight, AngleTargetOffset);
      armDistance = GetDistance(kMiddleNodeHeight, distance);
      break;
    
    case NodeLevel::UpperNodeLevel:
      distance = GetCameraDistance(kUpperNodeHeight, AngleTargetOffset);
      armDistance =  11.125;
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
      distance = 0;
      armAngle = -60;
      break;
      
    case NodeLevel::MiddleNodeLevel:
      distance = GetCameraDistance(kMiddleNodeHeight, AngleTargetOffset);
      armAngle = -16;
      break;
    
    case NodeLevel::UpperNodeLevel:
      distance = GetCameraDistance(kUpperNodeHeight, AngleTargetOffset);
      armAngle = 86;
      break;
    }
    return armAngle;
  }
  
}
SetArmPostitionForDistance::SetArmPostitionForDistance(Arm& arm, Turret& turret, const NodeLevel& Level)
: mArm(arm)
, mTurret(turret)
, mLevel(Level)
, mArmPosition{0.2, 0, 0}
 {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(&mArm);
}

// Called when the command is initially scheduled.
void SetArmPostitionForDistance::Initialize() 
{
  mArmPosition.SetTolerance(0);
  //mArmPosition.EnableContinuousInput(-76, -4);
}

// Called repeatedly when this Command is scheduled to run
void SetArmPostitionForDistance::Execute() {
  //double AngleTargetOffset = mTurret.GetVisionPitch();
  double ArmAngleSetPoint = GetNodeAngle(mLevel, 0);
  double outputArmAngle = 0;
  double CurrentArmAngle = mArm.CANCoderArmStatus();

    outputArmAngle = mArmPosition.Calculate(CurrentArmAngle, ArmAngleSetPoint + 3); //+ feedforward;
  mArm.SetArmSpeed(outputArmAngle * -1.0);
  // NEEDS TO BE FINISHED HAVING MOTORS SET TO DESIRED ANGLE
}

// Called once the command ends or is interrupted.
void SetArmPostitionForDistance::End(bool interrupted) {}

// Returns true when the command should end.
bool SetArmPostitionForDistance::IsFinished() {
  return mArmPosition.AtSetpoint();
}
