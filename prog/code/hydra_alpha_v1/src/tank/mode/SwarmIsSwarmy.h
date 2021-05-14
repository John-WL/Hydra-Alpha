// Author: John-William Lebel, 2021-04-08, creation

// This mode is pretty complicated, as it requires multiple delicate elements to work hand in hand.

// The purpose of this mode is to be able to follow the other tank without ANY inputs from the remote controller.



////////////////////////////////////////////////////////////////////////////
// First part! Find the position of the other tank.

// First, we're retreiving positioning information (I think it's a rectangle?) about where the other tank is in the camera's pixels.
// We then use the following elements to generate an
// approximate 3D vector orientation that points in the direction of the other tank:
// - the centered pixel position of the rectangle we just found;
// - the known approximate orientation of the camera (we can infer it from the current servomotor outputs);
// - and the known position of the camera on the tank.

// Let's call this approximate orientation we just found "~Ot".

// (note: an arbitrary position on the tank is used as the centered origin of any spacial calculation)

// We then use this value of ~Ot combined with the size of the rectangle found by
// the camera to approximate the position the other tank is from our perspective.
// More formaly:
// the approximate position of the other tank from our tank's perspective = findCorrespondingDistanceFromRectangleSize(rectangleSize) * ~Ot.
// Another way of writing it is:
// ~D = ~d(Rs) * ~Ot, where:
// ~D is the approximte 3D vector position of the other tank from our tank's perspective;
// ~d(x) is the distance finder function;
// Rs is the rectangle size of the other tank in the camera's pixels;
// ~Ot is the approximate orientation the other tank has from our tank's perspective (it's normalized).

// The function "findCorrespondingDistanceFromRectangleSize(x)" (or "~d(x)") only serves as a scaling function that gives a linear variation with
// non-linear rectangle size variations (it's basically a distance finder that uses the size of the rectangle to
// find the corresponding approximate distance).
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
// Second part! Control the tank so it follows the best it can the other tank.

// Once we've found ~D, we then need to throttle and steer the tank.
// The idea is to always try to keep a certain distance from the other tank,
// while trying to keep our orientation as straight as possible towards the other tank.

// I think the routine that the servos controlling the camera angles are going to need to follow is
// to try to keep the rectangle captured by the camera as centered as possible in the camera's frame.
// If we're using the centered position of the rectangle found to steer and level the camera angles, we're going to need
// to use some dampening for the outputed orientation of the servos...
// (There is gonna be some delay in the response of the servos, and the captured rectangle will also experience some delay)
// Let's call the camera angle controlled by the two servos "~Ocam" (it could be a 3D vector representing the
// actual local orientation, or a 2D vector containing the angles... We're probably going to need both anyway).

// After handling the "gimbal" of the camera, we are then steering the tank in such a way that it always tries to
// face the other tank the best it can. The last thing we do after steering is adding some throttle depending on the distance
// that separates us from the other tank.

// And that's about it.
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
// Third part! We need to handle edgecases...
// Yes, we ARE going to lose sight of the other tank. This is INEVITABLE.
// So, what do we do when there is no rectangle in the camera's frame?

// One way to "solve" this issue is to spin slowly the tank while keeping the camera straight forward.
// Once we find a rectangle, we switch to the "follow the other tank" state.

// Therefore, this whole system needs to be implemented into a state machine that has 2 states:
// 1) the "follow the other tank" state;
// 2) the "search for the other tank" state;
////////////////////////////////////////////////////////////////////////////



#ifndef SWARM_IS_SWARMY_H
#define SWARM_IS_SWARMY_H

// distance in mm
#define DESIRED_DITANCE_FROM_TARGET 500
#define APPROXIMATE_AVERAGE_LENGTH_OF_OTHER_TANK 200

#include "../peripheral/protocol_format/IncommingCommunicationFormat.h"

class SwarmIsSwarmy
{
public:
    static void execute(IncommingCommunicationFormat remoteInput);
    
private:
    static IncommingCommunicationFormat _followState(IncommingCommunicationFormat remoteInput);
    static IncommingCommunicationFormat _searchState(IncommingCommunicationFormat remoteInput);

    static bool _rectangleInCameraFrameExists();

    static IncommingCommunicationFormat _adjustOutputWithSensorData(IncommingCommunicationFormat output);
};

#endif
