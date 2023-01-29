#include <gtest/gtest.h>
#include <frc/WPILib.h>
#include "MySubsystem.h"

class MySubsystemTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    // Create mock objects for any hardware components used by the subsystem
    mock_motor_ = std::make_unique<frc::MockSpeedController>(1);
    my_subsystem_ = new MySubsystem(mock_motor_.get());
  }

  virtual void TearDown() {
    delete my_subsystem_;
  }

  std::unique_ptr<frc::MockSpeedController> mock_motor_;
  MySubsystem* my_subsystem_;
};

TEST_F(MySubsystemTest, TestInitialState) {
  // Test that the subsystem is in the expected initial state
  EXPECT_EQ(my_subsystem_->GetStatus(), MySubsystem::kIdle);
  EXPECT_EQ(mock_motor_->Get(), 0);
}

TEST_F(MySubsystemTest, TestSetSpeed) {
  // Test setting the speed of the motor
  my_subsystem_->SetSpeed(0.5);
  EXPECT_EQ(mock_motor_->Get(), 0.5);
}
