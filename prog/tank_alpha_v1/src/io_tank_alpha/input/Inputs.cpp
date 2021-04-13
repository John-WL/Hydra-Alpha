// Author: John-William Lebel, 2021-04-08, creation
// 2021-04-11, added "sequenced functions"

#include "Inputs.h"

#include "Arduino.h"

#include "Vector.h"

#include "../../utils/sequence/Sequence.h"

#include "../../peripheral/i2c/bno055/Bno055.h"

#include "../battery/BatteryVoltageSensor.h"

void Inputs::init()
{
    BatteryVoltageSensor::init();
    Bno055::init();
}

void Inputs::update()
{
    _inputSequencer.update();
}

std::vector<void (*)(void)> Inputs::_updateFunctions = {
    []()
    {
        BatteryVoltageSensor::sample();
        //Serial.println(BatteryVoltageSensor::getValue());
    },
    []()
    {
        //Serial.println("this is the part where I send useless data into the monitor for no apparent reason");
    }
};

Sequence Inputs::_inputSequencer{_updateFunctions};

