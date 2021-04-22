// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "esp_camera.h"

#include "../shared/core/Esp32DualCore.h"

#include "peripheral/tank_alpha/TankAlpha.h"
#include "peripheral/camera_sensor/CameraSensor.h"
#include "peripheral/wifi_client_hydra/WiFiClientHydra.h"


void setup()
{
    Serial.begin(SERIAL_COMMUNICATION_SPEED);
    //Serial.setDebugOutput(true);

    Esp32DualCore::init();

    // put your WiFi sender implementation in the brackets
    WiFiClientHydra::init();
    CameraSensor::init(WiFiClientHydra::sendDataToRemote);
    TankAlpha::init();
}

void loop()
{
    CameraSensor::update();
}

void Esp32DualCore::main()
{
    while(true)
    {
        TankAlpha::update();
    }
}

