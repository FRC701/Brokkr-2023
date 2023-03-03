// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/smartdashboard/SmartDashboard.h>

#include "commands/GetArmPosition.h"
//  using namespace std;

constexpr double kP = 0.15;
constexpr double kI = 0;
constexpr double kD = 0;

GetArmPosition::GetArmPosition(Arm& arm) 
: mArm(arm)
, mArmControl{kP, kI, kD} //Once 0.9 kP i belive too high
{
  AddRequirements(&mArm);
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void GetArmPosition::Initialize() 
{
  mArmControl.SetTolerance(1);
  mArmControl.EnableContinuousInput(2, 80);
}

// Called repeatedly when this Command is scheduled to run
void GetArmPosition::Execute() 
{
  double ArmAngle = frc::SmartDashboard::GetNumber("ArmAngle", 0);
  double output = mArmControl.Calculate(mArm.CANCoderArmStatus(), ArmAngle);
  //output = std::clamp(output, 4, 80);
  mArm.SetArmSpeed(output * -1.0);
}

// Called once the command ends or is interrupted.
void GetArmPosition::End(bool interrupted) {}

// Returns true when the command should end.
bool GetArmPosition::IsFinished() {
  return mArmControl.AtSetpoint();
}
