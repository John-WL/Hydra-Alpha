// Author: John-William Lebel, 2021-04-08, creation
// 2021-04-11, added "sequenced functions"

#include "Inputs.h"

#include "Arduino.h"

#include "Vector.h"

#include "../../../shared/utils/sequence/Sequence.h"

#include "battery/BatteryVoltageSensor.h"
#include "sonar/Sonar.h"

#include "../../peripheral/i2c/bno055/Bno055.h"

#include "../../peripheral/serial/esp_cam/EspCam.h"

void Inputs::init()
{
    BatteryVoltageSensor::init();
    //Sonar::init([](long distance){Sonar::measuredDistance = distance;});
    Bno055::init();
    //EspCam::init(); // updated in the second thread, see tank_alpha_v1.hpp
}

void Inputs::update()
{
    _inputSequencer.update();
}

std::vector<void (*)(void)> Inputs::_updateFunctions = {
    []()
    {
        BatteryVoltageSensor::sample();
        Serial.println(BatteryVoltageSensor::getValue());
        //Sonar::requestUpdate();
    },
    []()
    {
        Bno055::update();
        //EspCam::update();
    }
};

Sequence Inputs::_inputSequencer{_updateFunctions};

