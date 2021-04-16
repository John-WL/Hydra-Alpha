// Author: John-William Lebel, 2021-04-14, creation

#include "Nrf24l01.h"

#include "SPI.h"
#include "RF24.h"
#include "RF24Network.h"

#include "../../../utils/timer/TimerMicros.h"

#include "../../protocol_format/IncommingCommunicationFormat.h"
#include "../../protocol_format/OutgoingCommunicationFormat.h"

#include "Vector.h"

void Nrf24l01::init(void (*onReceive)(std::vector<IncommingCommunicationFormat> data))
{
    _onReceive = onReceive;
    SPI.begin();
    bool initializationFailed = !_nrf24l01.begin();
    if(initializationFailed)
    {
        Serial.println("nrf24l01 initialisation failed.");
        return;
    }
    _network.begin(NRF24L01_ALPHA_NODE);
    _network.multicastRelay = true;
}

void Nrf24l01::update()
{
    _network.update();
}

void Nrf24l01::sendData(std::vector<OutgoingCommunicationFormat> dataToSend)
{
    // try first to send data on the main line
    _network.begin(NRF24L01_ALPHA_NODE);
    RF24NetworkHeader emptyHeader{};
    bool sentSuccessfully = _network.multicast(emptyHeader, &dataToSend, dataToSend.size()*sizeof(OutgoingCommunicationFormat), NRF24L01_REMOTE_LEVEL);
    if(sentSuccessfully)
    {
        _receptionFailureTimeout.start();
        return;
    }
    // if it didn't work, try to send data on the secondary line
    _network.begin(NRF24L01_ALPHA_ALTERNATIVE_NODE);
    sentSuccessfully = _network.multicast(emptyHeader, &dataToSend, dataToSend.size()*sizeof(OutgoingCommunicationFormat), NRF24L01_REMOTE_LEVEL);
    if(sentSuccessfully)
    {
        _receptionFailureTimeout.start();
        return;
    }

    // if we didn't receive anything, 
    // check if the reception timout is reached
    _receptionFailureTimeout.update();
}

void Nrf24l01::_receiveData()
{
    std::vector<IncommingCommunicationFormat> receivedData{};

    while(_network.available())
    {
        RF24NetworkHeader header;
        IncommingCommunicationFormat receivedPacketFromNrf24l01 = IncommingCommunicationFormat{};
        _network.read(header, &receivedPacketFromNrf24l01, sizeof(receivedPacketFromNrf24l01));
        if(header.from_node == NRF24L01_REMOTE_NODE)
        {
            receivedData.push_back(receivedPacketFromNrf24l01);
        }
    }

    _onReceive(receivedData);
}

void Nrf24l01::_handleConnectionFailure()
{
    // Do something about it!
    // Something like these will do:
    // - Get in automatic mode;
    // - Stop all motors and wait patiently.

}

void (*Nrf24l01::_onReceive)(std::vector<IncommingCommunicationFormat>){};

TimerMicros Nrf24l01::_receptionFailureTimeout
{
    NRF24L01_RECEPTION_TIMEOUT_BEFORE_CONSIDERED_FAILURE,
    _handleConnectionFailure
};

RF24 Nrf24l01::_nrf24l01{NRF24L01_CE_PIN, NRF24L01_CSN_PIN};
RF24Network Nrf24l01::_network{_nrf24l01};