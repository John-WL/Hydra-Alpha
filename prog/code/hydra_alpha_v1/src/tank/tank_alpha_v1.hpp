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
    5000,
    []()
    {
        Inputs::update();
        //FunctioningMode::execute();
        Outputs::update();
    }
};

void setup()
{
    Esp32DualCore::init();

    Serial.begin(SERIAL_COMMUNICATION_SPEED);
    Wire.begin();
    //init_RF();

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
    while(true)
    {
        //update_RF();
    }
}
