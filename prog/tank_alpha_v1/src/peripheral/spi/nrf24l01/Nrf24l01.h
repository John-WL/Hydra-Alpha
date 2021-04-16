// Author: John-William Lebel, 2021-04-14, creation

#ifndef NRF24L01_H
#define NRF24L01_H

#include "SPI.h"
#include "RF24.h"
#include "RF24Network.h"

#include "../../../utils/timer/TimerMicros.h"

#include "../../protocol_format/IncommingCommunicationFormat.h"
#include "../../protocol_format/OutgoingCommunicationFormat.h"

#include "Vector.h"

#define NRF24L01_CE_PIN 4
#define NRF24L01_CSN_PIN 5

#define NRF24L01_RECEPTION_TIMEOUT_BEFORE_CONSIDERED_FAILURE 40000

#define NRF24L01_REMOTE_LEVEL 1

#define NRF24L01_REMOTE_NODE 0
#define NRF24L01_ALPHA_NODE 1
#define NRF24L01_ALPHA_ALTERNATIVE_NODE 21


class Nrf24l01
{
    public:
        static void init(void (*onReceive)(std::vector<IncommingCommunicationFormat> dataReceived));
        static void update();
        static void sendData(std::vector<OutgoingCommunicationFormat> dataToSend);
    
    private:
        static void _receiveData();
        static void _handleConnectionFailure();

        static void (*_onReceive)(std::vector<IncommingCommunicationFormat> dataReceived);

        static TimerMicros _receptionFailureTimeout;

        static RF24 _nrf24l01;
        static RF24Network _network;

};

#endif