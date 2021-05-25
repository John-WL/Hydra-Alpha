// Author: John-William Lebel, 2021-04-17, creation

#include "Tank.h"

#include "QueueArray.h"
#include "Vector.h"

#include "../camera_sensor/CameraSensor.h"

#include "../../../shared/utils/math/shape/Rectangle2.h"
#include "../../../shared/utils/math/vector/Vector2.h"

#include "../../../shared/peripheral/spare_serial/SerialSlave.h"

void Tank::init()
{
    SerialSlave::begin(115200);
}

void Tank::update()
{
    // empty the array
    while(dataReceivedArray.count() > 0)
    {
        dataReceivedArray.pop();
    }

    // get data (if any)
    std::vector<uint8_t> dataReceivedVector = SerialSlave::receive(2);

    // check if we have data
    if(dataReceivedVector.size() > 0)
    {
        // fill in the queue
        while(dataReceivedArray.count() < dataReceivedVector.size())
        {
            uint8_t currentArrayLength = dataReceivedArray.count();
            uint8_t valueToPushInArray = dataReceivedVector[currentArrayLength];
            dataReceivedArray.push(valueToPushInArray);
        }

        digitalWrite(33, HIGH);

        // receive
        onReceive(dataReceivedArray);
    }
}

void Tank::onReceive(QueueArray<uint8_t>& dataReceived)
{
    if(!dataReceived.count())
    {
        return;
    }

    // make sure to remember what the last command id was
    _lastReceivedCommandId = dataReceived.pop();

    CameraSensor::enableSendingFramesOverWiFi(_lastReceivedCommandId & 0xF0);

    switch(_lastReceivedCommandId)
    {
        case TankCommands::ENABLE_DISABLE_SENDING_CAMERA_FRAME_OVER_WI_FI:
            // check if the master forgot a byte...
            if(!dataReceived.count())
            {
                return;
            }
            // update the boolean to enable/disable WiFi camera transmission
            CameraSensor::enableSendingFramesOverWiFi(dataReceived.pop() & 0x80);
            break;
        case TankCommands::SEND_BACK_RECTANGLES_BAKING_STATUS:
            // Nothing to do.
            // We are expecting a request in a short time.
            // We're gonna handle this mode in the request
            // function the next time the master sends a request.
            break;
        case TankCommands::REQUEST_BAKING_RECTANGLES:
            // request to bake rectangles
            CameraSensor::requestToBakeFaceRectangles();
            break;
        case TankCommands::SEND_BACK_BACKED_RECTANGLES:
            // Nothing to do.
            // We are expecting a request in a short time.
            // We're gonna handle this mode in the request
            // function the next time the master sends a request.
            break;
        default:
            break;
    }

    // request by hand because we're using serial instead of I2C
    onRequest(dataReceived);
}

void Tank::onRequest(QueueArray<uint8_t>& dataRequested)
{
    std::vector<uint8_t> dataRequestedVector{};

    switch(_lastReceivedCommandId)
    {
        case TankCommands::ENABLE_DISABLE_SENDING_CAMERA_FRAME_OVER_WI_FI:
            // everything was handled in the onReceive() function
            break;
        case TankCommands::SEND_BACK_RECTANGLES_BAKING_STATUS:
            // send rectangle baking status
            dataRequestedVector.push_back(CameraSensor::rectanglesBakingStatus);
            SerialSlave::send(dataRequestedVector);
            break;
        case TankCommands::REQUEST_BAKING_RECTANGLES:
            // everything was handled in the onReceive() function
            break;
        case TankCommands::SEND_BACK_BACKED_RECTANGLES:
            // check if we found any rectangles
            if(CameraSensor::faceRectangles.size() == 0)
            {
                // write back 1 zero
                dataRequestedVector.push_back(0);
                SerialSlave::send(dataRequestedVector);
                break;
            }
            // send the 4 coordinates of the rectangle most likely to be the one we are looking for
            Rectangle2 rectangleFound = CameraSensor::faceRectangles[0];
            int x1 = rectangleFound.upperLeft.x;
            int y1 = rectangleFound.upperLeft.y;
            int x2 = rectangleFound.lowerRight.x;
            int y2 = rectangleFound.lowerRight.y;
            
            dataRequested.push(0x80);
            dataRequested.push((unsigned char)x1);
            dataRequested.push(((unsigned char)((x1 >> 8) & 0x0F)) | ((unsigned char)((y1 << 4) & 0xF0)));
            dataRequested.push((unsigned char)(y1 >> 4));
            dataRequested.push((unsigned char)x2);
            dataRequested.push(((unsigned char)((x2 >> 8) & 0x0F)) | ((unsigned char)((y2 << 4) & 0xF0)));
            dataRequested.push((unsigned char)(y2 >> 4));

            while(dataRequested.count() > 0)
            {
                dataRequestedVector.push_back(dataRequested.pop());
            }

            SerialSlave::send(dataRequestedVector);
            break;
    }
}

unsigned char Tank::_lastReceivedCommandId{0};
QueueArray<uint8_t> Tank::dataReceivedArray{};