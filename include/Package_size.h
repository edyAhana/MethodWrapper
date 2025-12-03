#ifndef PACKAGE_SIZE_H
#define PACKAGE_SIZE_H

#include <cstddef>

template<typename Head, typename... Tail>
struct package_size {
    static constexpr std::size_t value = package_size<Tail...>::value + 1;
};

template<typename Head>
struct package_size<Head> {
    static constexpr std::size_t value =  1;
};

template<typename... Args>
constexpr std::size_t package_size_v = package_size<Args...>::value;

#endif