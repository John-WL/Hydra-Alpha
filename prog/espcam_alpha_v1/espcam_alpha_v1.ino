// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "esp_camera.h"

#include "src/core/Esp32DualCore.h"

#include "src/io_esp_cam/camera_sensor/CameraSensor.h"

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    // put your WiFi sender implementation in
    // the brackets
    CameraSensor::init([](camera_fb_t* cameraFrameBuffer){});
}

void loop()
{
    CameraSensor::update();
}

void Esp32DualCore::main()
{
    while(true)
    {
        
    }
}