#include "PnumaControl.h"

PnumaControl::PnumaControl(int pushIn, int pullIn)
{
    pushPin = pushIn; //constructor requires push and pull actuator pin #'s, set to private
    pullPin = pullIn;
}

PnumaControl::~PnumaControl()
{
}

void PnumaControl::setup()
{
    pinMode(pushPin, OUTPUT);
    pinMode(pullPin, OUTPUT);
    digitalWrite(pushPin, LOW);
    digitalWrite(pullPin, LOW);
}
void PnumaControl::control()
{
    if (running)
    {
        baseClock = millis();                                //update clock
        unsigned long timeDelta = baseClock - lastActuation; //find time difference between last actuation

        int freq = 1000 / cyclesPerSecond; //compare to desired frequency

        if (timeDelta > freq)
        {
            setNextCycle();           //update state based off of mode
            actuate();                //fire updated actuation state
            lastActuation = millis(); //reset timer
        }
    }
};
void PnumaControl::setMode(bool pushEnable, bool pullEnable)
{
    if (pushEnable && pullEnable)
    {
        mode = pushAndPull;
    }
    else if (!pushEnable && !pullEnable)
    {
        mode = none;
    }
    else if (!pushEnable && pullEnable)
    {
        mode = pullOnly;
    }
    else if (pushEnable && !pullEnable)
    {
        mode = pushOnly;
    }
}
void PnumaControl::setNextCycle()
{
    switch (mode)
    {
    case pushOnly:
        switch (status)
        {
        case off:
            status = out;
        case on:
            status = out;
        case in:
            status = out;
        case out:
            status = off;
            break;
        default:
            break;
        }
    case pullOnly:
        switch (status)
        {
        case off:
            status = in;
        case on:
            status = in;
        case in:
            status = off;
        case out:
            status = in;
            break;
        default:
            break;
        }
    case pushAndPull:
        switch (status)
        {
        case off:
            status = out;
        case on:
            status = out;
        case in:
            status = out;
        case out:
            status = in;
            break;
        default:
            break;
        }
    case none:
        switch (status)
        {
        case off:
            status = off;
        case on:
            status = off;
        case in:
            status = off;
        case out:
            status = off;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}
void PnumaControl::actuate()
{
    switch (status)
    {
    case off:
        digitalWrite(pushPin, LOW);
        digitalWrite(pullPin, LOW);
        break;
    case on:
        digitalWrite(pushPin, HIGH);
        digitalWrite(pullPin, HIGH);
        break;
    case in:
        digitalWrite(pushPin, LOW);
        digitalWrite(pullPin, HIGH);
        break;
    case out:
        digitalWrite(pushPin, HIGH);
        digitalWrite(pullPin, LOW);
        break;
    default:
        break;
    }
}