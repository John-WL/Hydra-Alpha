// Author: John-William Lebel, 2021-04-11, creation

#ifndef I2C_PROTOCOL_H
#define I2C_PROTOCOL_H

#define I2C_RECEIVE_TIMEOUT_MICROSECONDS 1000L
#define I2C_RECEIVE_MAX_MEMORY_USAGE 10

#include "Arduino.h"

#include "../../../shared/utils/timer/TimerMicros.h"

class I2cProtocol
{
    public:
        static void transmit(unsigned char deviceAddress, std::vector<unsigned char> data);
        static std::vector<unsigned char> receive(unsigned char deviceAddress, unsigned char dataLengthRequest);

    private:
        static void _endReception();

        static bool _receptionDone;
        static TimerMicros _receptionTimeoutTimer;

};

#endif
