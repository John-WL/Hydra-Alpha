// Author: John-William Lebel, 2021-04-17, creation

#ifndef SOFT_SLAVE_I2C_H
#define SOFT_SLAVE_I2C_H

#include "Vector.h"

namespace SoftI2cSlaveCommunicationState
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

class SoftI2cSlave
{
public:
    SoftI2cSlave(uint8_t chipAddress, uint8_t sdaPin, uint8_t sclPin);
    std::vector<uint8_t> generateDataToTransmit(std::vector<uint8_t> receivedData);

private:
    void IRAM_ATTR _onSdaChange();
    void IRAM_ATTR _onSclChange();

    uint8_t _chipAddress;
    uint8_t _sdaPin;
    uint8_t _sclPin;
    bool _sdaState;
    bool _sclState;

    uint8_t _receivedAddressSelect;
    uint8_t _communicationState;
    uint8_t _bitCount;

    bool _sendsAcknowledges;

    uint8_t _receivedByte;
    uint8_t _transmitByte;
    std::vector<uint8_t> _receivedData;
    std::vector<uint8_t> _transmitData;

};

#endif