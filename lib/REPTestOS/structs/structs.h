#ifndef STRUCTS_H
#define STRUCTS_H

#include "REPTestOS_menus_menu.h"

struct testParams
{
  int totalCycles;
  int cyclesRemaining;
  int cyclesExecuted;

  int daysRemaining;

  TimeStorage timeRemaining;
  TimeStorage totalTime;

  void decSecond()
  {
    if (timeRemaining.seconds > 0)
    {
      timeRemaining.seconds--;
    }
    else if (timeRemaining.minutes > 0)
    {
      timeRemaining.minutes--;
      timeRemaining.seconds = 59;
    }
    else if (timeRemaining.hours > 0)
    {
      timeRemaining.hours--;
      timeRemaining.minutes = 59;
      timeRemaining.seconds = 59;
    }
    else if (daysRemaining > 0)
    {
      daysRemaining--;
      timeRemaining.hours = 24;
      timeRemaining.minutes = 59;
      timeRemaining.seconds = 59;
    }
  }

  long getSeconds()
  {
    long seconds;
    seconds += this->timeRemaining.seconds;
    seconds += this->timeRemaining.minutes * 60;
    seconds += this->timeRemaining.hours * 60 * 60;
    seconds += this->daysRemaining * 24 * 60 * 60;
    return seconds;
  }

  void setBySeconds(long seconds)
  {
    long minutes = seconds / 60;
    long hours = minutes / 60;
    long days = hours / 24;
    this->daysRemaining = days;
    this->timeRemaining.hours = int(days % 24);
    this->timeRemaining.minutes = int(hours % 60);
    this->timeRemaining.seconds = int(minutes % 60);
    Serial.println(daysRemaining);
    Serial.println(timeRemaining.hours);
    Serial.println(timeRemaining.minutes);
    Serial.println(timeRemaining.seconds);
  }
};

#endif
