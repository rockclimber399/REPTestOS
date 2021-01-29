#include "REPTestOS.h"

//global variable definitions
PnumaControl pnuma1(9, 10);

REPTestOS::REPTestOS(/* args */){}; //constructor
REPTestOS::~REPTestOS(){};          //destructor

void REPTestOS::bootOS() //boot operating system function. To run in startup
{
  Wire.begin();              //Start wire
  setupMenu();               //Initialize menu system
  Serial.begin(9600);        // initialize serial communication at 9600 bits per second:
  Serial.println("Booting"); //small serial indicator during boot phase

  //Start remaining items
}

void REPTestOS::runOS() //constantly runs in loop
{
  taskManager.runLoop(); //handler for menu system task management
}

/*----------------------------------------------------------
------------------------------------------------------------
----------------- Menu System Handlers ---------------------
------------------------------------------------------------
----------------------------------------------------------*/

void CALLBACK_FUNCTION cycleFrequency(int id)
{
  pnuma1.cyclesPerSecond = int(menuTestSettingsCyclesPerSecond.getAsFloatingPointValue());
}

void CALLBACK_FUNCTION pullControl(int id)
{
  pnuma1.pull = menuTestSettingsPull.getBoolean();
}

void CALLBACK_FUNCTION pushControl(int id)
{
  pnuma1.pull = menuTestSettingsPull.getBoolean();
}

void CALLBACK_FUNCTION stopTest(int id)
{
  // TODO - your menu change code
}

void CALLBACK_FUNCTION startTest(int id)
{
  menuTotalCycles.setTextValue(menuTestSettingsPull.getBoolean());
}

void CALLBACK_FUNCTION maxRunTime(int id)
{
  // TODO - your menu change code
}

void CALLBACK_FUNCTION maxCycles(int id)
{
  // TODO - your menu change code
}

void CALLBACK_FUNCTION totalCycles(int id)
{
  //
}

void CALLBACK_FUNCTION runTimer(int id)
{
  // TODO - your menu change code
}

void CALLBACK_FUNCTION saveTestSettings(int id)
{
  // TODO - your menu change code
}

/*----------------------------------------------------------
------------------------------------------------------------
---------------------- Functions ---------------------------
------------------------------------------------------------
----------------------------------------------------------*/

//use itoa(int, array, 10) to convert int to const char*

String returnString(bool input)
{
  if (input)
  {
    return "True";
  }
  return "False";
}