// Author: John-William Lebel, 2021-04-16, creation

#include "CameraSensor.h"

#include "Arduino.h"

#include "esp_camera.h"

#include "camera_pins.h"

#include "Vector.h"

void CameraSensor::init(void (*wiFiCallback)(std::vector<uint8_t>))
{
    _wiFiCallback = wiFiCallback;

    // camera settings
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 10000000;
    config.pixel_format = PIXFORMAT_JPEG;
    //config.pixel_format = PIXFORMAT_RGB565;

    // frame size is 320x240,
    // what we need for the lcd, and
    // optimal for face detection!
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = DESIRED_JPEG_QUALITY;
    config.fb_count = 2;

    // checking for errors when initializing
    esp_err_t errorId = esp_camera_init(&config);
    if(errorId != ESP_OK)
    {
        Serial.print("Camera init failed with error #");
        Serial.print(errorId);
        Serial.println(".");
        return;
    }

    _mtmnConfig = mtmn_init_config();
}

void CameraSensor::update()
{
    // if we don't need to query the camera image, 
    // then don't query it for no reason
    if(!_isSendingFramesOverWiFi)
    {
        return;
    }

    // camera frame buffer
    camera_fb_t* cameraFrameBuffer = esp_camera_fb_get();

    // convert the data array to a vector<uint8_t>
    std::vector<uint8_t> cameraFramebufferVector
    {
        cameraFrameBuffer->buf,
        cameraFrameBuffer->buf + cameraFrameBuffer->len
    };

    // send over WiFi
    _wiFiCallback(cameraFramebufferVector);

    // return the frame buffer to be reused
    esp_camera_fb_return(cameraFrameBuffer);
}

void CameraSensor::enableSendingFramesOverWiFi(bool sendingOverWiFi)
{
    _isSendingFramesOverWiFi = sendingOverWiFi;
}

void (*CameraSensor::_wiFiCallback)(std::vector<uint8_t>){};
bool CameraSensor::_isSendingFramesOverWiFi{true};
mtmn_config_t CameraSensor::_mtmnConfig{0};