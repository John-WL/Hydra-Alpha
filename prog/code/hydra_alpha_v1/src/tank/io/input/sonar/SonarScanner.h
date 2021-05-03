#ifndef SONAR_SCANNER
#define SONAR_SCANNER

class SonarScanner
{
public:
    static void init();
    static void updateSonarDesiredOrientation();
    static std::vector<float> findDrivableAngles();
    static void addDataPoint(SonarDataPoint sonarDataPoint);

private:
    static QueueArray<SonarDataPoint> _sonarDataPoints;

};

#endif