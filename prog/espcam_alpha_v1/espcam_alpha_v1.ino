// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "esp_camera.h"

#include "../tank_alpha_v1/src/core/Esp32DualCore.h"

#include "../tank_alpha_v1/src/utils/timer/TimerMicros.h"

#define CAMERA_DESIRED_FPS 4
#define CAMERA_DESIRED_REFRESH_PERIOD (1 / CAMERA_DESIRED_FPS)
#define CAMERA_DESIRED_REFRESH_PERIOD_MICROSECONDS (1000000 * CAMERA_DESIRED_REFRESH_PERIOD)

TimerMicros cameraShotTimer{CAMERA_DESIRED_REFRESH_PERIOD_MICROSECONDS, handlerCameraFrame};

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println();

    cameraShotTimer.start();
}

void loop()
{
    cameraShotTimer.update();
}

void Esp32DualCore::main()
{
    while(true)
    {
        
    }
}