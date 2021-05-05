// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "esp_camera.h"

#include "../shared/core/Esp32DualCore.h"

#include "peripheral/serial_tank/Tank.h"
#include "peripheral/camera_sensor/CameraSensor.h"
#include "peripheral/wifi_client_hydra/WiFiClientHydra.h"


void setup()
{
    Serial.begin(115200);
    //Serial.setDebugOutput(true);

    // put your WiFi sender implementation in the brackets
    WiFiClientHydra::init();
    CameraSensor::init(WiFiClientHydra::sendDataToRemote);

    Esp32DualCore::init();
}

void loop()
{
    CameraSensor::update();
}

void Esp32DualCore::main()
{
    //Tank::init();
    
    while(true)
    {
        //Tank::update();
    }
}
