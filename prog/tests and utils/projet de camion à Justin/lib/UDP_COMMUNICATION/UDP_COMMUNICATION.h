/* 
                                                                  YAao,
                                                                   Y8888b,  
  _______    _        _         _   _       _                    ,oA8888888b,  
 |__   __|  | |      | |       | \ | |     | |             ,aaad8888888888888888bo,
    | | ___ | |_ __ _| |_   _  |  \| | ___ | |_         ,d888888888888888888888888888b,
    | |/ _ \| __/ _` | | | | | | . ` |/ _ \| __|      ,888888888888888888888888888888888b,
    | | (_) | || (_| | | |_| | | |\  | (_) | |_      d8888888888888888888888888888888888888,
    |_|\___/_\__\__,_|_|\__, | |_| \_|\___/ \__|    d888888888888888888888888888888888888888b
     /\     \ \    / (_) __/ |                     d888888P'                    `Y888888888888,
    /  \     \ \  / / _ |___/_   _ ___             88888P'                    Ybaaaa8888888888l
   / /\ \     \ \/ / | | '__| | | / __|           a8888'                      `Y8888P' `V888888
  / ____ \     \  /  | | |  | |_| \__ \         d8888888a                                `Y8888
 /_/    \_\     \/   |_|_|   \__,_|___/        AY/'' `\Y8b                                 ``Y8b
                                               Y'      `YP                                    ~~
                                                        `'                                       
Name:          UDP_COMMUNICATION.h
Created by:    Justin Bourassa - TotalyNotAVirus
Creation Date: 16-11-2020
Description:   Library to transfert data with UDP
*/

#ifndef UDP_COMMUNICATION_h
#define UDP_COMMUNICATION_h


#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>



class UDP_COMMUNICATION
{
    public:
        UDP_COMMUNICATION(const char* ssid, const char* password,unsigned int localUdpPort);
        void ConnectToWiFi(void);
        char * ReceivePacket(void);
        void SendPacket(unsigned char* Message, IPAddress targetIP);

    private:
        WiFiUDP Udp;
        const char* _ssid;
        const char* _password;
        unsigned int _localUdpPort;
        char incomingPacket[255];
        char replyPacket[16] = "Reception Done!";

};


#endif