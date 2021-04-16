// Author: John-William Lebel, 2021-04-13, creation

#include "Orientation3.h"
#include "Vector3.h"

Orientation3::Orientation3() :
    front{DEFAULT_FRONT_ORIENTATION},
    roof{DEFAULT_ROOF_ORIENTATION}
{}

Orientation3::Orientation3(Vector3 initialFront, Vector3 initialRoof) :
    front{initialFront},
    roof{initialRoof}
{}

Orientation3 Orientation3::operator=(Orientation3 orientation)
{
    front = orientation.front;
    roof = orientation.roof;
}

Orientation3 Orientation3::rotate(Vector3 rotator)
{
    return Orientation3(front.rotate(rotator), roof.rotate(rotator));
}

Orientation3 Orientation3::eulerXyzToOrientation(Vector3 eulerXyz)
{
    Orientation3 orientation{};

    Vector3 rotatorX = Vector3(eulerXyz.x, 0, 0);
    Vector3 rotatorY = Vector3(0, eulerXyz.y, 0).rotate(rotatorX);
    Vector3 rotatorZ = Vector3(0, 0, eulerXyz.z).rotate(rotatorX).rotate(rotatorY);

    return Orientation3{}.rotate(rotatorX).rotate(rotatorY).rotate(rotatorZ);
}