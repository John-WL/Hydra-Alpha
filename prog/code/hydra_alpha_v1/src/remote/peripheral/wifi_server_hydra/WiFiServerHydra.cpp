#include "WiFiServerHydra.h"

#include "WiFi.h"
#include "ArduinoWebsockets.h"

#include "Vector.h"

void WiFiServerHydra::init()
{
    WiFi.softAP(WI_FI_SERVER_SSID, WI_FI_SERVER_PASSWORD);
    _server.listen(WI_FI_SERVER_PORT);
}

void WiFiServerHydra::update()
{
    if(_server.poll())
    {
        _clients.push_back(_server.accept());
    }

    for
    (uint8_t i = 0; i < _clients.size(); i++)
    {
        if(_clients[i].available())
        {
            _receiveDataFrom(_clients[i]);
        }
    }
}

websockets::WebsocketsMessage WiFiServerHydra::_receiveDataFrom(websockets::WebsocketsClient client)
{
    client.poll();
    Serial.println("Read blocking...");
    websockets::WebsocketsMessage reception = client.readBlocking();

    Serial.print("Received data with length: ");
    Serial.println(reception.length());

    Serial.println();

    return reception;
}

websockets::WebsocketsServer WiFiServerHydra::_server{};
std::vector<websockets::WebsocketsClient> WiFiServerHydra::_clients{10};