// Author: John-William Lebel, 2021-04-16, creation

#include "WiFiClientHydra.h"

#include "Arduino.h"

#include "WiFi.h"
#include "ArduinoWebsockets.h"

#include "Vector.h"

void WiFiClientHydra::init()
{
    _connectToWiFiServer();
    _connectClient();
    _reconnectionDelayTimer.start();
}

void WiFiClientHydra::sendDataToRemote(std::vector<uint8_t> data)
{
    // WiFi connected?
    if(WiFi.status() == WL_CONNECTED && _isClientConnected)
    {
        // send data
        _client.sendBinary((const char*)&data, data.size());

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
                WiFi.begin(WI_FI_CLIENT_HYDRA_SSID_REMOTE, WI_FI_CLIENT_HYDRA_GENERAL_PASSWORD);
            }
            else
            {
                // Try to connect our client object to Remote.
                // We are connected to the access point, but our client object isn't yet.
                _isClientConnected = _client.connect(WI_FI_CLIENT_HYDRA_SERVER_IP, WI_FI_CLIENT_HYDRA_SERVER_PORT, "/");
            }
            // Restart reconnection timeout.
            _tryReconnectionTimeoutReached == false;
            _reconnectionDelayTimer.start();
        }
    }
    
    //_signalStrength = 
}

void WiFiClientHydra::_connectToWiFiServer()
{
    WiFi.disconnect();
    WiFi.begin(WI_FI_CLIENT_HYDRA_SSID_REMOTE, WI_FI_CLIENT_HYDRA_GENERAL_PASSWORD);
}

void WiFiClientHydra::_connectClient()
{
    _isClientConnected = _client.connect(WI_FI_CLIENT_HYDRA_SERVER_IP, WI_FI_CLIENT_HYDRA_SERVER_PORT, "/");
}

void WiFiClientHydra::_resetReconnectionTimoutReached()
{
    _tryReconnectionTimeoutReached = true;
}

bool WiFiClientHydra::_tryReconnectionTimeoutReached{false};
TimerMicros WiFiClientHydra::_reconnectionDelayTimer
{
    WI_FI_CLIENT_HYDRA_WAIT_TIME_BEFORE_TRYING_TO_RECONNECT_AGAIN,
    _resetReconnectionTimoutReached
};
websockets::WebsocketsClient WiFiClientHydra::_client{};
bool WiFiClientHydra::_isClientConnected{false};
