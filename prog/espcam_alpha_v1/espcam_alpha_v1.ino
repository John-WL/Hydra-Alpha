// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "src/core/Esp32DualCore.h"

#include "src/utils/timer/TimerMicros.h"

#include "esp_camera.h"

#define CAMERA_DESIRED_FPS 10
#define CAMERA_DESIRED_REFRESH_PERIOD (1 / CAMERA_DESIRED_FPS)
#define CAMERA_DESIRED_REFRESH_PERIOD_MICROSECONDS (1000000 * CAMERA_DESIRED_REFRESH_PERIOD)

TimerMicros cameraShotTimer{CAMERA_DESIRED_REFRESH_PERIOD_MICROSECONDS, handlerCameraFrame};

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println();

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
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
    
    // initialize with high specs to pre-allocate larger buffers

    // here, my guess is that if we don't have a lot of memory, 
    // we allocate a less memory consuming JPEG format?
    if(psramFound())
    {
        config.frame_size = FRAMESIZE_UXGA;
        config.jpeg_quality = 10;
        config.fb_count = 2;
    }
    else
    {
        config.frame_size = FRAMESIZE_SVGA;
        config.jpeg_quality = 12;
        config.fb_count = 1;
    }

    #if defined(CAMERA_MODEL_ESP_EYE)
    pinMode(13, INPUT_PULLUP);
    pinMode(14, INPUT_PULLUP);
    #endif

    // camera initialization
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }



    // That's the camera object to take pictures?
    // What are its methods, what the hell can we do with it?????
    // How do we use it???

    // update: no. That's for gathering sensor info, and nobody cares about that,
    // unless you want to modify the settings of the senor, which we are doing right below, dumass.  
    sensor_t* s = esp_camera_sensor_get();



    // Initial sensors are flipped vertically and colors are a bit saturated.
    // That looks like some sort of configuration that depends on the camera 
    // module.
    if (s->id.PID == OV3660_PID)
    {
        s->set_vflip(s, 1);//flip it back
        s->set_brightness(s, 1);//up the blightness just a bit
        s->set_saturation(s, -2);//lower the saturation
    }
    
    // Drop down frame size for higher initial frame rate.
    // WHY do we need to do that????
    // Is it a fix for the WiFi ONLY,
    // OR is it a UNIVERSAL fix? Does it brake down if we don't use that?????
    // Is it only for visibility of frames on the web??????

    // update: we probably don't need to do that indeed. 
    s->set_framesize(s, FRAMESIZE_QVGA);

    // looks like we've got some more settings for a board we're not even using

    // this is the case, yes.
    #if defined(CAMERA_MODEL_M5STACK_WIDE)
    s->set_vflip(s, 1);
    s->set_hmirror(s, 1);
    #endif

    // Alright, and here is the part we mainly want to focus on. 
    /*
        // Alright, begin wifi, that's an easy one...
        WiFi.begin(ssid, password);

        // Loop until we're connected...
        while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        }
        Serial.println("");
        Serial.println("WiFi connected");

        // Start the main program? 
        // Does it run on interrupts?
        // On callbacks?
        // Who tells the cpu "hey wake up, we got a WiFi request, send your data"???
        startCameraServer();

        // some more debug info, nobody cares
        Serial.print("Camera Ready! Use 'http://");
        Serial.print(WiFi.localIP());
        Serial.println("' to connect");
    */

    // That's what I'd replace all of the above with:
    cameraShotTimer.start();
}

void loop()
{
    cameraShotTimer.update();
}

void Esp32DualCore::main()
{
    while(true)
    {
        
    }
}