// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "ArmPositionForDistanceCommandTest.h"

/*
    Unit testing uses the AAA pattern for constructing tests:
    1. Arrange. Setup the test. What are the initial conditions for the test?
    2. Action. Do something to change the conditions. 
    3. Assert. Did the change occur the way you expected the change to happen.

    Each of these steps can be simple or complex. Simple is better. Using functions 
    for arranging is common as many tests will have similar initial conditions.
*/

TEST_F(ArmPositionForDistanceCommandTest, execute_once) {
    // Arrange
    // Initialize the command
    mCommand.Initialize();

    // Action
    // Execute the command once
    mCommand.Execute();

    // Assert
    // The command should not be done
    bool isFinished = mCommand.IsFinished();
    EXPECT_FALSE(isFinished);
}