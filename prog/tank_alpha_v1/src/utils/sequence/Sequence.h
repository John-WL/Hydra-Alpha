// Author: John-William Lebel, 2021-04-12, creation

// Implementation of a "function sequencer". 
// When the function "update()" is called, 
// objects of this class will iterate over
// all the lambda functions passed as parameters
// to their constructor

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "Vector.h"

#include "../function_container/FunctionContainer.h"

class Sequence
{
    public:
        Sequence(std::vector<void (*)(void)>);

        void update();
        
    private:
        std::vector<void (*)(void)> _updateFunctions;
        std::vector<void (*)(void)>::iterator _updateFunctionsIterator;
    
};

#endif