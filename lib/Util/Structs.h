#ifndef STRUCTS_H_
#define STRUCTS_H_

struct OSStatus
{
    bool running = false;
    bool eStop = false;
    bool lowPressure = false;
    int keyStatus;

    int keyOffPin;
    int keyOnPin;
    int startButtonPin;
    int eStopPin;
    int pressurePin;
};

#endif