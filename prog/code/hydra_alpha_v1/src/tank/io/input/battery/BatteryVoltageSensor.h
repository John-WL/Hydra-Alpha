// Author: John-William Lebel, 2021-04-10, creation

// This class implements the battery voltage level reading functionnality. 
// It uses an on-board ADC to estimate the current voltage level of the battery. 

#ifndef BATTERY_SENSOR_H
#define BATTERY_SENSOR_H

// battery readings settings
#define BATTERY_ADC_PIN                         36
#define BATTERY_PERCENTAGE_OFFSET               70.0

// actual value of this should be around pow(e, -cutoffFrequency / sampleRate)
#define BATTERY_LOW_PASS_FILTER_COEFFICIENT     0.95

class BatteryVoltageSensor
{
    public:
        static void init();
        static void sample();
        static float getValue();

    private:
        // Battery level variable.
        static float _batteryLevelPercentage;
};

#endif