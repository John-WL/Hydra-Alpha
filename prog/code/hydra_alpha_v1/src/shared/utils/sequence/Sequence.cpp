// Author: John-William Lebel, 2021-04-12, creation

#include "Sequence.h"

#include "Vector.h"

Sequence::Sequence(std::vector<void (*)(void)> updateFunctions) :
    _updateFunctions{updateFunctions},
    _updateFunctionsIterator{_updateFunctions.begin()++}
{}

void Sequence::update()
{
    (*_updateFunctionsIterator)();

    _updateFunctionsIterator++;
    if(_updateFunctionsIterator >= _updateFunctions.end())
    {
        _updateFunctionsIterator = _updateFunctions.begin()++;
    }
}
