// Author: John-William Lebel, 2021-04-10, creation

// This class implements the battery voltage level reading functionnality. 
// It uses an on-board ADC to estimate the current voltage level of the battery. 

#ifndef BATTERY_SENSOR_H
#define BATTERY_SENSOR_H

// battery readings settings
#define BATTERY_ADC_PIN                         36
#define BATTERY_PERCENTAGE_OFFSET               110
#define BATTERY_LOW_VLOTAGE_ADC_VALUE           (4096 * 0.63)
#define BATTERY_HIGH_VLOTAGE_ADC_VALUE          (4096 * 0.7736363636)

// actual value of this should be around pow(e, -cutoffFrequency / sampleRate)
#define BATTERY_LOW_PASS_FILTER_COEFFICIENT     0.995

class BatteryVoltageSensor
{
    public:
        static void init();
        static void sample();
        static float getValue();

    private:
        static float _convertAdcToUnfilteredPercentage(uint16_t adcValue);

        // Battery level variable.
        static float _batteryLevelPercentage;
};

#endif