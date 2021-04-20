// Author: John-William Lebel, 2021-04-17, creation

#ifndef SOFT_SLAVE_I2C_H
#define SOFT_SLAVE_I2C_H


// problem this intends to solve:
// https://github.com/espressif/arduino-esp32/issues/118



#include "Vector.h"

#include "Arduino.h"

namespace SoftSlaveI2cCommunicationState
{
    enum Enum
    {
        START,
        READ_ADDRESS,
        READ_DATA,
        WRITE_DATA,
        STOP,
        IDLE
    };
}

class SoftSlaveI2c
{
public:
    static void init(uint8_t chipAddress, uint8_t sdaPin, uint8_t sclPin);
    static void onReceive(std::vector<uint8_t> receivedData);
    static std::vector<uint8_t> onRequest();

private:
    static void IRAM_ATTR _onSdaChange();
    static void IRAM_ATTR _onSclChange();

    static uint8_t _chipAddress;
    static uint8_t _sdaPin;
    static uint8_t _sclPin;
    static bool _sdaState;
    static bool _sclState;

    static uint8_t _receivedAddressSelect;
    static uint8_t _communicationState;
    static uint8_t _bitCount;

    static bool _sendsAcknowledges;

    static uint8_t _receivedByte;
    static uint8_t _transmitByte;
    static std::vector<uint8_t> _receivedData;
    static std::vector<uint8_t> _transmitData;

    static bool _wasReceiving;

};

#endif