// Author: John-William Lebel, 2021-04-08, creation

#include "SwarmIsSwarmy.h"

void SwarmIsSwarmy::execute()
{
    if(SwarmIsSwarmy::rectangleInCameraFrameExists()) 
    {
        SwarmIsSwarmy::followState();
    }
    else
    {
        SwarmIsSwarmy::searchState();
    }
}

void SwarmIsSwarmy::followState()
{

}

void SwarmIsSwarmy::searchState()
{

}

bool SwarmIsSwarmy::rectangleInCameraFrameExists()
{
    return false;
}