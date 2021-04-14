// Author: John-William Lebel, 2021-04-13, creation

#include "Orientation.h"
#include "Vector3.h"

Orientation3::Orientation3() : 
    front{Vector3()},
    roof{Vector3()}
{}

Orientation3::Orientation3(Vector3 initialFront, Vector3 initialRoof) : 
    front{initialFront},
    roof{initialRoof}
{}