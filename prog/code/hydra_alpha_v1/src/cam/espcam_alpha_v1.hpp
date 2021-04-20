// Author: John-William Lebel, 2021-04-08, creation

#include "Arduino.h"

#include "QueueArray.h"
#include "Vector.h"

//#include "esp_camera.h"

#include "../shared/core/Esp32DualCore.h"

//#include "src/peripheral/camera_sensor/CameraSensor.h"
//#include "src/peripheral/wifi_client_hydra/WiFiClientHydra.h"
//#include "src/peripheral/tank_alpha/TankAlpha.h"

#include "core/slow_slave_i2c/SlowSlaveI2c.h"
#include "core/slow_master_i2c/SlowMasterI2c.h"
//#include "Wire.h"

#include "core/clock_stretch_test/ClockStretchTest3.hpp"

void SlowSlaveI2c::onReceive(QueueArray<uint8_t>& data)
{
    Serial.print("Slave received ");
    Serial.print(data.count());
    Serial.println(" byte(s).");

    while(data.count())
    {
        uint8_t byte = data.pop();
        Serial.println(byte);
    }
}

void SlowSlaveI2c::onRequest(QueueArray<uint8_t>& data)
{
    data.push(5);
    data.push(18);
    data.push(34);
    data.push(48);
    data.push(165);
    data.push(238);
    data.push(165);
    data.push(238);
    data.push(165);
    data.push(238);
    data.push(165);
    data.push(238);
    data.push(165);
    data.push(238);

    Serial.print("Transmitting ");
    Serial.print(data.count());
    Serial.println(" byte(s)...");
}

void setup()
{
    Serial.begin(SERIAL_COMMUNICATION_SPEED);
    //Serial.setDebugOutput(true);

    // put your WiFi sender implementation in the brackets
    //WiFiClientHydra::init();
    //CameraSensor::init(WiFiClientHydra::sendDataToRemote);
    //TankAlpha::init();



    /*Serial.println("Initializing hard master I2C...\n");
    Wire.begin();
    delay(1000);
    Serial.println("Initialized.\n\n");*/

    Esp32DualCore::init();

    //Serial.println("Initializing soft master I2C...\n");
    //SlowMasterI2c::init(26, 25);
    //delay(1000);
    //Serial.println("Initialized.\n\n");

    //Serial.println("Initializing soft slave I2C...\n");
    //SlowSlaveI2c::init(76, 33, 32);
    //delay(1000);
    //Serial.println("Initialized.\n\n");

    ClockStretchTest3::init(25, 32);
}

void loop()
{
    //CameraSensor::update();
    //SlowSlaveI2c::update();
    //ClockStretchTest3::updateSlave();
}

void Esp32DualCore::main()
{
    while(true)
    {
        //ClockStretchTest3::updateMaster();
        pinMode(25, OUTPUT);
        if(digitalRead(25))
        {}
        pinMode(25, INPUT);
    }
}

