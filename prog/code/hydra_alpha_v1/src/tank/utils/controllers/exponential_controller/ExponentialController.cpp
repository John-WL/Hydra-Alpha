#include "ExponentialController.h"

ExponentialController::ExponentialController(float convergenceRate) :
    _convergenceRate{convergenceRate},
    _position{0}
{}

float ExponentialController::sample(float _destination)
{
    _position += (_destination - _position) * _convergenceRate;

    return _position;
}