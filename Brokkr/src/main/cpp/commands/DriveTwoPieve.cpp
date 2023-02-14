// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/DriveTwoPieve.h"
#include <pathplanner/lib/PathPlanner.h>
#include <frc2/command/RamseteCommand.h>
#include <frc/trajectory/TrajectoryUtil.h>


using namespace pathplanner;

DriveTwoPieve::DriveTwoPieve(Chassis& chassis) 
: mChassis(chassis)
{
/* PathPlannerTrajectory path = PathPlanner::loadPath("Two Pieve", PathConstraints(18.42_mps, 6_mps_sq));

// Sample the state of the path at 1.2 seconds
PathPlannerTrajectory::PathPlannerState exampleState = path.sample(1.2_s);

constexpr auto kRamseteB = 2.0 * 1_rad * 1_rad / (1_m * 1_m);
constexpr auto kRamseteZeta = 0.7 / 1_rad;

constexpr auto ks = 0.22_V;
constexpr auto kv = 1.98 * 1_V * 1_s / 1_m;
constexpr auto ka = 0.2 * 1_V * 1_s * 1_s / 1_m;

double kPDriveVelocity = 8.5;

 frc2::Command* ramseteCommand{frc2::RamseteCommand(
      path, [this] { return mChassis.GetPose(); },
      frc::RamseteController{kRamseteB, kRamseteZeta},
      frc::SimpleMotorFeedforward<units::meters>{
          ks, kv, ka},
      frc::DifferentialDriveKinematics{units::meter_t{24}},
      [this] { return mChassis.GetWheelSpeeds(); },
      frc2::PIDController{kPDriveVelocity, 0, 0},
      frc2::PIDController{kPDriveVelocity, 0, 0},
      [this](auto left, auto right) { mChassis.TankDriveVoltage(left, right); },
      {&mChassis})}; */}