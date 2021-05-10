#ifndef CUSTOM_SERIAL_INTERFACE_H
#define CUSTOM_SERIAL_INTERFACE_H

#include "SerialIO.h"

#include "Arduino.h"

#include "Vector.h"

namespace SerialSlave
{
    inline void begin(unsigned long bps)
    {
        Serial.begin(bps);
    }

    inline void send(std::vector<uint8_t> data)
    {
        return SerialIO::send(Serial, data);
    }

    inline std::vector<uint8_t> receive(unsigned char dataLength)
    {
        return SerialIO::receive(Serial, dataLength);
    }
}

#endif