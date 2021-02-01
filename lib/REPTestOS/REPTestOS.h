#ifndef REPTESTOS_H
#define REPTESTOS_H

#include "REPTestOS_menus_menu.h"
#include "PnumaControl.h"

//The function of this is to marry the whole system. Bringing in the LCD menusystem, as well as pnumatic control,
//and any sensors that may be necessary, and the logic of behavior. Menu Logic will exist within "MenuSystem_menu.h"

class REPTestOS
{
private:
public:
  REPTestOS();  //constructor function
  ~REPTestOS(); //destructor function

  //other public functions/variables
  void bootOS(); //boot the operating system and all dependants
  void runOS();  //runOS() needs to be in main Loop
};

#endif