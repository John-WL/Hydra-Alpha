// Author: John-William Lebel, 2021-04-16, creation

#include "WiFiClientHydra.h"

#include "Arduino.h"

#include "Vector.h"

#include "WiFi.h"
#include "ArduinoWebsockets.h"

void WiFiClientHydra::init()
{
    WiFi.begin(WI_FI_SERVER_SSID, WI_FI_SERVER_PASSWORD);

    uint32_t initialTimeOfBegin = micros();
    while(WiFi.status() != WL_CONNECTED)
    {
        yield();

        if((micros() - initialTimeOfBegin) > CONNECTION_TIMEOUT)
        {
            // We're gonna reset the Esp32 if we're still not connected on the next update() call.
            // This is just to make sure we don't get stuck here.
            break;
        }
    }

    while(!_client.connect(WI_FI_SERVER_IP, WI_FI_SERVER_PORT, "/"))
    {
        yield();

        // That's useful when we reset the Esp32 server exactly at the wrong moment.
        // We can get stuck here if we're not careful at the exact moment we reset the server.
        // This breaking code serves as a measure to prevent that. 
        if(WiFi.status() != WL_CONNECTED)
        {
            break;
        }
    }
}

void WiFiClientHydra::sendDataToRemote(std::vector<uint8_t> data)
{
    // try to send data first
    if(WiFi.status() == WL_CONNECTED)
    {
        _sendData(data);
    }
}

void WiFiClientHydra::reconnectWiFiOnConnectionLost()
{
    // if we're disconnected, re-init the WiFi
    if(WiFi.status() != WL_CONNECTED)
    {
        WiFi.disconnect();
        init();
    }
}

void WiFiClientHydra::_sendData(std::vector<uint8_t> data)
{
    // send data with the client object
    _client.sendBinary((const char*)&data[0], data.size());
}

websockets::WebsocketsClient WiFiClientHydra::_client{};
