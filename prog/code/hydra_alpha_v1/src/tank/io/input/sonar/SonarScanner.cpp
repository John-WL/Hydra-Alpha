#include "SonarScanner.h"

#include "Arduino.h"

#include "SonarSample.h"

#include "Sonar.h"

#include "../../../../shared/utils/data_structure/CircularBuffer.h"

#include "../../output/Outputs.h"

void SonarScanner::init()
{
    Sonar::init(SonarScanner::_addDataPoint);
}

void SonarScanner::update()
{
    Sonar::requestUpdate();
    _updateSonarDesiredOrientation();
}

std::vector<SonarSample> SonarScanner::findDrivableSamples()
{
    std::vector<SonarSample> drivableSamples{};

    for(uint16_t i = 0; i < _sonarSampleBuffer.size(); i++)
    {
        SonarSample currentSample = _sonarSampleBuffer[i];
        if((currentSample.distance > DISTANCE_THREASHOLD_TO_BE_CONSIDERED_VALID)
                || (currentSample.distance < 0))
        {
            drivableSamples.push_back(_sonarSampleBuffer[i]);
        }
    }

    return drivableSamples;
}

void SonarScanner::_updateSonarDesiredOrientation()
{
    float x = micros() / 300000.0;
    float angleScalar = sin(x);
    Outputs::servoMotorSonarZ.setMotorAngle(angleScalar * PI/2);
}

void SonarScanner::_addDataPoint(SonarSample sonarSample)
{
    _sonarSampleBuffer.add(sonarSample);
}

CircularBuffer<SonarSample> SonarScanner::_sonarSampleBuffer{MAX_AMOUNT_OF_SONAR_SAMPLES};