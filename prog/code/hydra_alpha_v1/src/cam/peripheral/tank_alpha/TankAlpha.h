// Author: John-William Lebel, 2021-04-17, creation

#ifndef TANK_ALPHA_H
#define TANK_ALPHA_H

#define SLOW_I2C_SLAVE_ADDRESS 0x24
#define SLOW_SDA_PIN 3
#define SLOW_SCL_PIN 1

#include "QueueArray.h"

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
    static void update();
    static void onReceive(QueueArray<uint8_t>& dataReceived);
    static void onRequest(QueueArray<uint8_t>& dataRequested);

private:
    static bool _enableSendingCameraFrameOverWiFi;
    static unsigned char _lastReceivedCommandId;

};

#endif