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
    _reconnectionTimer.start();
}

void WiFiClientHydra::sendDataToRemote(std::vector<uint8_t> data)
{
    if(_wifiAndClientConnected())
    {
        _sendData(data);
    }
    else
    {
        _reconnectionTimer.update();
        if(_timeoutOfReconnectionReached)
        {
            _handleReconnection();
            _restartReconnectionTimer();
        }
    }
    
    _updateRemoteSignalStrength();
}

int8_t WiFiClientHydra::getRemoteSignalStrength()
{
    return _remoteRssiStrength;
}

bool WiFiClientHydra::_wifiAndClientConnected()
{
    return _wifiConnected() && _isClientConnected;
}

bool WiFiClientHydra::_wifiConnected()
{
    return (WiFi.status() == WL_CONNECTED);
}

void WiFiClientHydra::_sendData(std::vector<uint8_t> data)
{
    _client.sendBinary((const char*)&data, data.size());
}

void WiFiClientHydra::_handleReconnection()
{
    if(!_wifiConnected())
    {
        _connectToWiFiServer();
    }
    else
    {
        _connectClient();
    }
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

void WiFiClientHydra::_reconnectionTimeoutCallback()
{
    _timeoutOfReconnectionReached = true;
}

void WiFiClientHydra::_restartReconnectionTimer()
{
    _timeoutOfReconnectionReached == false;
    _reconnectionTimer.start();
}

int8_t WiFiClientHydra::_findRemoteSsidIndex()
{
    int8_t networkSize = WiFi.scanNetworks();
    for(int8_t i = 0; i < networkSize; i++)
    {
        if(WiFi.SSID(i) == WI_FI_CLIENT_HYDRA_SSID_REMOTE)
        {
            return i;
        }
    }

    return -1;
}

void WiFiClientHydra::_updateRemoteSignalStrength()
{
    int8_t remoteWiFiIndex = _findRemoteSsidIndex();
    if(remoteWiFiIndex >= 0)
    {
        _remoteRssiStrength = WiFi.RSSI(remoteWiFiIndex);
    }
    else
    {
        _remoteRssiStrength = -128;
    }
}

bool WiFiClientHydra::_timeoutOfReconnectionReached{false};
int8_t WiFiClientHydra::_remoteRssiStrength{-128};
TimerMicros WiFiClientHydra::_reconnectionTimer
{
    WI_FI_CLIENT_HYDRA_WAIT_TIME_BEFORE_TRYING_TO_RECONNECT_AGAIN,
    _reconnectionTimeoutCallback
};
websockets::WebsocketsClient WiFiClientHydra::_client{};
bool WiFiClientHydra::_isClientConnected{false};
