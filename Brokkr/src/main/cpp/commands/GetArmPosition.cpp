// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/smartdashboard/SmartDashboard.h>

#include "commands/GetArmPosition.h"
namespace
{
  const double kArm_P = 0.2;
  const double kArm_I = 0.0;
  const double kArm_D = 0.0;
  const double kArm_S = 0.0;
  const double kArm_G = 0.7;
  const double kArm_V = 2.28;
  const double kArm_A = 0.08;
}

using Angle = units::radians;

using Acceleration = units::compound_unit<units::radians_per_second,
                                          units::inverse<units::second>>;
using kv_unit =
    units::compound_unit<units::volts,
                         units::inverse<units::radians_per_second>>;
using ka_unit =
    units::compound_unit<units::volts, units::inverse<Acceleration>>;

GetArmPosition::GetArmPosition(Arm &arm)
    : mArm(arm), mArmControl{kArm_P, kArm_I, kArm_D}, mFeedForward{units::volt_t(kArm_S), units::volt_t(kArm_G), units::unit_t<kv_unit>(kArm_V), units::unit_t<ka_unit>(kArm_A)} // Once 0.9 kP i belive too high
{
  AddRequirements(&mArm);
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void GetArmPosition::Initialize()
{
  mArmControl.SetTolerance(0);
  mArmControl.EnableContinuousInput(-76, -4);
}

// Called repeatedly when this Command is scheduled to run
void GetArmPosition::Execute()
{
  double ArmAngleAdjusted = 0;
  double outputArmAngle = 0;
  double CurrentArmAngle = mArm.CANCoderArmStatus();
  double ArmAngleSetPoint = GetArmAngle();
      [[maybe_unused]]
  int kMinStartAngle = -60;
      [[maybe_unused]]
  int kMaxStartAngle = -35;
      [[maybe_unused]] 
  double feedforward = mFeedForward.Calculate(units::unit_t<Angle>(ArmAngleSetPoint * 0.0174533), 2_rad_per_s).value();
      [[maybe_unused]] 
  double feedforwardAdjusted = mFeedForward.Calculate(units::unit_t<Angle>(ArmAngleAdjusted * 0.0174533), 2_rad_per_s).value();
  // if (CurrentArmAngle <= kMinStartAngle) // WORKAROUND to hitting turret when at small angles:if current angle is less than ten and setpoint is >41 move to 10 first
  //{
  if (abs(ArmAngleSetPoint - CurrentArmAngle) >= 35)
  { /*
     double DeltaArmAngle = (kMinStartAngle + CurrentArmAngle);
     ArmAngleAdjusted = -DeltaArmAngle + CurrentArmAngle;
     outputArmAngle = mArmControl.Calculate(CurrentArmAngle, ArmAngleAdjusted); */
    //+ feedforwardAdjusted;
    outputArmAngle = -mArmControl.Calculate(CurrentArmAngle, ArmAngleSetPoint + 3);
  }
  else
  {
    outputArmAngle = mArmControl.Calculate(CurrentArmAngle, ArmAngleSetPoint + 3); //+ feedforward;
  }
  mArm.SetArmSpeed(outputArmAngle * -1.0);
}
/*else
 {
   outputArmAngle = mArmControl.Calculate(CurrentArmAngle, ArmAngleSetPoint + 3);//+ feedforward;
 } */
// output = std::clamp(outputArmAngle, 2., 80.);//alternative to enableContinuousOutput
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