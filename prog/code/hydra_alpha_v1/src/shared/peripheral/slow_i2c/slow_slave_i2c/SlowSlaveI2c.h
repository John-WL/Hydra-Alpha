// Author: John-William Lebel, 2021-04-18, creation

#ifndef SLOW_SLAVE_I2C_H
#define SLOW_SLAVE_I2C_H

#include "Vector.h"

#include "Arduino.h"

#include "QueueArray.h"

class SlowSlaveI2c
{
public:
    SlowSlaveI2c() = delete;
    static void init(uint8_t sdaPin, uint8_t sclPin, uint8_t chipAddress);
    static void update();
    static void onReceive(QueueArray<uint8_t>& receivedData);
    static void onRequest(QueueArray<uint8_t>& dataToSend);

private:
    // called when sda line changes
    static void _onSdaChange();

    // called when scl line rises
    static void (*_onSclSync)(void);
    // called when scl line falls
    static void (*_onSclFetch)(void);

    // returns true if sda and scl edges
    // correspond to a start bit
    static bool _gotStartBit();

    // returns true if sda and scl edges
    // correspond to a stop bit
    static bool _gotStopBit();

    static void _startAcknowledge();
    static void _stopAcknowledge();

    // states
    static void _idleState();

    static void _fetchAddressState();
    static void _readAddressState();

    static void _fetchReadDataState();
    static void _readDataState();

    static void _fetchWriteDataState();
    static void _writeDataState();

    // hardware access
    static void _sdaHigh();
    static void _sdaLow();
    static bool _sdaRead();
    static bool _sclRead();


    static uint8_t _chipAddress;
    static uint8_t _sdaPin;
    static uint8_t _sclPin;
    static bool _sdaCurrentState;
    static bool _sclCurrentState;
    static bool _sdaPreviousState;
    static bool _sclPreviousState;

    static uint8_t _receivedAddressSelect;
    static bool _receivingData;

    static bool _sendsAcknowledges;

    static uint8_t _bitCount;
    static uint8_t _readByte;
    static uint8_t _writeByte;
    static QueueArray<uint8_t> _readData;
    static QueueArray<uint8_t> _writeData;
};

#endif