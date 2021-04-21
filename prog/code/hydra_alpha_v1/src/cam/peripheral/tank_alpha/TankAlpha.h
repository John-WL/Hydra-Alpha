// Author: John-William Lebel, 2021-04-17, creation

#ifndef TANK_ALPHA_H
#define TANK_ALPHA_H

#define SLOW_SDA_PIN 3
#define SLOW_SCL_PIN 1

namespace TankAlphaCommands
{
    enum Enum
    {
        ENABLE_DISABLE_SENDING_CAMERA_FRAME_OVER_WI_FI  = 0x00,
        SEND_BACK_RECTANGLES_BAKING_STATUS              = 0x01,
        REQUEST_BAKING_RECTANGLES                       = 0x02,
        SEND_BACK_BACKED_RECTANGLES                     = 0x03
    };
}

class TankAlpha
{
public:
    static void init();

    static bool enableSendingCameraFrameOverWiFi;
    static unsigned char lastReceivedCommandId;

private:
    static void _receiveEvent();
    static void _requestEvent();

};

#endif