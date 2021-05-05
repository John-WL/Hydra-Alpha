#ifndef WI_FI_SERVER_HYDRA_H
#define WI_FI_SERVER_HYDRA_H

#include "WiFi.h"
#include "ArduinoWebsockets.h"

#include "Vector.h"

#define WI_FI_SERVER_SSID "Hydra::Remote"
#define WI_FI_SERVER_PASSWORD "S.H.I.E.L.D."

#define WI_FI_SERVER_IP "192.168.4.1"
#define WI_FI_SERVER_PORT 8888

class WiFiServerHydra
{
public:
    static void init();
    static void update();

private:
    static websockets::WebsocketsMessage _receiveDataFrom(websockets::WebsocketsClient client);

    static websockets::WebsocketsServer _server;
    static std::vector<websockets::WebsocketsClient> _clients;

};

#endif