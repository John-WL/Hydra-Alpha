// Author: John-William Lebel, 2021-04-17, creation


#include "TankAlpha.h"

#include "QueueArray.h"

#include "../camera_sensor/CameraSensor.h"

#include "../../../shared/utils/math/shape/Rectangle2.h"
#include "../../../shared/utils/math/vector/Vector2.h"

#include "../../../shared/peripheral/slow_i2c/slow_slave_i2c/SlowSlaveI2c.h"

void TankAlpha::init()
{
    SlowSlaveI2c::init(
        SLOW_SDA_PIN,
        SLOW_SCL_PIN,
        SLOW_I2C_SLAVE_ADDRESS
    );
}

void TankAlpha::update()
{
    SlowSlaveI2c::update();
}

void SlowSlaveI2c::onReceive(QueueArray<uint8_t>& dataReceived)
{
    TankAlpha::onReceive(dataReceived);
}

void SlowSlaveI2c::onRequest(QueueArray<uint8_t>& dataRequested)
{
    TankAlpha::onRequest(dataRequested);
}

void TankAlpha::onReceive(QueueArray<uint8_t>& dataReceived)
{
    if(!dataReceived.count())
    {
        return;
    }

    // make sure to remember what the last command id was
    _lastReceivedCommandId = dataReceived.pop();
    switch(_lastReceivedCommandId)
    {
        case TankAlphaCommands::ENABLE_DISABLE_SENDING_CAMERA_FRAME_OVER_WI_FI:
            // check if the master forgot a byte...
            if(!dataReceived.count())
            {
                return;
            }
            // update the boolean to enable/disable WiFi camera transmission
            _enableSendingCameraFrameOverWiFi = dataReceived.pop() & 0x80;
            break;
        case TankAlphaCommands::SEND_BACK_RECTANGLES_BAKING_STATUS:
            // Nothing to do.
            // We are expecting a request in a short time.
            // We're gonna handle this mode in the request
            // function the next time the master sends a request.
            break;
        case TankAlphaCommands::REQUEST_BAKING_RECTANGLES:
            // request to bake rectangles
            CameraSensor::requestToBakeFaceRectangles();
            break;
        case TankAlphaCommands::SEND_BACK_BACKED_RECTANGLES:
            // Nothing to do.
            // We are expecting a request in a short time.
            // We're gonna handle this mode in the request
            // function the next time the master sends a request.
            break;
        default:
            break;
    }
}

void TankAlpha::onRequest(QueueArray<uint8_t>& dataRequested)
{
    switch(_lastReceivedCommandId)
    {
        case TankAlphaCommands::ENABLE_DISABLE_SENDING_CAMERA_FRAME_OVER_WI_FI:
            // everything was handled in the _receiveEvent() function
            break;
        case TankAlphaCommands::SEND_BACK_RECTANGLES_BAKING_STATUS:
            // send rectangle baking status
            dataRequested.push(CameraSensor::rectanglesBakingStatus);
            break;
        case TankAlphaCommands::REQUEST_BAKING_RECTANGLES:
            // everything was handled in the _receiveEvent() function
            break;
        case TankAlphaCommands::SEND_BACK_BACKED_RECTANGLES:
            // check if we found any rectangles
            if(CameraSensor::faceRectangles.size() == 0)
            {
                // write back 7 zeros
                for(uint8_t i = 0; i < 7; i++)
                {
                    dataRequested.push(0);
                }
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
            break;
    }
}

bool TankAlpha::_enableSendingCameraFrameOverWiFi{false};

unsigned char TankAlpha::_lastReceivedCommandId{0};