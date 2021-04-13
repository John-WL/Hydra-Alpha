// Author: John-William Lebel, 2021-04-11, creation

// class used to control the bdc motors

// ********important********
// the bdcs are swapped in the schematic!!!
// (left is actually right and right is actually left)

#ifndef BDC_MOTOR_H
#define BDC_MOTOR_H

#define MAX_BDC_MOTOR_TORQUE 32

class BdcMotor
{
    public:
        BdcMotor(void (*)(signed char));
        void update();
        void setMotorTorque(signed char);

        static void generalHardwareAccess(signed char motorTorque, unsigned char bitOffset);

    private:
        signed char _motorTorque;
        void (*_hardwareAccessFunction)(signed char);
};

#endif