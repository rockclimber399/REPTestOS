#include "PnumaControl.h"
PnumaControl pnuma1(9, 10);

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
    digitalWrite(pushPin, HIGH);
    digitalWrite(pullPin, HIGH);
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
            this->setNextCycle();     //update state based off of mode
            this->actuate();          //fire updated actuation state
            lastActuation = millis(); //reset timer
        }
    }
    else
    {
        status = off;
        this->actuate();
    }
};
String PnumaControl::setMode(bool pushEnable, bool pullEnable)
{
    if (pushEnable && pullEnable)
    {
        mode = pushAndPull;
        return "pushAndPull";
    }
    else if (!pushEnable && !pullEnable)
    {
        mode = none;
        return "none";
    }
    else if (!pushEnable && pullEnable)
    {
        mode = pullOnly;
        return "pullOnly";
    }
    else if (pushEnable && !pullEnable)
    {
        mode = pushOnly;
        return "pushOnly";
    }
    else
    {
        mode = none;
        return "none";
    }
}

bool PnumaControl::setRunning(bool run)
{
    running = run;
    return running;
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
        digitalWrite(pushPin, HIGH);
        digitalWrite(pullPin, HIGH);
        break;
    case on:
        digitalWrite(pushPin, LOW);
        digitalWrite(pullPin, LOW);
        break;
    case in:
        digitalWrite(pushPin, HIGH);
        digitalWrite(pullPin, LOW);
        break;
    case out:
        digitalWrite(pushPin, LOW);
        digitalWrite(pullPin, HIGH);
        break;
    default:
        break;
    }
}