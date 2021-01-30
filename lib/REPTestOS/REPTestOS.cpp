#include "REPTestOS.h"
#include "Util.h"

//global variable definitions
Util util;
PnumaControl pnuma1(9, 10);

REPTestOS::REPTestOS(){};  //constructor
REPTestOS::~REPTestOS(){}; //destructor

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

uint8_t taskId = taskManager.scheduleOnce(3000, doThing);

void doThing()
{
  menuTotalCycles.setTextValue(util.returnCharPFromBool(menuTestSettingsPull.getBoolean()));
};

/*----------------------------------------------------------
------------------------------------------------------------
----------------- Menu System Handlers ---------------------
------------------------------------------------------------
----------------------------------------------------------*/

void CALLBACK_FUNCTION cycleFrequency(int id)
{
  pnuma1.cyclesPerSecond = int(menuTestSettingsCyclesPerSecond.getAsFloatingPointValue()); //update pnuma1 with value
}

void CALLBACK_FUNCTION pullControl(int id)
{
  pnuma1.setMode(menuTestSettingsPush.getBoolean(), menuTestSettingsPull.getBoolean()); //update pnuma1 with mode
}

void CALLBACK_FUNCTION pushControl(int id)
{
  pnuma1.setMode(menuTestSettingsPush.getBoolean(), menuTestSettingsPull.getBoolean()); //update pnuma1 with mode
}

void CALLBACK_FUNCTION stopTest(int id)
{
  pnuma1.running = false;
}

void CALLBACK_FUNCTION startTest(int id)
{
  pnuma1.running = true;
}

void CALLBACK_FUNCTION maxRunTime(int id)
{
  // TODO - your menu change code
}

void CALLBACK_FUNCTION maxCycles(int id)
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
//from bool to const char* menuTotalCycles.setTextValue(util.returnCharPFromBool(menuTestSettingsPull.getBoolean()));
