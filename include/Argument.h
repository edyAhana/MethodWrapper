#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <iostream>
#include "Holder.h"

class Argument {
public:
    Holder value;
    uint8_t index;

    Argument() = default;
    
    template<typename T>
    Argument(uint8_t index, const T& value)
        : index(index)
        , value(value) {}

    Argument(const Argument& other);
    
    Argument(Argument&& other) noexcept;

    Argument& operator=(const Argument& other);
    
    Argument& operator=(Argument&& other) noexcept;
};

template<typename T>
T arg_cast(const Argument& arg) {
    return holder_cast<T>(arg.value);
}

#endif