#include <Arduino.h>

//this is the event structure.
struct Event
{
  unsigned long timer;    //this will hold the millis() of the last time the "event" was triggered
  unsigned int frequency; //this is the amount of time in ms between event triggers.
  bool flag = false;      //this will initially have a false value when you make a new event
};

Event eventOne; //new global variables of the Event structure for holding the event information
Event eventTwo;

unsigned long baseClock; //place to hold millis() each time through the loop

void setup()
{
  eventOne.frequency = 500; //this sets the frequency of the events
  eventTwo.frequency = 1000;
}

//check out the "pass by reference" portion of my email for a closer explination of the & here.
//this function takes an "Event" type variable, and asses if enough time has passed since the last trigger and sets the flag if so
//you'll notice this is the same as the code that was duplicated in the last example.
void checkEventTimers(Event &event)
{
  baseClock = millis();
  unsigned int timeDelta = baseClock - event.timer;
  if (timeDelta > event.frequency)
  {
    event.flag = true;
    event.timer = millis();
  }
}

//this function just monitors timings, and sets the flags for events when they should happen
void manageFlags()
{
  checkEventTimers(eventOne); //instead of having all that duplicate code, we just pass the events to the function we made.
  checkEventTimers(eventTwo);
}
//this function executes functions based upon if the flags are set or not.
void manageEvents()
{
  if (eventOne.flag)
  {
    doEventOne();
  }
  if (eventTwo.flag)
  {
    doEventTwo();
  }
}

void doEventOne()
{
  //event code here
  eventOne.flag = false; //make sure to clear the flag after you execute the event function
}
void doEventTwo()
{
  //event code here
  eventTwo.flag = false; //make sure to clear the flag after you execute the event function
}

void loop()
{
  manageFlags();  //handles timing every time through the loop
  manageEvents(); //looks for enabled flags, and executes events based on that
}