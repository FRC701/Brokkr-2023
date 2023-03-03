#include "commands/IntakeSpinHelperBasic.h"

IntakeSpinHelperBasic::IntakeSpinHelperBasic(Claw& claw, double speed)
: IntakeSpinHelper(claw)
, mSpeed(speed)
{
    
}

double IntakeSpinHelperBasic::GetCurrentLimit()
{
  return Claw::kCurrentLimit;
}

double IntakeSpinHelperBasic::GetMotorSpeed()
{
  return mSpeed;
}
