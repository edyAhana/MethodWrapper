#include "Argument.h"

Argument::Argument(const Argument& other)
    : value(other.value)
    , index(other.index) {}

Argument::Argument(Argument&& other) noexcept
    : value(std::move(other.value))
    , index(other.index) {}

Argument& Argument::operator=(const Argument& other) {
    if(this == &other) {
        return *this;
    }
    value = other.value;
    index = other.index;
    return *this;
}

Argument& Argument::operator=(Argument&& other) noexcept {
    if(this == &other) {
        return *this;
    }
    value = std::move(other.value);
    index = other.index;
    return *this;
}