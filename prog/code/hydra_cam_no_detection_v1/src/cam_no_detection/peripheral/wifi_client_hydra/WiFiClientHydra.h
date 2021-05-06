// Author: John-William Lebel, 2021-04-16, creation



// useful links...

// tutorial for basic library access and examples:
// https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/

// video explanation of exactly what we want to do:
// https://www.youtube.com/watch?v=TfuEI1-YrsA&ab_channel=ThatProject


// Here's an example implementation in the main:
/*
void setup()
{
    WiFiClientHydra::init();
}

void loop()
{
    std::vector<uint8_t> dataToSend{};

    //... fill the vector with your data

    WiFiClientHydra::sendDataToRemote(dataToSend);
}
*/


#ifndef WI_FI_CLIENT_HYDRA_H
#define WI_FI_CLIENT_HYDRA_H

// 2 seconds
#define CONNECTION_TIMEOUT 2000000

#define WI_FI_SERVER_SSID "Hydra::Remote"
#define WI_FI_SERVER_PASSWORD "S.H.I.E.L.D."

#define WI_FI_SERVER_IP "192.168.4.1"
#define WI_FI_SERVER_PORT 8888

#include "WiFi.h"
#include "ArduinoWebsockets.h"

#include "Vector.h"

class WiFiClientHydra
{
public:
    static void init();
    static void sendDataToRemote(std::vector<uint8_t> data);

private:
    static void _sendData(std::vector<uint8_t> data);

    static websockets::WebsocketsClient _client;
};

#endif