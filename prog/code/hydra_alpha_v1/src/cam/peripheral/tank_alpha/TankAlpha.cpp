// Author: John-William Lebel, 2021-04-17, creation

/*
#include "TankAlpha.h"

#include "../camera_sensor/CameraSensor.h"

#include "../../utils/math/shape/Rectangle2.h"
#include "../../utils/math/vector/Vector2.h"

#include "Wire.h"

void TankAlpha::init()
{
    Wire.begin(0x24);
    Wire.onReceive(_receiveEvent);
    Wire.onRequest(_requestEvent);
}

void TankAlpha::_receiveEvent(int dataLength)
{
    if(!Wire.available())
    {
        return;
    }

    // make sure to remember what the last command id was
    _lastReceivedCommandId = Wire.read();
    switch(_lastReceivedCommandId)
    {
        case TankAlphaCommands::ENABLE_DISABLE_SENDING_CAMERA_FRAME_OVER_WI_FI:
            // check if the master forgot a byte...
            if(Wire.available() < 1)
            {
                return;
            }
            // update the boolean to enable/disable WiFi camera transmission
            enableSendingCameraFrameOverWiFi = Wire.read() & 0x80;
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
    _wireFlush();   // empty the remainning bytes (if there are any)
}

void TankAlpha::_requestEvent()
{
    switch(_lastReceivedCommandId)
    {
        case TankAlphaCommands::ENABLE_DISABLE_SENDING_CAMERA_FRAME_OVER_WI_FI:
            // everything was handled in the _receiveEvent() function
            break;
        case TankAlphaCommands::SEND_BACK_RECTANGLES_BAKING_STATUS:
            // send rectangle baking status
            Wire.write(CameraSensor::rectanglesBakingStatus);
            break;
        case TankAlphaCommands::REQUEST_BAKING_RECTANGLES:
            // everything was handled in the _receiveEvent() function
            break;
        case TankAlphaCommands::SEND_BACK_BACKED_RECTANGLES:
            // check if we found any rectangles
            if(CameraSensor::faceRectangles.size() == 0)
            {
                unsigned char returnData[7] = {0, 0, 0, 0, 0, 0, 0};
                Wire.write(returnData, 7);
                break;
            }
            // send the 4 coordinates of the rectangle most likely to be the one we are looking for
            Rectangle2 rectangleFound = CameraSensor::faceRectangles[0];
            int x1 = rectangleFound.upperLeft.x;
            int y1 = rectangleFound.upperLeft.y;
            int x2 = rectangleFound.lowerRight.x;
            int y2 = rectangleFound.lowerRight.y;

            int v1 = (unsigned char)x1;
            unsigned char returnData[7] = 
            {
                0x80,
                (unsigned char)x1,
                ((unsigned char)((x1 >> 8) & 0x0F)) | ((unsigned char)((y1 << 4) & 0xF0)),
                (unsigned char)(y1 >> 4),
                (unsigned char)x2,
                ((unsigned char)((x2 >> 8) & 0x0F)) | ((unsigned char)((y2 << 4) & 0xF0)),
                (unsigned char)(y2 >> 4)
            };
            Wire.write(returnData, 7);
            break;
    }
}

void TankAlpha::_wireFlush()
{
    while(Wire.available())
    {
        Wire.read();
    }
}

bool TankAlpha::enableSendingCameraFrameOverWiFi{false};

unsigned char TankAlpha::_lastReceivedCommandId{0};*/