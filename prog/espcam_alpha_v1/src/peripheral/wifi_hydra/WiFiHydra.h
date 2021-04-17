// Author: John-William Lebel, 2021-04-16, creation



// useful links...

// tutorial for basic library access and examples:
// https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/

// video explanation of exactly what we want to do:
// https://www.youtube.com/watch?v=TfuEI1-YrsA&ab_channel=ThatProject



#ifndef WI_FI_HYDRA_H
#define WI_FI_HYDRA_H

#include "WiFi.h"
#include "ArduinoWebsockets.h"

#include "../../utils/timer/TimerMicros.h"

#define WI_FI_HYDRA_SSID_REMOTE "Hydra::Remote"
#define WI_FI_HYDRA_SSID_ALPHA "Hydra::Alpha"
#define WI_FI_HYDRA_SSID_OMEGA "Hydra::Omega"
#define WI_FI_HYDRA_GENERAL_PASSWORD "S.H.I.E.L.D."

#define WEBSOCKETS_SERVER_IP "192.168.4.1"
#define WEBSOCKETS_SERVER_PORT 8888

#define WI_FI_HYDRA_WAIT_TIME_BEFORE_TRYING_TO_RECONNECT_AGAIN 1000000

class WiFiHydra
{
    public:
        static void init();
        static void sendDataToRemote(std::vector<uint8_t> data);

    private:
        static void _resetReconnectionTimoutReached();

        static bool _tryReconnectionTimeoutReached;
        static TimerMicros _reconnectionDelayTimer;
        static websockets::WebsocketsClient _clientAlpha;
};

#endif