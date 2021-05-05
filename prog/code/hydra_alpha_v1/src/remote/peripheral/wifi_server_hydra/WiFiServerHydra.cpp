#include "WiFiServerHydra.h"

#include "WiFi.h"
#include "ArduinoWebsockets.h"

#include "Vector.h"

void WiFiServerHydra::init()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(WI_FI_SERVER_SSID, WI_FI_SERVER_PASSWORD, 1, 0, 4);
    _server.listen(WI_FI_SERVER_PORT);
}

void WiFiServerHydra::update(void (*messageHandler)(websockets::WebsocketsMessage*, uint8_t))
{
    std::vector<websockets::WebsocketsMessage> messages{};

    if(_server.poll())
    {
        _clients[_amountOfConnectedClients] = _server.accept();
        _amountOfConnectedClients++;
    }

    for(uint8_t i = 0; i < _amountOfConnectedClients; i++)
    {
        if(_clients[i].available() && isWiFiEnabled[i])
        {
            messages.push_back(_receiveDataFrom(&_clients[i]));
        }
    }

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

bool WiFiServerHydra::isWiFiEnabled[2]{true, false};

uint8_t WiFiServerHydra::_amountOfConnectedClients{0};
websockets::WebsocketsServer WiFiServerHydra::_server{};
websockets::WebsocketsClient WiFiServerHydra::_clients[2]{};