// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "esp_camera.h"

#include "../shared/core/Esp32DualCore.h"

#include "peripheral/serial_tank/Tank.h"
#include "peripheral/camera_sensor/CameraSensor.h"
#include "peripheral/wifi_client_hydra/WiFiClientHydra.h"


void setup()
{
    //Tank::init();
    Esp32DualCore::init();
    
    pinMode(33, OUTPUT);
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

    CameraSensor::enableSendingFramesOverWiFi(true);
    
    while(true)
    {
        WiFiClientHydra::reconnectWiFiOnConnectionLost();
        CameraSensor::update();
    }
}
