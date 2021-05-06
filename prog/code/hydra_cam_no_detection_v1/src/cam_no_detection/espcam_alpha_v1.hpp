// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "peripheral/wifi_client_hydra/WiFiClientHydra.h"
#include "peripheral/camera_sensor/CameraSensor.h"

void setup()
{
    Serial.begin(115200);

    WiFiClientHydra::init();
    CameraSensor::init(WiFiClientHydra::sendDataToRemote);
}

void loop()
{
    CameraSensor::update();
}
