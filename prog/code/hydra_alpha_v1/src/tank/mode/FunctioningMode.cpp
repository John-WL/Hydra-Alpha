// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "FunctioningMode.h"

#include "RfLessControlTest.h"
#include "ListeningToYourCommands.h"
#include "SwarmIsSwarmy.h"

#include "../peripheral/protocol_format/DataConverter.h"
#include "../peripheral/spi/HydraRF/HydraRF.h"
    
void FunctioningMode::execute()
{
    // ComRemote is defined in "HydraRF.h"
    IncommingCommunicationFormat input = DataConverter::translate(&ComRemote);

    // call the function that corresponds to the current functioning mode
    switch(_functioningMode)
    {
        case LISTENING_TO_YOUR_COMMANDS_FUNCTIONING_MODE:
            ListeningToYourCommands::execute(input);
            break;
        case SWARM_IS_SWARMY_FUNCTIONING_MODE:
            SwarmIsSwarmy::execute(input);
            break;
        case RF_LESS_CONTROL_TEST:
            RfLessControlTest::execute();
            break;
        default:
            // how the hell did we get here??
            // some debug info...
            Serial.println("The selected mode is undefined!");
            Serial.print("The selected mode was #");
            Serial.print(_functioningMode);
            Serial.println(", but only mode #0 or #1 are valid!");
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
