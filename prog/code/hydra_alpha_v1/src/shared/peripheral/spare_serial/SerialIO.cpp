#include "SerialIO.h"

#include "Arduino.h"

#include "Vector.h"

#include "../../utils/timer/TimerMicros.h"

void SerialIO::send(HardwareSerial serial, std::vector<uint8_t> data)
{
    serial.write((uint8_t*)&data, data.size());
}

std::vector<uint8_t> SerialIO::receive(HardwareSerial serial, unsigned char dataLength)
{
    static std::vector<uint8_t> dataReceived{2};
    dataReceived.clear();

    isReceptionTimeoutReached = false;
    receptionTimeout.start();
    while((dataReceived.size() < dataLength) 
            && !isReceptionTimeoutReached)
    {
        if(serial.available())
        {
            dataReceived.push_back(_receiveByte(serial));
        }
        receptionTimeout.update();
        
        yield();
    }

    return dataReceived;
}

uint8_t SerialIO::_receiveByte(HardwareSerial serial)
{
    return (uint8_t)serial.read();
}

bool SerialIO::isReceptionTimeoutReached{false};
TimerMicros SerialIO::receptionTimeout
{
    1000,
    []()
    {
        isReceptionTimeoutReached = true;
    }
};