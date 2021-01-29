#ifndef PNUMACONTROL_H
#define PNUMACONTROL_H

#include "Arduino.h"

enum ActuatorState
{
  off,
  on,
  in,
  out
}; //enum decleration of actuator state

enum ActuatorMode
{
  pushOnly,
  pullOnly,
  pushAndPull,
  none
}; //enum decleration of actuator mode

class PnumaControl
{
private:
  // bool push = false; //boolean for push enable
  // bool pull = false; //boolean for pull enable
public:
  PnumaControl(int pushIn, int pullIn);

  ~PnumaControl();

  int pushPin;                     //arduino pin for push solenoid
  int pullPin;                     //arduino pin for pull solenoid
  int cyclesPerSecond;             //rate of actuation
  bool running = false;            //trigger for actuation
  unsigned long baseClock;         //timer
  unsigned long lastActuation = 0; //time of last actuation
  ActuatorState status = off;      //used for tracking actuator state
  ActuatorMode mode = none;        //used for tracking actuation mode

  void setup();                                   //function to set pins of object on boot.
  void control();                                 //primary control handler, must run in loop
  void setMode(bool pushEnable, bool pullEnable); //sets ActuatorMode based off of settings
  void setNextCycle();                            //sets the state of the actuator's next movement based on push/pull enables and current state
  void actuate();                                 //handles actuator state logic to fire actuator as needed
};

#endif