#include "PnumaControl.h"

PnumaControl::PnumaControl(int pushIn, int pullIn)
{
    pushPin = pushIn; //constructor requires push and pull actuator pin #'s, set to private
    pullPin = pullIn;
}

PnumaControl::~PnumaControl()
{
}
