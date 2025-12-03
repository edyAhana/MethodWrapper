#ifndef UINT_SEQUENCE_H
#define UINT_SEQUENCE_H

#include <cstddef>

template<std::size_t... I>
struct uinteger_sequence {};

namespace details {
    template<std::size_t C, std::size_t N, std::size_t... Ints>
    struct  make_uinteger_sequence_helper {
        using type = typename make_uinteger_sequence_helper<C+1, N, Ints..., C>::type;
    };

    template<std::size_t N, std::size_t... Ints>
    struct make_uinteger_sequence_helper<N, N, Ints...> {
        using type = uinteger_sequence<Ints...>;
    };
};

template<std::size_t N>
using make_uinteger_squence = typename details::make_uinteger_sequence_helper<0, N>::type;

#endif

