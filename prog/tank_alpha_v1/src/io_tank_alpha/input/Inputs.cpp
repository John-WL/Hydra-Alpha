// Author: John-William Lebel, 2021-04-08, creation
// 2021-04-11, added "sequenced functions"

#include "Inputs.h"

#include "Arduino.h"

#include "Vector.h"

#include "../../utils/sequence/Sequence.h"

#include "../../peripheral/i2c/bno055/Bno055.h"

#include "battery/BatteryVoltageSensor.h"
#include "sonar/Sonar.h"

void Inputs::init()
{
    BatteryVoltageSensor::init();
    Sonar::init([](long distance){});
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
    }
};

Imu* Inputs::onBoardImu = new Bno055{};

Sequence Inputs::_inputSequencer{_updateFunctions};

