// Author: John-William Lebel, 2021-04-16, creation

#include "CameraSensor.h"

#include "Arduino.h"

#include "esp_camera.h"
//#include "fd_forward.h"

#include "Vector.h"

#include "../../../shared/utils/math/shape/Rectangle2.h"

#include "../../../../config/camera_pins.h"
#include "color_detection/ColorDetection.h"

void CameraSensor::init(void (*sendOverWiFiCallback)(std::vector<uint8_t>))
{
    // save the callback
    _sendOverWiFiCallback = sendOverWiFiCallback;

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
    config.pixel_format = PIXFORMAT_RGB565;

    // frame size is 320x240 frame size,
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

    // more camera settings
    sensor_t* s = esp_camera_sensor_get();
    
    if (s->id.PID == OV3660_PID)
    {
        s->set_vflip(s, 1);         // flip it back (back?)
        s->set_brightness(s, 1);    // up the brightness just a bit
        s->set_saturation(s, -2);   // lower the saturation
    }

    // setting specific to the M5-Stack Wide model
    #if defined(CAMERA_MODEL_M5STACK_WIDE)
    s->set_vflip(s, 1);
    s->set_hmirror(s, 1);
    #endif

    _mtmnConfig = mtmn_init_config();
}

void CameraSensor::update()
{
    // if we don't need to query the camera image, 
    // then don't query it for no reason
    if(!_isSendingFramesOverWiFi && (rectanglesBakingStatus != EspCamRectanglesBakingStatus::PENDING))
    {
        return;
    }

    // camera frame buffer
    camera_fb_t* cameraFrameBuffer = esp_camera_fb_get();

    // Bake rectangles!
    if(rectanglesBakingStatus == EspCamRectanglesBakingStatus::PENDING)
    {
        faceRectangles.clear();

        // Hmm... Smells good.
        _generateRectanglesFromFaceDetection(cameraFrameBuffer);
        _generateRectanglesFromColorDetection(cameraFrameBuffer);
    }

    // send over WiFi the way you want, I don't care anymore
    if(_isSendingFramesOverWiFi)
    {
        // convert 565 to JPEG
        uint8_t** jpegBuffer;
        size_t* jpegLength;
        fmt2jpg(
            cameraFrameBuffer->buf,
            cameraFrameBuffer->len,
            cameraFrameBuffer->width,
            cameraFrameBuffer->height,
            cameraFrameBuffer->format,
            DESIRED_JPEG_QUALITY,
            jpegBuffer,
            jpegLength
        );

        // convert the data array to a vector<uint8_t>
        std::vector<uint8_t> cameraFramebufferVector{};
        cameraFramebufferVector.insert(
            cameraFramebufferVector.end(),
            *jpegBuffer,
            &((*jpegBuffer)[*jpegLength])
        );

        _sendOverWiFiCallback(cameraFramebufferVector);

        // we need to free the pointers after use
        free(jpegBuffer);
        free(jpegLength);
    }

    // return the frame buffer to be reused
    esp_camera_fb_return(cameraFrameBuffer);
}

void CameraSensor::_generateRectanglesFromFaceDetection(camera_fb_t* cameraFrameBuffer)
{
    dl_matrix3du_t* image_matrix = dl_matrix3du_alloc(1, cameraFrameBuffer->width, cameraFrameBuffer->height, 3);
    fmt2rgb888(cameraFrameBuffer->buf, cameraFrameBuffer->len, cameraFrameBuffer->format, image_matrix->item);
    
    box_array_t* boxes = face_detect(image_matrix, &_mtmnConfig);

    if(boxes != NULL)
    {

        for(int i = 0; i < boxes->len; i++)
        {
            box_t* faceBox = boxes[i].box;
            Vector2 upperLeft{faceBox->box_p[0], faceBox->box_p[1]};
            Vector2 lowerRight{faceBox->box_p[2], faceBox->box_p[3]};
            Rectangle2 faceLocation{upperLeft, lowerRight};
            faceRectangles.push_back(faceLocation);
        }

        rectanglesBakingStatus = EspCamRectanglesBakingStatus::BAKED;
        
        // gives an error?
        /*
        dl_lib_free(boxes->score);
        dl_lib_free(boxes->box);
        dl_lib_free(boxes->landmark);
        dl_lib_free(boxes);
        */
        free(boxes->score);
        free(boxes->box);
        free(boxes->landmark);
        free(boxes);
    }
    
    dl_matrix3du_free(image_matrix);
}

void CameraSensor::_generateRectanglesFromColorDetection(camera_fb_t* cameraFrameBuffer)
{
    std::vector<Rectangle2> generatedRectangle = ColorDetection::generateRectanglesFrom565Buffer(
        (unsigned int*)cameraFrameBuffer->buf,
        cameraFrameBuffer->width,
        cameraFrameBuffer->height
    );

    if(generatedRectangle.size() == 0)
    {
        return;
    }

    faceRectangles.push_back(generatedRectangle[0]);
}

void CameraSensor::requestToBakeFaceRectangles()
{
    if(rectanglesBakingStatus == EspCamRectanglesBakingStatus::IDLE)
    {
        rectanglesBakingStatus = EspCamRectanglesBakingStatus::PENDING;
    }
}

void CameraSensor::resetBakedFaceRectanglesStatus()
{
    if(rectanglesBakingStatus == EspCamRectanglesBakingStatus::BAKED)
    {
        rectanglesBakingStatus = EspCamRectanglesBakingStatus::IDLE;
    }
}

std::vector<Rectangle2> CameraSensor::faceRectangles;

bool CameraSensor::_isSendingFramesOverWiFi{false};
unsigned char CameraSensor::rectanglesBakingStatus{0};
void (*CameraSensor::_sendOverWiFiCallback)(std::vector<uint8_t>) = [](std::vector<uint8_t> cameraFrameBuffer){};

mtmn_config_t CameraSensor::_mtmnConfig{0};