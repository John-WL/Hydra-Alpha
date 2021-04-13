#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
Adafruit_BNO055 bno055 = Adafruit_BNO055(55, 0x29);
char hasBno055InitializedCorrectly = 0;
 
void setup(void) {
    Serial.begin(9600);
    
    // Initialise the sensor
    hasBno055InitializedCorrectly = bno055.begin();
    delay(1000);
    bno055.setExtCrystalUse(true);
}
 
void loop(void) {
    if(!hasBno055InitializedCorrectly) {
        while(true) {
            Serial.println("Bno055 couldn't initialize");
        }
    }
    
    // Get the bno055 event
    sensors_event_t bno055Event;
    bno055.getEvent(&bno055Event);
    
    // log imu data
    Serial.print("X: ");
    Serial.print(bno055Event.orientation.x, 7);
    Serial.print("\tY: ");
    Serial.print(bno055Event.orientation.y, 7);
    Serial.print("\tZ: ");
    Serial.print(bno055Event.orientation.z, 7);
    Serial.println("");
}
