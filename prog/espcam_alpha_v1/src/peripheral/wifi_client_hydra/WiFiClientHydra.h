// Author: John-William Lebel, 2021-04-16, creation



// useful links...

// tutorial for basic library access and examples:
// https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/

// video explanation of exactly what we want to do:
// https://www.youtube.com/watch?v=TfuEI1-YrsA&ab_channel=ThatProject



#ifndef WI_FI_CLIENT_HYDRA_H
#define WI_FI_CLIENT_HYDRA_H

#include "WiFi.h"
#include "ArduinoWebsockets.h"

#include "Vector.h"

#include "../../utils/timer/TimerMicros.h"

#define WI_FI_CLIENT_HYDRA_SSID_REMOTE "Hydra::Remote"
#define WI_FI_CLIENT_HYDRA_GENERAL_PASSWORD "S.H.I.E.L.D."

#define WI_FI_CLIENT_HYDRA_SERVER_IP "192.168.4.1"
#define WI_FI_CLIENT_HYDRA_SERVER_PORT 8888

// 1'000'000µS = 1S
#define WI_FI_CLIENT_HYDRA_WAIT_TIME_BEFORE_TRYING_TO_RECONNECT_AGAIN 1000000

class WiFiClientHydra
{
    public:
        static void init();
        static void sendDataToRemote(std::vector<uint8_t> data);
        static void getRemoteSignalStrength();

    private:
        static void _handleDisconnection(void (*_sendData)(void));
        static void _sendData();
        static void _connectToWiFiServer();
        static void _connectClient();
        static void _resetReconnectionTimoutReached();

        static bool _tryReconnectionTimeoutReached;
        static TimerMicros _reconnectionDelayTimer;
        static websockets::WebsocketsClient _client;
        static bool _isClientConnected;
};

#endif