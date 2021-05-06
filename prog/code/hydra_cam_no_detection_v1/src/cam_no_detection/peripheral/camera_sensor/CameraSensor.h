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

#define DESIRED_JPEG_QUALITY 8

#include "esp_camera.h"
#include "fd_forward.h"

#include "Vector.h"

#define CAMERA_MODEL_AI_THINKER

class CameraSensor
{
public:
    static void init(void (*wiFiCallback)(std::vector<uint8_t> data));
    static void update();
    static void enableSendingFramesOverWiFi(bool isSendingFramesOverWiFi);

private:
    static void (*_wiFiCallback)(std::vector<uint8_t>);
    static bool _isSendingFramesOverWiFi;
    static mtmn_config_t _mtmnConfig;
    
};

#endif