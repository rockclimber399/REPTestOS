#include <Arduino.h>
#include <REPTestOS.h>

REPTestOS OS; //create now Operating System object

void setup()
{
  OS.bootOS();
}

void loop()
{
  OS.runOS();
}
