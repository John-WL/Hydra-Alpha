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
    // We're using a vector because arrays seem unusable with the websockets::WebsocketsMessage class.
    std::vector<websockets::WebsocketsMessage> messages{};

    // if we have any client that tries to connect to us
    if(_server.poll())
    {
        // save it
        _clients[_amountOfConnectedClients] = _server.accept();
        _amountOfConnectedClients++;
    }

    // look for received messages
    for(uint8_t i = 0; i < _amountOfConnectedClients; i++)
    {
        if(_clients[i].available() && _isWiFiEnabled[i])
        {
            messages.push_back(_receiveDataFrom(&_clients[i]));
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

#ifdef ENABLE_SIMULTANEOUS_RECEPTION
bool WiFiServerHydra::_isWiFiEnabled[2]{true, true};
#else
bool WiFiServerHydra::_isWiFiEnabled[2]{true, false};
#endif
uint8_t WiFiServerHydra::_amountOfConnectedClients{0};
websockets::WebsocketsServer WiFiServerHydra::_server{};
websockets::WebsocketsClient WiFiServerHydra::_clients[2]{};