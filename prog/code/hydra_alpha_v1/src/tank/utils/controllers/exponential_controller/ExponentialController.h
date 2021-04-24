#ifndef EXPONENTIAL_CONTROLLER_H
#define EXPONENTIAL_CONTROLLER_H

class ExponentialController
{
public:
    ExponentialController(float convergenceRate);
    float sample(float destination);

private:
    float _position;
    float _convergenceRate;

};

#endif