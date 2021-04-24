// Author: John-William Lebel, 2021-04-15, creation

#ifndef ESP_CAM_MASTER_H
#define ESP_CAM_MASTER_H

#include "../../../../shared/utils/math/shape/Rectangle2.h"

#define I2C_ESP_CAM_SLAVE_ADDRESS 0x24

// SOLDERED BY HAND ON THE BOARD!!!!!!
// ALSO, WATCH THE I2C CONNECTOR OF THE ESPCAM.
// WE DO NOT SOLDER THE SDA AND SCL OF THE ESPCAM ON THE BOARD
// WITH THE CONNECTOR. THIS PORT IS UNUSABLE BY THE ESPCAM IN
// ITS CURRENT CONFIGURATION. WE NEED TO SOLDER WIRES DIRECTLY. 
#define I2C_ESP_CAM_SDA 17
#define I2C_ESP_CAM_SCL 16

#define ESP_CAM_HARDWARE_RESET_PIN 32

#define ESP_CAM_RECTANGLE_IDLE_GENERATION_STATUS 0
#define ESP_CAM_RECTANGLE_PENDING_GENERATION_STATUS 1
#define ESP_CAM_RECTANGLE_BAKED_GENERATION_STATUS 2
#define ESP_CAM_RECTANGLE_INVALID_GENERATION_STATUS 3

#define ESP_CAM_OK_WIFI_STATUS 0
#define ESP_CAM_SEARCHING_WIFI_STATUS 1

class EspCam
{
public:
    static void init();
    static void update();
    static void enableSendingImagesOverWifi(bool isSendingImagesOverWiFi);

    static Rectangle2* rectangleOfTankOmegaInFrame;

private:
    static void _updateRectangleRequest();
    static void _updateWiFiCameraRequest();

    static void _requestHandlingOfSendingImagesOverWiFi(bool isSendingData);
    static unsigned char _requestStatusOfRectangleGeneration();
    static void _requestGenerationOfRectangle();
    static Rectangle2* _requestRectangleOfTankOmegaInFrame();


    static bool _isSendingImagesOverWiFi;
    static bool _wasSendingImagesOverWiFi;

};

#endif