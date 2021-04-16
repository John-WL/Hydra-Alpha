// Author: John-William Lebel, 2021-04-08, creation
// 2021-04-11, added "sequenced functions"

#include "Inputs.h"

#include "Arduino.h"

#include "Vector.h"

#include "../../utils/sequence/Sequence.h"

#include "battery/BatteryVoltageSensor.h"
#include "sonar/Sonar.h"

#include "../../peripheral/i2c/bno055/Bno055.h"

#include "../../peripheral/i2c/esp_cam/EspCamSlave.h"

void Inputs::init()
{
    BatteryVoltageSensor::init();
    Sonar::init([](long distance){});
    Bno055::init();
    EspCamSlave::init();
}

void Inputs::update()
{
    _inputSequencer.update();
}

std::vector<void (*)(void)> Inputs::_updateFunctions = {
    []()
    {
        BatteryVoltageSensor::sample();
        Sonar::requestUpdate();
    },
    []()
    {
        Bno055::update();
        EspCamSlave::update();
    }
};

Sequence Inputs::_inputSequencer{_updateFunctions};

