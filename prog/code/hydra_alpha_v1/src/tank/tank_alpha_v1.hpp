// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "Wire.h"

#include "../shared/core/Esp32DualCore.h"

#include "mode/FunctioningMode.h"

#include "io/input/Inputs.h"
#include "io/output/Outputs.h"

#include "../shared/utils/timer/TimerMicros.h"

#include "peripheral/i2c/I2cProtocol.h"

#include "../shared/utils/math/vector/Vector3.h"

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
    Serial.begin(SERIAL_COMMUNICATION_SPEED);
    Wire.begin();

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
        
    }
}
