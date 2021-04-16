// Author: John-William Lebel, 2021-04-08, creation

// simple section of code where we gather all the info we need for the application

#ifndef INPUTS_H
#define INPUTS_H

#include "Vector.h"

#include "../../utils/sequence/Sequence.h"

class Inputs
{
    public:
        static void init();
        static void update();
        
    private:
        static std::vector<void (*)(void)> _updateFunctions;
        static Sequence _inputSequencer;

};

#endif
