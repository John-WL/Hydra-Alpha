// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "Wire.h"

#include "../shared/core/Esp32DualCore.h"

#include "peripheral/slow_i2c/esp_cam/EspCam.h"

#include "../shared/utils/timer/TimerMicros.h"

#include "mode/FunctioningMode.h"

#include "io/input/Inputs.h"
#include "io/output/Outputs.h"

#include "io/input/sonar/Sonar.h"


TimerMicros programTimer
{
    10000,
    []()
    {
        //Inputs::update();
        //FunctioningMode::execute();
        //Outputs::update();
        Sonar::init([](long distance)
        {
            Serial.println(distance);
        });
    }
};

void setup()
{
    Esp32DualCore::init();

    Serial.begin(SERIAL_COMMUNICATION_SPEED);
    //Wire.begin();

    //Inputs::init();
    //Outputs::init();

    //programTimer.start();
}

void loop()
{
    //programTimer.update();
    Sonar::requestUpdate();

    //delay(1000);
}

void Esp32DualCore::main()
{
    while(true)
    {
        //EspCam::update();
    }
}
