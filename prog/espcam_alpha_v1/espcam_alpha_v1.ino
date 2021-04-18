// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "Vector.h"

#include "esp_camera.h"

#include "src/core/esp32_dual_core/Esp32DualCore.h"

#include "src/peripheral/camera_sensor/CameraSensor.h"
#include "src/peripheral/wifi_client_hydra/WiFiClientHydra.h"
#include "src/peripheral/tank_alpha/TankAlpha.h"

void setup()
{
    Serial.begin(115200);
    //Serial.setDebugOutput(true);

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
    {}
}