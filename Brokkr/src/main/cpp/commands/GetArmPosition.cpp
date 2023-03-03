// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/smartdashboard/SmartDashboard.h>

#include "commands/GetArmPosition.h"
namespace
{
  const double kArm_P = 0.15;
  const double kArm_I = 0.0;
  const double kArm_D = 0.0;
}
GetArmPosition::GetArmPosition(Arm &arm)
    : mArm(arm), mArmControl{kArm_P, kArm_I, kArm_D} // Once 0.9 kP i belive too high
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
  double ArmAngleAdjusted = 0;
  double outputArmAngle = 0;
  double CurrentArmAngle = mArm.CANCoderArmStatus();
  double ArmAngleSetPoint = GetArmAngle();
  int kMinStartAngle = 10;
  int kMaxStartAngle = 41;
  if (CurrentArmAngle <= kMinStartAngle) // WORKAROUND to hitting turrent wehn at small angles:if current angle is less than ten and setpoint is >41 move to 10 first
  {
    if (ArmAngleSetPoint >= kMaxStartAngle)
    {
      double DeltaArmAngle = (kMinStartAngle - CurrentArmAngle);
      ArmAngleAdjusted = DeltaArmAngle + CurrentArmAngle;
      outputArmAngle = mArmControl.Calculate(CurrentArmAngle, ArmAngleAdjusted);
    }
    else
    {
      outputArmAngle = mArmControl.Calculate(CurrentArmAngle, ArmAngleSetPoint);
    }
  }
  else
  {
    outputArmAngle = mArmControl.Calculate(CurrentArmAngle, ArmAngleSetPoint);
  }
  // output = std::clamp(outputArmAngle, 2., 80.);//alternative to enableContinuousOutput

  mArm.SetArmSpeed(outputArmAngle * -1.0);
}

double GetArmPosition::GetArmAngle()
{
  return frc::SmartDashboard::GetNumber("ArmAngle", 0);
}

// Called once the command ends or is interrupted.
void GetArmPosition::End(bool interrupted) {}

// Returns true when the command should end.
bool GetArmPosition::IsFinished()
{
  return mArmControl.AtSetpoint();
}
