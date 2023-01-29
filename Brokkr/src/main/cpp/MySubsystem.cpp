#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

class MySubsystem {
 public:
  MySubsystem(int talonFXId) : talonFX_(talonFXId) {}

  void SetSpeed(double speed) {
    talonFX_.Set(ControlMode::PercentOutput, speed);
  }

 private:
  MySubsystem talonFX_;
};
