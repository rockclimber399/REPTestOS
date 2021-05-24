#ifndef CONFIG_H_
#define CONFIG_H_

//uncomment desired board, and verify pin configurations for board.
//make sure to update platformio.ini file with correct settings for new board

// #define ESP8266
// #define ESP32
// #define UNO
#define ATMega2560

//config for ESP8266
#ifdef ESP8266
#define _keyOffPin 47      //set keyOffPin
#define _keyOnPin 46       //set keyOnPin
#define _startButtonPin 48 //set startuButtonPin
#define _eStopPin 49       //set eStopPin
#define _eStopPin2 50      //set eStopPin
#define _pressurePin 12    //set pressurePin
#define _pnuma1PushPin 44  //set pushPin for pnuma1
#define _pnuma1PullPin 45  //set pullPin for pnuma1
#endif

//config for ESP32
#ifdef ESP32
#define _keyOffPin 47      //set keyOffPin
#define _keyOnPin 46       //set keyOnPin
#define _startButtonPin 48 //set startuButtonPin
#define _eStopPin 49       //set eStopPin
#define _eStopPin2 50      //set eStopPin
#define _pressurePin 12    //set pressurePin
#define _pnuma1PushPin 44  //set pushPin for pnuma1
#define _pnuma1PullPin 45  //set pullPin for pnuma1
#endif

//config for Arduino UNO
#ifdef UNO
#define _keyOffPin 47      //set keyOffPin
#define _keyOnPin 46       //set keyOnPin
#define _startButtonPin 48 //set startuButtonPin
#define _eStopPin 49       //set eStopPin
#define _eStopPin2 50      //set eStopPin
#define _pressurePin 12    //set pressurePin
#define _pnuma1PushPin 44  //set pushPin for pnuma1
#define _pnuma1PullPin 45  //set pullPin for pnuma1
#endif

//config for Arduino Mega
#ifdef ATMega2560
#define _keyOffPin 47      //set keyOffPin
#define _keyOnPin 46       //set keyOnPin
#define _startButtonPin 48 //set startuButtonPin
#define _eStopPin 49       //set eStopPin
#define _eStopPin2 50      //set eStopPin2
#define _pressurePin 12    //set pressurePin
#define _pnuma1PushPin 44  //set pushPin for pnuma1
#define _pnuma1PullPin 45  //set pullPin for pnuma1
#endif

#endif