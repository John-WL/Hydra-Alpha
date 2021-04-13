// Author: John-William Lebel, 2021-04-08, creation

#ifdef COMPILE_ESPCAM_ALPHA

#include "Arduino.h"

#include "src/core/Esp32DualCore.h"

#include "src/utils/timer/TimerMicros.h"

#include "src/peripheral/i2c/I2cProtocol.h"

TimerMicros programTimer
{
    10000,
    []()
    {}
};

void setup()
{

}

void loop()
{

}

void Esp32DualCore::main()
{
    while(true)
    {
        
    }
}

#endif