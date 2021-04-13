// Author: John-William Lebel, 2021-04-10, creation

#include "Arduino.h"

#include "BatteryVoltageSensor.h"

void BatteryVoltageSensor::init() {
    pinMode(BATTERY_ADC_PIN, INPUT);
}

void BatteryVoltageSensor::sample() {
    // read the battery level
    int batteryReading = analogRead(BATTERY_ADC_PIN);

    // simple low-pass filtering following the equation
    // Xn+1 = Xn*k + Qn*(1-k),
    // where:
    // Xn is the previous sensed battery percentage level;
    // Xn+1 is the new sensed battery percentage level;
    // Qn is the raw reading from the ADC, and it's wiggling a little bit (thus we're filtering it, obviously hehe);
    // k is the constant of low-pass filtering (1 means full filtering (filtering frequency = 0),
    // and 0 means no filtering at all (filtering frequency = infinity)).
    BatteryVoltageSensor::_batteryLevelPercentage = BatteryVoltageSensor::_batteryLevelPercentage*BATTERY_LOW_PASS_FILTER_COEFFICIENT +
        (batteryReading*(100 + BATTERY_PERCENTAGE_OFFSET)/4095.0 - BATTERY_PERCENTAGE_OFFSET)*(1-BATTERY_LOW_PASS_FILTER_COEFFICIENT);
    // another thing to note is that the ADC is not giving us directly the values in persentages (due to obvious hardware desing reasons),
    // and so we are actually doing, right before the filtering, a linear regression on Qn to make it yeild the desired range of values.
    // The resulting transformation is a simple percentage of remaining battery life, on which we are actually applying the low-pass.

    // if we're too far off the readings, this just means someone's varying that battery level a lot!
    // Make sure we have sticky readings.
    // So basically, to have sticky readings, you check the difference between your "raw" percentage and the filtered percentage.
    // If the difference is too great, you set the filtered percentage to the "raw" percentage.
    // This makes sure we never have a too big difference between the actual readings and our filtering.
    if(abs(BatteryVoltageSensor::_batteryLevelPercentage - (batteryReading*(100 + BATTERY_PERCENTAGE_OFFSET)/4095.0 - BATTERY_PERCENTAGE_OFFSET)) > 2) {
        BatteryVoltageSensor::_batteryLevelPercentage = (batteryReading*(100 + BATTERY_PERCENTAGE_OFFSET)/4095.0 - BATTERY_PERCENTAGE_OFFSET);
    }
    
    // A possible improvement would be to have a table of voltages that correspond to the percentage of battery remaining (the actual function of battery level
    // is not linear, but is actually a weird S-like shape. The voltage drops quickly at first, then stabilizes, and then starts to drop quickly again near the
    // end, as the true remaining battery percentage level drops linearily).
}

float BatteryVoltageSensor::getValue()
{
    return BatteryVoltageSensor::_batteryLevelPercentage;
}

float BatteryVoltageSensor::_batteryLevelPercentage = 0;
