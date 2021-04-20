// Author: John-William Lebel, 2021-04-12, creation

// just a class containing a function

#ifndef FUNCTION_CONTAINER_H
#define FUNCTION_CONTAINER_H

class FunctionContainer
{
    public:
        FunctionContainer(void (*containedFunction)(void))
        {
            _containedFunction = containedFunction;
        }

        void operator()(void)
        {
            return _containedFunction();
        }
    private:
        void (*_containedFunction)(void);

};

#endif