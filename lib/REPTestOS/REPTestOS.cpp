#include "REPTestOS.h"
#include "Util.h"
#include "structs/structs.h"

//global variable definitions
Util util;
testParams currentTest;

REPTestOS::REPTestOS(){};  //constructor
REPTestOS::~REPTestOS(){}; //destructor

void REPTestOS::bootOS() //boot operating system function. To run in startup
{
  Wire.begin();              //Start wire
  setupMenu();               //Initialize menu system
  Serial.begin(9600);        // initialize serial communication at 9600 bits per second:
  Serial.println("Booting"); //small serial indicator during boot phase
  pnuma1.setup();            //setup function for pins for pnuma 1
  //Start remaining items
  pinMode(13, INPUT_PULLUP);                      //set pullup logic for e-stop loop.
  menuTimeRem.setTime(currentTest.timeRemaining); //initialize timeRemaining as 00:00:00
  menuTimeRem.setChanged(true);
}

void REPTestOS::runOS() //constantly runs in loop
{
  taskManager.runLoop(); //handler for menu system task management
  pnuma1.control(currentTest);
}

/*----------------------------------------------------------
------------------------------------------------------------
----------------- Menu System Handlers ---------------------
------------------------------------------------------------
----------------------------------------------------------*/

void CALLBACK_FUNCTION cycleFrequency(int id)
{
  int val = pnuma1.setCyclesPerSecond(int(menuTestSettingsCyclesPerSecond.getAsFloatingPointValue())); //update pnuma1 with value
  Serial.println(val);
}

void CALLBACK_FUNCTION pullControl(int id)
{
  ActuatorMode mode = pnuma1.setMode(menuTestSettingsPush.getBoolean(), menuTestSettingsPull.getBoolean()); //update pnuma1 with mode
  Serial.println(mode);
}

void CALLBACK_FUNCTION pushControl(int id)
{
  ActuatorMode mode = pnuma1.setMode(menuTestSettingsPush.getBoolean(), menuTestSettingsPull.getBoolean()); //update pnuma1 with mode
  Serial.println(mode);
}

void CALLBACK_FUNCTION stopTest(int id)
{
  bool running = pnuma1.setRunning(false);
  Serial.println(running);
}

void CALLBACK_FUNCTION startTest(int id)
{
  bool running = pnuma1.setRunning(true);
  Serial.println(running);
}

void CALLBACK_FUNCTION resetTest(int id)
{
  pnuma1.setRunning(false);                   //stop test cycling
  menuTimeRem.setTime(currentTest.totalTime); //reset countdown
  menuTimeRem.setChanged(true);
  currentTest.timeRemaining = currentTest.totalTime;
  currentTest.cyclesRemaining = currentTest.totalCycles;
  pnuma1.setState(off);
  pnuma1.actuate();
}

void CALLBACK_FUNCTION maxRunTime(int id)
{
  // currentTest.totalTime = currentTest.timeRemaining = menuTestSettingsMaxTime.getTime();
  // menuTimeRem.setTime(currentTest.timeRemaining);
}

void CALLBACK_FUNCTION maxCycles(int id)
{
  LargeFixedNumber *maxCyclesVal = menuTestSettingsMaxCycles.getLargeNumber(); //sets the max number of cycles in test structure
  currentTest.totalCycles = currentTest.cyclesRemaining = maxCyclesVal->getAsFloat();
  currentTest.setBySeconds(currentTest.totalCycles / pnuma1.getCyclesPerSecond());
  menuTimeRem.setTime(currentTest.timeRemaining);
}

void CALLBACK_FUNCTION saveTestSettings(int id)
{
  pnuma1.setNextCycle();
  pnuma1.actuate();
}

void CALLBACK_FUNCTION extend(int id)
{
  pnuma1.setState(out);
  pnuma1.actuate();
}

void CALLBACK_FUNCTION retract(int id)
{
  pnuma1.setState(in);
  pnuma1.actuate();
}

void CALLBACK_FUNCTION onHold(int id)
{
  pnuma1.setState(on);
  pnuma1.actuate();
}

void CALLBACK_FUNCTION allOff(int id)
{
  pnuma1.setState(off);
  pnuma1.actuate();
}

/*----------------------------------------------------------
------------------------------------------------------------
---------------------- Functions ---------------------------
------------------------------------------------------------
----------------------------------------------------------*/

//use itoa(int, array, 10) to convert int to const char*
//from bool to const char* menuTotalCycles.setTextValue(util.returnCharPFromBool(menuTestSettingsPull.getBoolean()));
