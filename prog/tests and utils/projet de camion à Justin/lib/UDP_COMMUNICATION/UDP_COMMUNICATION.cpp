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

#include <Arduino.h>
#include "UDP_COMMUNICATION.h"
#include <stdio.h>

#define membersof(x) (sizeof(x) / sizeof(x[0]))

char  ReplyMessage[2] = {0xFF, 0xFF};
char* Reply = ReplyMessage;

UDP_COMMUNICATION::UDP_COMMUNICATION(const char* ssid, const char* password,unsigned int localUdpPort)
{
    _ssid = ssid;
    _password = password;
    _localUdpPort = localUdpPort;
}

void UDP_COMMUNICATION::ConnectToWiFi(void)
{
    Serial.print("Connecting to ");
    Serial.print(_ssid);
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
     }
     Serial.println("");
     Serial.println("WiFi connected.");
     Serial.println("IP address:");
     Serial.println(WiFi.localIP());

     Udp.begin(_localUdpPort);
}

char * UDP_COMMUNICATION::ReceivePacket(void)
{
    int packetSize = Udp.parsePacket();
    if (packetSize)
    {
      Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
     int len = Udp.read(incomingPacket, 255);
    if (len >0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: ");
    return incomingPacket;
  }
  else
  {
    return Reply;
  }
  
}

void UDP_COMMUNICATION::SendPacket(unsigned char* Message, IPAddress targetIP)
{
  Udp.beginPacket(targetIP, _localUdpPort);
  Serial.print("Sending UDP message to: ");
  Serial.println(targetIP);
  //Serial.printf("Sending: %02X\n", Message);
  Udp.write(Message, 1);
  Udp.endPacket();
}