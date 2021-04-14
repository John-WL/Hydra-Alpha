// Author: John-William Lebel, 2021-04-13, creation

#ifndef IMU_H
#define IMU_H

class Imu
{
    public:
        virtual Vector3 acceleration() = 0;

        virtual Orientation3 orientation() = 0;
        virtual Vector3 angularVelocity() = 0;

    private:
        
}

#endif