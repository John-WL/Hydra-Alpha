// Author: John-William Lebel, 2021-04-08, creation

#include "src/core/Esp32DualCore.h"

#include "src/mode/FunctioningMode.h"

#include "src/io_tank_alpha/input/Inputs.h"
#include "src/io_tank_alpha/output/Outputs.h"

#include "src/utils/timer/TimerMicros.h"

#include "src/peripheral/i2c/I2cProtocol.h"

TimerMicros programTimer
{
    10000,
    []()
    {
        Inputs::update();
        FunctioningMode::execute();
        Outputs::update();
    }
};

void setup()
{
    Serial.begin(9600);
    
    I2cProtocol::init();
    Inputs::init();
    Outputs::init();
    Esp32DualCore::init();

    programTimer.start();
}

void loop()
{
    programTimer.update();
}

void Esp32DualCore::main()
{
    while(true)
    {
        Serial.println("core 2");
    }
}
