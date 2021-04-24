#ifndef CUSTOM_SERIAL2_INTERFACE_H
#define CUSTOM_SERIAL2_INTERFACE_H

#include "SerialIO.h"

#include "Arduino.h"

#include "Vector.h"

#define RX2_PIN 16
#define TX2_PIN 17

namespace SerialMaster
{
    void begin(unsigned long bps)
    {
        Serial2.begin(bps, SERIAL_8N1, RX2_PIN, TX2_PIN);
    }

    void send(std::vector<uint8_t> data)
    {
        return SerialIO::send(Serial2, data);
    }

    std::vector<uint8_t> receive(unsigned char dataLength)
    {
        return SerialIO::receive(Serial2, dataLength);
    }
}

#endif