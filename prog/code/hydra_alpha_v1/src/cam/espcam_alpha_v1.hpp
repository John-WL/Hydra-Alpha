// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "esp_camera.h"

#include "../shared/core/Esp32DualCore.h"

#include "peripheral/tank_alpha/Tank.h"
#include "peripheral/camera_sensor/CameraSensor.h"
#include "peripheral/wifi_client_hydra/WiFiClientHydra.h"


void setup()
{
    Serial.begin(115200);
    //Serial.setDebugOutput(true);

    //Tank::init();

    Esp32DualCore::init();
}

void loop()
{
        //Tank::update();
}

void Esp32DualCore::main()
{
    // put your WiFi sender implementation in the brackets
    WiFiClientHydra::init();
    CameraSensor::init(WiFiClientHydra::sendDataToRemote);
    
    while(true)
    {
        //Serial.println("update camera and WiFi");
        CameraSensor::update();
    }
}
