// Author: John-William Lebel, 2021-04-14, creation

#include "Nrf24l01.h"

#include "SPI.h"
#include "RF24.h"
#include "RF24Network.h"

#include "../../protocol_format/MainCommunicationFormat.h"

#include "Vector.h"

void Nrf24l01::init()
{
    SPI.begin();
    bool initializationFailed = !_nrf24l01.begin();

    if(initializationFailed)
    {
        Serial.println("Nrf24L01 initialisation failed.");
        return;
    }

    _network.begin(01);
    _network.multicastRelay = true;
}

void Nrf24l01::update()
{
    _network.update();
}

void Nrf24l01::_receiveData()
{
    while(_network.available())
    {
        RF24NetworkHeader header;
        MainCommunicationFormat* receivedPacketFromNrf24l01 = new MainCommunicationFormat{};
        _network.read(header, receivedPacketFromNrf24l01, sizeof(*receivedPacketFromNrf24l01));
        dataReceived.push_back(*receivedPacketFromNrf24l01);
    }
}

void Nrf24l01::_sendData()
{
    _network.begin(01);
    RF24NetworkHeader emptyHeader{};
    bool sentSuccessfully = _network.multicast(emptyHeader, &dataToSend, dataToSend.size()*sizeof(MainCommunicationFormat), NRF24L01_REMOTE_LEVEL);
    if(sentSuccessfully)
    {
        _clearBuffer(&dataToSend);
        return;
    }
    _network.begin(021);
    sentSuccessfully = _network.multicast(emptyHeader, &dataToSend, dataToSend.size()*sizeof(MainCommunicationFormat), NRF24L01_REMOTE_LEVEL);
    if(sentSuccessfully)
    {
        _clearBuffer(&dataToSend);
        return;
    }
}

void Nrf24l01::_clearBuffer(std::vector<MainCommunicationFormat>* buffer)
{
    for(std::vector<MainCommunicationFormat>::iterator dataIterator = ++buffer->begin(); 
        dataIterator < buffer->end();
        dataIterator++)
    {
        // wtf?
        delete &(*dataIterator);
    }

    buffer->clear();
}

RF24 Nrf24l01::_nrf24l01{NRF24L01_CE_PIN, NRF24L01_CSN_PIN};
RF24Network Nrf24l01::_network{_nrf24l01};

std::vector<MainCommunicationFormat> dataToSend{};
std::vector<MainCommunicationFormat> dataReceived{};