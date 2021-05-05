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

#include "../../../shared/utils/timer/TimerMicros.h"

#define WI_FI_CLIENT_HYDRA_WAIT_TIME_BEFORE_TRYING_TO_RECONNECT_AGAIN 1000000

class WiFiClientHydra
{
public:
    static void init();
    static void sendDataToRemote(std::vector<uint8_t> data);
    static int8_t getRemoteSignalStrength();

private:
    static void _sendData(std::vector<uint8_t> data);

    static websockets::WebsocketsClient _client;
};

#endif