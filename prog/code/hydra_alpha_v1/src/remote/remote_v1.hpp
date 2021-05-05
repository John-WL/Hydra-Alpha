// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "../shared/core/Esp32DualCore.h"

#include "peripheral/wifi_server_hydra/WiFiServerHydra.h"


void setup()
{
    Serial.begin(115200);

    Esp32DualCore::init();
}

void loop()
{}

void Esp32DualCore::main()
{
    WiFiServerHydra::init();
    
    while(true)
    {
        WiFiServerHydra::update();
    }
}
