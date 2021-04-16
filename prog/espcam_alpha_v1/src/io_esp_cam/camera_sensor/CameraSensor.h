// Author: John-William Lebel, 2021-04-16, creation

#ifndef CAMERA_SENSOR_H
#define CAMERA_SENSOR_H

// useful links...

// for face detection:
// https://techtutorialsx.com/2020/06/13/esp32-camera-face-detection/
// https://github.com/espressif/esp-face/tree/6a8b537b35d166637b3ea10790ccd89a007a2bb0/face_detection

// for basic camera sampling:
// https://github.com/espressif/esp32-camera/blob/master/driver/include/esp_camera.h

// for playing with the camera settings:
// https://randomnerdtutorials.com/esp32-cam-ov2640-camera-settings/

#include "esp_camera.h"
#include "fd_forward.h"

#include "Vector.h"

#include "../../utils/math/shape/Rectangle2.h"

#define CAMERA_MODEL_AI_THINKER

#define ESP_CAM_IDLE_RECTANGLES_BAKING_STATUS 0
#define ESP_CAM_PENDING_RECTANGLES_BAKING_STATUS 1
#define ESP_CAM_BAKED_RECTANGLES_BAKING_STATUS 2
#define ESP_CAM_INVALID_RECTANGLES_BAKING_STATUS 3

class CameraSensor
{
    public:
        static void init(void (*sendOverWiFiCallback)(camera_fb_t*));
        static void update();

        static void enableSendingFramesOverWiFi(bool isSendingFramesOverWiFi);
        static void requestToBakeFaceRectangles();
        static void resetBakedFaceRectanglesStatus();

        static std::vector<Rectangle2> faceRectangles;

    private:
        static void _generateRectanglesFromFaceDetection(camera_fb_t* cameraFramebuffer);

        static bool _isSendingFramesOverWiFi;
        static unsigned char _rectanglesBakingStatus;
        static void (*_sendOverWiFiCallback)(camera_fb_t*);

        static mtmn_config_t _mtmnConfig;
};

#endif