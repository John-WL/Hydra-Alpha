#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include "Arduino.h"

#include "Vector.h"

template<typename T>
class CircularBuffer
{
public:
    CircularBuffer(uint16_t size) :
        _linearBuffer{},
        _nextAddIndex{0},
        _size{0},
        _desiredSize{size}
    {
        _linearBuffer.reserve(size);
    }

    T operator[](uint16_t index)
    {
        return _linearBuffer
        [
            (
                ((_nextAddIndex - 1) - index) 
                + _linearBuffer.size()
            )
            % _linearBuffer.size()
        ];
    }

    void add(T element)
    {
        if(_linearBuffer.size() >= _desiredSize)
        {
            _linearBuffer.erase(_linearBuffer.begin() + _nextAddIndex);
        }
        _linearBuffer.insert(_linearBuffer.begin() + _nextAddIndex, element);

        _nextAddIndex++;
        if(_nextAddIndex >= _linearBuffer.size())
        {
            _nextAddIndex = 0;
        }

        if(_size < _linearBuffer.size())
        {
            _size++;
        }
    }
    
    uint16_t size()
    {
        return _size;
    }

private:
    std::vector<T> _linearBuffer;
    uint16_t _nextAddIndex;
    uint16_t _size;
    uint16_t _desiredSize;

};

#endif