#include "REPTestOS.h"

REPTestOS::REPTestOS(/* args */) //constructor
{
}

REPTestOS::~REPTestOS() //destructor
{
}

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
  // TODO - your menu change code
}

void CALLBACK_FUNCTION pullControl(int id)
{
  // TODO - your menu change code
}

void CALLBACK_FUNCTION pushControl(int id)
{
  // TODO - your menu change code
}

void CALLBACK_FUNCTION runTest(int id)
{
  // TODO - your menu change code
}