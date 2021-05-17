#include "WiFiServerHydra.h"

#include "WiFi.h"
#include "ArduinoWebsockets.h"

#include "Vector.h"

#ifdef ENABLE_SIMULTANEOUS_RECEPTION
#define MAX_AMOUNT_OF_SIMULTANEOUS_MESSAGES 2
#else
#define MAX_AMOUNT_OF_SIMULTANEOUS_MESSAGES 1
#endif

void WiFiServerHydra::init()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(WI_FI_SERVER_SSID, WI_FI_SERVER_PASSWORD, 1, 0, 4);
    _server.listen(WI_FI_SERVER_PORT);
}

void WiFiServerHydra::update(void (*messageHandler)(websockets::WebsocketsMessage*, uint8_t))
{
    Serial.println("update call");
    // We're using a vector because arrays seem unusable with the websockets::WebsocketsMessage class.
    std::vector<websockets::WebsocketsMessage> messages{};

    // if we have any client that tries to connect to us
    if(_server.poll())
    {
        // save it
        _clients[_amountOfConnectedClients] = _server.accept();
        _amountOfConnectedClients++;
        Serial.println("Client connected.");
    }

    // look for received messages
    for(uint8_t i = 0; i < _amountOfConnectedClients; i++)
    {
        if(messages.size() >= MAX_AMOUNT_OF_SIMULTANEOUS_MESSAGES)
        {
            break;
        }

        if(_clients[i].available() && messages.size() < MAX_AMOUNT_OF_SIMULTANEOUS_MESSAGES)
        {
            Serial.println("before receive block");
            messages.push_back(_receiveDataFrom(&_clients[i]));
            Serial.println("after receive block");
        }
    }

    // only use the callback if we actually received anything
    if(messages.size() > 0)
    {
        messageHandler((websockets::WebsocketsMessage*)&messages[0], messages.size());
    }
}

websockets::WebsocketsMessage WiFiServerHydra::_receiveDataFrom(websockets::WebsocketsClient* client)
{
    client->poll();
    return client->readBlocking();
}

uint8_t WiFiServerHydra::_amountOfConnectedClients{0};
websockets::WebsocketsServer WiFiServerHydra::_server{};
websockets::WebsocketsClient WiFiServerHydra::_clients[2]{};