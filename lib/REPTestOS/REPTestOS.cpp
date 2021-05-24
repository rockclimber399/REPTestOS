#include "REPTestOS.h"

//global variable definitions
Util util;
OSStatus osStatus;
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
  setupControls();           //setup function for this OS to configure pins
  //Start remaining items
  menuTimeRem.setTime(currentTest.timeRemaining); //initialize timeRemaining as 00:00:00
  menuTimeRem.setChanged(true);
  currentTest.minPressure = 0;
}

void REPTestOS::runOS() //constantly runs in loop
{
  taskManager.runLoop(); //handler for menu system task management
  pnuma1.control(currentTest, systemCheck());
  if (digitalRead(_startButtonPin))
    osStatus.setRunning(true);
}

bool REPTestOS::systemCheck()
{
  //this function should return true if all safety measures are good. Otherwise false, so machine does not run.
  //check key, eStop, pressure, and "Running Toggle"
  if (getKeyState() == 2)
  {
    if (!osStatus.eStop())
    {
      if (osStatus.currentPressure() >= currentTest.minPressure)
      {
        if (osStatus.running)
        {
          return true;
        }
        //Serial.println("Running set false");
      }
      //Serial.println("Pressure reading to Low");
    }
    //Serial.println("E-STOP");
  }
  //Serial.println("key State not on");
  osStatus.running = false;
  return false;
}

int REPTestOS::getKeyState()
{
  bool offPin = digitalRead(osStatus.keyOffPin);
  bool onPin = digitalRead(osStatus.keyOnPin);

  if (!offPin && !onPin)
  {
    return 1; //if neither pin is grounded, switch is neutral
  }
  else if (offPin && !onPin)
  {
    return 0; //if off pin is grounded, switch is OFF
  }
  else if (!offPin && onPin)
  {
    return 2; //if on pin is grounded, switch is on
  }
  else
  {
    return 0; //default to return 0 (off) for safety
  }

}; //function to check current key state.

void REPTestOS::setupControls()
{
  osStatus.keyOffPin = _keyOffPin;           //set keyOffPin
  osStatus.keyOnPin = _keyOnPin;             //set keyOnPin
  osStatus.startButtonPin = _startButtonPin; //set startuButtonPin
  osStatus.eStopPin = _eStopPin;             //set eStopPin
  osStatus.eStopPin2 = _eStopPin2;           //set eStopPin
  osStatus.pressurePin = _pressurePin;       //set pressurePin

  pinMode(osStatus.keyOffPin, INPUT_PULLUP);
  pinMode(osStatus.keyOnPin, INPUT_PULLUP);
  pinMode(osStatus.startButtonPin, INPUT_PULLUP);
  pinMode(osStatus.eStopPin, INPUT_PULLUP);
  pinMode(osStatus.eStopPin2, INPUT_PULLUP);
  pinMode(osStatus.pressurePin, INPUT); //analog input

  digitalWrite(osStatus.keyOffPin, HIGH);
  digitalWrite(osStatus.keyOnPin, HIGH);
  digitalWrite(osStatus.startButtonPin, HIGH);
  digitalWrite(osStatus.eStopPin, HIGH);
  digitalWrite(osStatus.eStopPin2, HIGH);
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

void CALLBACK_FUNCTION resetTest(int id)
{
  osStatus.setRunning(false);                 //stop test cycling
  menuTimeRem.setTime(currentTest.totalTime); //reset countdown
  menuTimeRem.setChanged(true);
  currentTest.timeRemaining = currentTest.totalTime;
  currentTest.cyclesRemaining = currentTest.totalCycles;
  menuTimeRem.setTime(currentTest.timeRemaining);
  pnuma1.setState(off);
  pnuma1.actuate();
}

void CALLBACK_FUNCTION maxCycles(int id)
{
  LargeFixedNumber *maxCyclesVal = menuTestSettingsMaxCycles.getLargeNumber(); //sets the max number of cycles in test structure
  currentTest.totalCycles = currentTest.cyclesRemaining = maxCyclesVal->getAsFloat();
  currentTest.setBySeconds(currentTest.totalCycles / pnuma1.getCyclesPerSecond());
  // Serial.println(currentTest.cyclesRemaining);
  menuTimeRem.setTime(currentTest.timeRemaining);
  currentTest.totalTime = currentTest.timeRemaining;
}

void CALLBACK_FUNCTION resetTotalCycles(int id)
{
  currentTest.cyclesExecuted = 0;
  menuTotalCycles.setTextValue(itoa(currentTest.cyclesExecuted, 'xxxx', 10));
  menuTotalCycles.setChanged(true);
}

/*----------------------------------------------------------
------------------------------------------------------------
---------------------- Functions ---------------------------
------------------------------------------------------------
----------------------------------------------------------*/

//use itoa(int, array, 10) to convert int to const char*
//from bool to const char* menuTotalCycles.setTextValue(util.returnCharPFromBool(menuTestSettingsPull.getBoolean()));
