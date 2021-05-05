#ifndef SONAR_SCANNER
#define SONAR_SCANNER

#include "SonarSample.h"
#include "../../../../shared/utils/data_structure/CircularBuffer.h"
#include "vector.h"

#define MAX_AMOUNT_OF_SONAR_SAMPLES 20
#define DISTANCE_THREASHOLD_TO_BE_CONSIDERED_VALID 200

class SonarScanner
{
public:
    static void init();
    static void update();
    static void _updateSonarDesiredOrientation();
    static void _addDataPoint(SonarSample sonarSample);
    static std::vector<SonarSample> findDrivableSamples();

private:
    static CircularBuffer<SonarSample> _sonarSampleBuffer;

};

#endif