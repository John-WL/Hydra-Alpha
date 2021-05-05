// Author: John-William Lebel, 2021-04-16, creation

#include "WiFiClientHydra.h"

#include "Arduino.h"

#include "Vector.h"

#include "WiFi.h"
#include "ArduinoWebsockets.h"

#include "../../../remote/peripheral/wifi_server_hydra/WiFiServerHydra.h"

void WiFiClientHydra::init()
{
    WiFi.begin(WI_FI_SERVER_SSID, WI_FI_SERVER_PASSWORD);

    Serial.println("Connect WiFi...");
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");

    Serial.println("\nConnect socket...");
    while(!_client.connect(WI_FI_SERVER_IP, WI_FI_SERVER_PORT, "/"))
    {
        delay(500);
        Serial.print(".");
        if(WiFi.status() != WL_CONNECTED)
        {
            break;
        }
    }
    Serial.println("\nSocket connected");
}

void WiFiClientHydra::sendDataToRemote(std::vector<uint8_t> data)
{
    _sendData(data);

    Serial.println(WiFi.status() == WL_CONNECTED);
    if(WiFi.status() != WL_CONNECTED)
    {
        ESP.restart();
    }
}

void WiFiClientHydra::_sendData(std::vector<uint8_t> data)
{
    _client.sendBinary((const char*)&data, data.size());
}

websockets::WebsocketsClient WiFiClientHydra::_client{};
