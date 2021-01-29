#ifndef PNUMACONTROL_H
#define PNUMACONTROL_H

class PnumaControl
{
private:
  /* data */
public:
  PnumaControl(int pushIn, int pullIn);

  ~PnumaControl();

  bool push = false;   //boolean for push enable
  bool pull = false;   //boolean for pull enable
  int pushPin;         //arduino pin for push solenoid
  int pullPin;         //arduino pin for pull solenoid
  int cyclesPerSecond; //rate of actuation
};

#endif