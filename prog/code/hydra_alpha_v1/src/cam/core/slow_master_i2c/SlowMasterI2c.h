// Author: John-William Lebel, 2021-04-18, creation

#ifndef SLOW_MASTER_I2C_H
#define SLOW_MASTER_I2C_H

#include "../../../../projectConfig.h"

#ifdef ENABLE_SERIAL_DEBUGGING
#define I2C_PIN_CHANGE_DELAY 2000
#else
#define I2C_PIN_CHANGE_DELAY 60
#endif

#include "Vector.h"

#include "Arduino.h"

#include "QueueArray.h"

class SlowMasterI2c
{
public:
    static void init(uint8_t sdaPin, uint8_t sclPin);
    static void send(uint8_t slaveAddress, QueueArray<uint8_t>& sendData);
    static QueueArray<uint8_t> request(uint8_t slaveAddress, uint8_t amount);

private:
    static void _startBit();
    static void _stopBit();

    static void _sendBit(bool value);
    static bool _getBit();
    static bool _getAcknowledge();

    static void _sendByte(uint8_t byte);
    static uint8_t _getByte();

    static uint8_t _sdaPin;
    static uint8_t _sclPin;

    static QueueArray<uint8_t> _readData;
};

#endif