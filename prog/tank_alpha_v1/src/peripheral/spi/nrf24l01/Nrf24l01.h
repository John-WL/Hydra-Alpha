// Author: John-William Lebel, 2021-04-14, creation

#ifndef NRF24L01_H
#define NRF24L01_H

#include "SPI.h"
#include "RF24.h"
#include "RF24Network.h"

#include "../../protocol_format/MainCommunicationFormat.h"

#include "Vector.h"

#define NRF24L01_CE_PIN 4
#define NRF24L01_CSN_PIN 5

#define NRF24L01_ADDRESS_REMOTE "000000"
#define NRF24L01_ADDRESS_ALPHA  "000001"
#define NRF24L01_ADDRESS_OMEGA  "000002"

#define NRF24L01_REMOTE_LEVEL 1

class Nrf24l01
{
    public:
        static void init();
        static void update();
        static std::vector<MainCommunicationFormat> dataToSend;
        static std::vector<MainCommunicationFormat> dataReceived;
    
    private:
        static RF24 _nrf24l01;
        static RF24Network _network;
        static void _sendData();
        static void _receiveData();
        static void _clearBuffer(std::vector<MainCommunicationFormat>* buffer);
        

};

#endif