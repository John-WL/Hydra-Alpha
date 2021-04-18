// Author: John-William Lebel, 2021-04-16, creation



// useful links...

// for face detection:
// https://techtutorialsx.com/2020/06/13/esp32-camera-face-detection/
// https://github.com/espressif/esp-face/tree/6a8b537b35d166637b3ea10790ccd89a007a2bb0/face_detection

// for basic camera sampling:
// https://github.com/espressif/esp32-camera/blob/master/driver/include/esp_camera.h
// https://github.com/espressif/esp32-camera/blob/master/driver/include/esp_camera.h#L120

// for playing with the camera settings:
// https://randomnerdtutorials.com/esp32-cam-ov2640-camera-settings/



#ifndef CAMERA_SENSOR_H
#define CAMERA_SENSOR_H

#include "esp_camera.h"
#include "fd_forward.h"

#include "Vector.h"

#include "../../utils/math/shape/Rectangle2.h"

#define CAMERA_MODEL_AI_THINKER

namespace EspCamRectanglesBakingStatus
{
    enum Enum
    {
        IDLE,
        PENDING,
        BAKED
    };
}

class CameraSensor
{
    public:
        static void init(void (*sendOverWiFiCallback)(std::vector<uint8_t>));
        static void update();

        static void enableSendingFramesOverWiFi(bool isSendingFramesOverWiFi);
        static void requestToBakeFaceRectangles();
        static void resetBakedFaceRectanglesStatus();

        static std::vector<Rectangle2> faceRectangles;
        static unsigned char rectanglesBakingStatus;

    private:
        static void _generateRectanglesFromFaceDetection(camera_fb_t* cameraFramebuffer);

        static bool _isSendingFramesOverWiFi;
        static void (*_sendOverWiFiCallback)(std::vector<uint8_t>);

        static mtmn_config_t _mtmnConfig;
};

#endif