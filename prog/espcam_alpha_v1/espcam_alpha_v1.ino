// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "Vector.h"

#include "esp_camera.h"

#include "src/core/Esp32DualCore.h"

#include "src/peripheral/camera_sensor/CameraSensor.h"
#include "src/peripheral/wifi_hydra/WiFiHydra.h"

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    // put your WiFi sender implementation in
    // the brackets
    CameraSensor::init(WiFiHydra::sendDataToRemote);
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