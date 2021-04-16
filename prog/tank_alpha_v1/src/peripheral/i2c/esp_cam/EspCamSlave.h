// Author: John-William Lebel, 2021-04-15, creation

#ifndef ESP_CAM_MASTER_H
#define ESP_CAM_MASTER_H

#include "../../../utils/math/shape/Rectangle2.h"
#include "../general_device/I2cDevice.h"

#define I2C_ESP_CAM_SLAVE_ADDRESS 0x24

#define ESP_CAM_HARDWARE_RESET_PIN 32

#define ESP_CAM_RECTANGLE_IDLE_GENERATION_STATUS 0
#define ESP_CAM_RECTANGLE_PENDING_GENERATION_STATUS 1
#define ESP_CAM_RECTANGLE_BAKED_GENERATION_STATUS 2
#define ESP_CAM_RECTANGLE_INVALID_GENERATION_STATUS 3

#define ESP_CAM_OK_WIFI_STATUS 0
#define ESP_CAM_SEARCHING_WIFI_STATUS 1
#define ESP_CAM_FAILURE_WIFI_STATUS 2

class EspCamSlave
{
    public:
        static void init();
        static void update();
        static void enableSendingImagesOverWifi(bool isSendingImagesOverWiFi);

        static Rectangle2* rectangleOfTankOmegaInFrame;

    private:
        static void _updateRectangleRequest();
        static void _updateWiFiCameraRequest();
        static void _hardReset();

        static void _requestHandlingOfSendingImagesOverWiFi(bool isSendingData);
        static unsigned char _requestStatusOfRectangleGeneration();
        static void _requestGenerationOfRectangle();
        static Rectangle2* _requestRectangleOfTankOmegaInFrame();


        static bool _isSendingImagesOverWiFi;
        static bool _wasSendingImagesOverWiFi;

        static I2cDevice _i2cDevice;

};

#endif