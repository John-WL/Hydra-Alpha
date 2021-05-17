// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "Wire.h"

#include "../shared/core/Esp32DualCore.h"

#include "peripheral/serial/esp_cam/EspCam.h"

#include "peripheral/spi/HydraRF/HydraRF.h"

#include "../shared/utils/timer/TimerMicros.h"

#include "mode/FunctioningMode.h"

#include "io/input/Inputs.h"
#include "io/output/Outputs.h"

#include "io/input/sonar/Sonar.h"


TimerMicros programTimer
{
    3000,
    []()
    {
        Inputs::update();
        FunctioningMode::execute();
        Outputs::update();
    }
};

void setup()
{
    Esp32DualCore::init();

    Serial.begin(SERIAL_COMMUNICATION_SPEED);
    Wire.begin();

    Inputs::init();
    Outputs::init();

    programTimer.start();
}

void loop()
{
    programTimer.update();
}

void Esp32DualCore::main()
{
    init_RF();
    while(true)
    {
        update_RF();

        // the bdc motors are updated here because they need the greatest refresh rate possible
        Outputs::bdcMotorLeft.update();
        Outputs::bdcMotorRight.update();
    }
}
