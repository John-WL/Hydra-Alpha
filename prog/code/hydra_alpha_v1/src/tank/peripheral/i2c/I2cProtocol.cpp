// Author: John-William Lebel, 2021-04-11, creation

#include "I2cProtocol.h"

#include "Wire.h"

#include "Vector.h"

#include "../../../shared/utils/timer/TimerMicros.h"

void I2cProtocol::transmit(unsigned char deviceAddress, std::vector<unsigned char> data)
{
    Wire.beginTransmission((deviceAddress >> 1) & ~0x01);
    for(std::vector<unsigned char>::iterator dataIterator = data.begin(); dataIterator < data.end(); dataIterator++)
    {
        Wire.write(*dataIterator);
    }
    Wire.endTransmission();
}

std::vector<unsigned char> I2cProtocol::receive(unsigned char deviceAddress, unsigned char dataLengthRequest)
{
    // receiving array
    std::vector<unsigned char> dataReceived{};

    // request data
    Wire.requestFrom(deviceAddress, dataLengthRequest);

    // reset the transmission state
    _receptionDone = false;

    // This timer ends the reception
    // if we reached the max timeout.
    // We still return the bytes we
    // were able to receive, even if
    // the timeout was reached.
    _receptionTimeoutTimer.start();

    // stay here until we receive all the bytes or 
    // reach the timeout limit
    while(!_receptionDone)
    {
        // if we received a byte
        if(Wire.available())
        {
            // assign the received byte to the next array index
            dataReceived.push_back(Wire.read());
        }

        // have we received all the bytes?
        _receptionDone = dataReceived.size() >= dataLengthRequest;
        // did we reach the timeout limit?
        _receptionTimeoutTimer.update();
    }

    return dataReceived;
}

void I2cProtocol::_endReception()
{
    _receptionDone = true;
}

bool I2cProtocol::_receptionDone = true;

TimerMicros I2cProtocol::_receptionTimeoutTimer
{
    I2C_RECEIVE_TIMEOUT_MICROSECONDS,
    []()
    {
        I2cProtocol::_endReception();
        Serial.println("I2C reception took too long!");
        Serial.println("Data was chopped in half...");
    }
};