// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "FunctioningMode.h"

#include "ListeningToYourCommands.h"
#include "SwarmIsSwarmy.h"
    
void FunctioningMode::execute()
{
    // !!!!!
    // make it so the data is not empty and comes from the RF communication
    IncommingCommunicationFormat input;
    // !!!!!

    // call the function that corresponds to the current functioning mode
    switch(FunctioningMode::_functioningMode)
    {
        case LISTENING_TO_YOUR_COMMANDS_FUNCTIONING_MODE:
            ListeningToYourCommands::execute(input);
            break;
        case SWARM_IS_SWARMY_FUNCTIONING_MODE:
            SwarmIsSwarmy::execute(input);
            break;
        default:
            // how the hell did we get here??
            // some debug info...
            Serial.println("the selected mode is undefined!");
            delay(1000);
            break;
    }
}

void FunctioningMode::set(unsigned char functionningMode)
{
    _functioningMode = functionningMode;
}

unsigned char FunctioningMode::get()
{
    return _functioningMode;
}

unsigned char FunctioningMode::_functioningMode = LISTENING_TO_YOUR_COMMANDS_FUNCTIONING_MODE;
