// Author: John-William Lebel, 2021-04-08, creation
// 2021-04-11, added "sequenced functions"

#include "Inputs.h"

#include "Arduino.h"

#include "Vector.h"

#include "../../../shared/utils/sequence/Sequence.h"

#include "battery/BatteryVoltageSensor.h"
#include "sonar/SonarScanner.h"

#include "../../peripheral/i2c/bno055/Bno055.h"

#include "../../peripheral/serial/esp_cam/EspCam.h"

void Inputs::init()
{
    EspCam::init();
    BatteryVoltageSensor::init();
    SonarScanner::init();
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
        SonarScanner::update();
    },
    []()
    {
        std::vector<SonarSample> sonarSamples = SonarScanner::findDrivableSamples();
    },
    []()
    {
        Bno055::update();
        EspCam::update();
    }
};

Sequence Inputs::_inputSequencer{_updateFunctions};

