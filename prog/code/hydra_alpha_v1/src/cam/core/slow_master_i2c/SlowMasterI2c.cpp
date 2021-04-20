// Author: John-William Lebel, 2021-04-19, creation

#include "SlowMasterI2c.h"

#include "Arduino.h"

#include "QueueArray.h"

#include "../../../../projectConfig.h"  // for easy on/off debugging

void SlowMasterI2c::init(uint8_t sdaPin, uint8_t sclPin)
{
    serialDebug("slow master I2C init");
    _sdaPin = sdaPin;
    _sclPin = sclPin;

    pinMode(_sdaPin, INPUT);
    pinMode(_sclPin, INPUT);
    digitalWrite(_sdaPin, LOW);
    digitalWrite(_sclPin, LOW);
}

void SlowMasterI2c::send(uint8_t slaveAddress, QueueArray<uint8_t>& sendData)
{
    _startBit();
    _sendByte(slaveAddress & (~0x01));
    for(int i = 0; sendData.count() > 0; i++)
    {
        serialDebug("sending 8 bits...");
        _sendByte(sendData.pop());
    }
    _stopBit();
}

QueueArray<uint8_t> SlowMasterI2c::request(uint8_t slaveAddress, uint8_t amount)
{
    QueueArray<uint8_t> getData{};

    _startBit();
    _sendByte(slaveAddress | 0x01);
    for(int i = 0; i < amount; i++)
    {
        getData.push(_getByte());
    }
    _stopBit();

    return getData;
}

void SlowMasterI2c::_sendByte(uint8_t byte)
{
    for(int i = 0; i < 8; i++)
    {
        _sendBit(byte & (0x80 >> i));
    }
    _getAcknowledge();
}

uint8_t SlowMasterI2c::_getByte()
{
    uint8_t byte = 0;

    for(int i = 0; i < 8; i++)
    {
        byte |= _getBit() ? (0x80 >> i) : 0;
    }
    _getAcknowledge();

    return byte;
}

void SlowMasterI2c::_sendBit(bool bitValue)
{
    bitValue ?                  // data set
        pinMode(_sdaPin, INPUT) :
        pinMode(_sdaPin, OUTPUT);
    delayMicroseconds(I2C_PIN_CHANGE_DELAY);
    pinMode(_sclPin, INPUT);    // sync
    delayMicroseconds(I2C_PIN_CHANGE_DELAY);
    pinMode(_sclPin, OUTPUT);   // fetch
    delayMicroseconds(I2C_PIN_CHANGE_DELAY);
}

bool SlowMasterI2c::_getBit()
{
    pinMode(_sclPin, INPUT);    // sync
    delayMicroseconds(I2C_PIN_CHANGE_DELAY);
    bool bitValue = digitalRead(_sdaPin);
    pinMode(_sclPin, OUTPUT);   // fetch
    delayMicroseconds(I2C_PIN_CHANGE_DELAY);
    return bitValue;
}

bool SlowMasterI2c::_getAcknowledge()
{
    return _getBit();
}

void SlowMasterI2c::_startBit()
{
    pinMode(_sdaPin, OUTPUT);   // start
    delayMicroseconds(I2C_PIN_CHANGE_DELAY);
    pinMode(_sclPin, OUTPUT);   // fetch
    delayMicroseconds(I2C_PIN_CHANGE_DELAY);
}

void SlowMasterI2c::_stopBit()
{
    pinMode(_sdaPin, OUTPUT);   // don't care
    delayMicroseconds(I2C_PIN_CHANGE_DELAY);
    pinMode(_sclPin, INPUT);    // sync
    delayMicroseconds(I2C_PIN_CHANGE_DELAY);
    pinMode(_sdaPin, INPUT);    // stop
    delayMicroseconds(I2C_PIN_CHANGE_DELAY);
}

uint8_t SlowMasterI2c::_sdaPin{0};
uint8_t SlowMasterI2c::_sclPin{0};

QueueArray<uint8_t> SlowMasterI2c::_readData{};