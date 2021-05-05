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

void WiFiServerHydra::update()
{
    if(_server.poll())
    {
        _client = _server.accept();
    }

    if(_client.available())
    {
        _receiveDataFrom(_client);
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
websockets::WebsocketsClient WiFiServerHydra::_client{};