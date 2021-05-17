// Author: John-William Lebel, 2021-04-18, creation

// ************************************************* //
// **************** CONFIG HANDLING **************** //
// ************************************************* //
//
//
// user configuration
#include "userConfig.h"

// *********************************************** //
// **************** SERIAL CONFIG **************** //
// *********************************************** //

#ifdef ENABLE_SERIAL_DEBUGGING
#define DEBUG_INIT(speed) (Serial.begin(speed))
#define DEBUG_FUNCTION(string) (Serial.println((string)))
#else
#define DEBUG_INIT
#define DEBUG_FUNCTION(string) (nullptr)
#endif

#define serialInit() (DEBUG_INIT(SERIAL_COMMUNICATION_SPEED))
#define serialDebug(string) (DEBUG_FUNCTION(string))



