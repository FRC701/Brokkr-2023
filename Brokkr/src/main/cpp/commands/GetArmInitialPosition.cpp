// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "frc/smartdashboard/SmartDashboard.h"

#include "commands/GetArmInitialPosition.h"

GetArmInitialPosition::GetArmInitialPosition(Arm& arm)
:mArm(arm)
, mArmControl{0, 0, 0} 
{
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void GetArmInitialPosition::Initialize() 
{
  mArmControl.SetTolerance(1);
  mArmControl.EnableContinuousInput(0, 20.5);
}

// Called repeatedly when this Command is scheduled to run
void GetArmInitialPosition::Execute() 
{
  double ExtensionLength = frc::SmartDashboard::GetNumber("ExtensionLength", 0);
  double output = mArmControl.Calculate(mArm.GetExtendTicks(), mArm.DistanceToTicks(ExtensionLength));
  mArm.ArmExtend(output);
}

// Called once the command ends or is interrupted.
void GetArmInitialPosition::End(bool interrupted) 
{}

// Returns true when the command should end.
bool GetArmInitialPosition::IsFinished() 
{
  return mArmControl.AtSetpoint();
}
