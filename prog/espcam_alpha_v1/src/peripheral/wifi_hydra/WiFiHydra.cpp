// Author: John-William Lebel, 2021-04-16, creation

#include "WiFiHydra.h"

#include "Arduino.h"

#include "WiFi.h"
#include "ArduinoWebsockets.h"

#include "Vector.h"

void WiFiHydra::init()
{
    WiFi.begin(WI_FI_HYDRA_SSID_REMOTE, WI_FI_HYDRA_GENERAL_PASSWORD);
    _clientAlpha.connect(WEBSOCKETS_SERVER_IP, WEBSOCKETS_SERVER_PORT, "/");
    _reconnectionDelayTimer.start();
}

void WiFiHydra::sendDataToRemote(std::vector<uint8_t> data)
{
    // WiFi connected?
    if(WiFi.status() == WL_CONNECTED && _clientAlpha.available())
    {
        // send data
        _clientAlpha.sendBinary((const char*)&data, data.size());
    }
    // WiFi disconnected.
    else
    {
        // make sure the reconnection timer is updated
        _reconnectionDelayTimer.update();
        // if the reconnection timeout is reached
        if(_tryReconnectionTimeoutReached)
        {
            // disconnect to reconnect later on
            if(WiFi.status() != WL_CONNECTED)
            {
                // Try to connect the WiFi object to Remote.
                // We are still not connected to the server.
                WiFi.disconnect();
                WiFi.begin(WI_FI_HYDRA_SSID_REMOTE, WI_FI_HYDRA_GENERAL_PASSWORD);
            }
            else
            {
                // Try to connect our client object to Remote.
                // We are connected to the server, but our client object isn't yet.
                _clientAlpha.connect(WEBSOCKETS_SERVER_IP, WEBSOCKETS_SERVER_PORT, "/");
            }
            // Restart reconnection timeout.
            _tryReconnectionTimeoutReached == false;
            _reconnectionDelayTimer.start();
        }
    }
}

void WiFiHydra::_resetReconnectionTimoutReached()
{
    _tryReconnectionTimeoutReached = true;
}

bool WiFiHydra::_tryReconnectionTimeoutReached{false};
TimerMicros WiFiHydra::_reconnectionDelayTimer
{
    WI_FI_HYDRA_WAIT_TIME_BEFORE_TRYING_TO_RECONNECT_AGAIN,
    _resetReconnectionTimoutReached
};
websockets::WebsocketsClient WiFiHydra::_clientAlpha{};