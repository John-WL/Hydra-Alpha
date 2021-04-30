// Author: John-William Lebel, 2021-04-10, creation

#include "Arduino.h"

#include "BatteryVoltageSensor.h"

void BatteryVoltageSensor::init() {
    pinMode(BATTERY_ADC_PIN, INPUT);
}

void BatteryVoltageSensor::sample() {
    // read the battery level
    uint16_t batteryReading = analogRead(BATTERY_ADC_PIN);

    _batteryLevelPercentage = _batteryLevelPercentage*BATTERY_LOW_PASS_FILTER_COEFFICIENT
        + _convertAdcToUnfilteredPercentage(batteryReading) * (1-BATTERY_LOW_PASS_FILTER_COEFFICIENT);

    if(abs(_batteryLevelPercentage - _convertAdcToUnfilteredPercentage(batteryReading)) > 2)
    {
        _batteryLevelPercentage = _convertAdcToUnfilteredPercentage(batteryReading);
    }
    
    // A possible improvement would be to have a table of voltages that correspond to the percentage of battery remaining (the actual function of battery level
    // is not linear, but is actually a weird S-like shape. The voltage drops quickly at first, then stabilizes, and then starts to drop quickly again near the
    // end, as the true remaining battery percentage level drops linearily).
}

float BatteryVoltageSensor::getValue()
{
    return _batteryLevelPercentage;
}

float BatteryVoltageSensor::_convertAdcToUnfilteredPercentage(uint16_t adcValue)
{
    return (((adcValue - BATTERY_LOW_VLOTAGE_ADC_VALUE)/(BATTERY_HIGH_VLOTAGE_ADC_VALUE - BATTERY_LOW_VLOTAGE_ADC_VALUE)) * 100);
}

float BatteryVoltageSensor::_batteryLevelPercentage = 0;
