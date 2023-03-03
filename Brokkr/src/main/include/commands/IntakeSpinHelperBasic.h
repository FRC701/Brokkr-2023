#include "commands/IntakeSpinHelper.h"

class IntakeSpinHelperBasic : public IntakeSpinHelper
{
public:
  IntakeSpinHelperBasic(Claw& claw, double speed);

protected:
  virtual double GetCurrentLimit();

  virtual double GetMotorSpeed();

  double mSpeed;
};