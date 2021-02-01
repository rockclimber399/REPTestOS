#include "REPTestOS.h"
#include "Util.h"

//global variable definitions
Util util;

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
}

void REPTestOS::runOS() //constantly runs in loop
{
  taskManager.runLoop(); //handler for menu system task management
  pnuma1.control();
}

/*----------------------------------------------------------
------------------------------------------------------------
----------------- Menu System Handlers ---------------------
------------------------------------------------------------
----------------------------------------------------------*/

void CALLBACK_FUNCTION cycleFrequency(int id)
{
  pnuma1.cyclesPerSecond = int(menuTestSettingsCyclesPerSecond.getAsFloatingPointValue()); //update pnuma1 with value
  Serial.println(pnuma1.cyclesPerSecond);
}

void CALLBACK_FUNCTION pullControl(int id)
{
  String mode = pnuma1.setMode(menuTestSettingsPush.getBoolean(), menuTestSettingsPull.getBoolean()); //update pnuma1 with mode
  Serial.println(mode);
}

void CALLBACK_FUNCTION pushControl(int id)
{
  String mode = pnuma1.setMode(menuTestSettingsPush.getBoolean(), menuTestSettingsPull.getBoolean()); //update pnuma1 with mode
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
  pnuma1.setNextCycle();
  pnuma1.actuate();
}

/*----------------------------------------------------------
------------------------------------------------------------
---------------------- Functions ---------------------------
------------------------------------------------------------
----------------------------------------------------------*/

//use itoa(int, array, 10) to convert int to const char*
//from bool to const char* menuTotalCycles.setTextValue(util.returnCharPFromBool(menuTestSettingsPull.getBoolean()));
