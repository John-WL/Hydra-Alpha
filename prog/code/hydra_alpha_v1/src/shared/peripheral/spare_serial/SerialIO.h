#ifndef CUSTOM_SERIAL_IO_INTERFACE_H
#define CUSTOM_SERIAL_IO_INTERFACE_H

#include "Arduino.h"

#include "Vector.h"

#include "../../utils/timer/TimerMicros.h"

class SerialIO
{
public:
    static void send(HardwareSerial serial, std::vector<uint8_t> data);
    static std::vector<uint8_t> receive(HardwareSerial serial, unsigned char dataLength);
    
private:
    static uint8_t _receiveByte(HardwareSerial serial);

    static bool isReceptionTimeoutReached;
    static TimerMicros receptionTimeout;
};

#endif