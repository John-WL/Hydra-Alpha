// Author: John-William Lebel, 2021-04-11, creation

#ifndef I2C_PROTOCOL_H
#define I2C_PROTOCOL_H

#define I2C_RECEIVE_TIMEOUT_MICROSECONDS 1000L
#define I2C_RECEIVE_MAX_MEMORY_USAGE 10

#include "Arduino.h"

class I2cProtocol
{
    public:
        static void transmit(unsigned char deviceAddress, unsigned char* data, unsigned char dataLength);
        static unsigned char* receive(unsigned char deviceAddress, unsigned char dataLength);
    private:
        static void endReception();
        static bool transmissionDone;
};

#endif
