#ifndef WRAPPER_H
#define WRAPPER_H

#include <functional>
#include <vector>
#include <type_traits>

#include "Argument.h"
#include "Holder.h"
#include "Uinteger_sequence.h"
#include "Package_size.h"

class ICallable {
public:
    virtual Holder call(const std::vector<Argument>& args = std::vector<Argument>()) = 0;
};


template<typename Ret, typename T, typename... Args>
class Wrapper : public ICallable {
public:
    using Pointer = Ret (T::*)(Args...);
    using ReturnType = Ret;
private:
    T& object;
    Pointer ptr;
    std::vector<Argument> args;
    std::size_t arg_counter;

    template<std::size_t... N>
    Holder call_helper(uinteger_sequence<N...> seq, const std::vector<Argument>& new_args) {
        auto tmp = args;
        for(auto& a: new_args) {
            tmp[a.index].value = a.value;
        }
        if constexpr (std::is_same_v<void, Ret>) {
            std::invoke(
                ptr, object, arg_cast<Args>(tmp[N])...
            ); 
            return Holder();
        } else {
            return std::invoke(
                ptr, object, arg_cast<Args>(tmp[N])...
            );
        }
    }
public:
    Wrapper() = delete;
    Wrapper(T& object, Pointer ptr, std::vector<Argument> args)
        : object(object)
        , ptr(ptr)
        , args(args)
        , arg_counter(args.size()) {}
    
    Holder call(const std::vector<Argument>& args = std::vector<Argument>()) override {
        return call_helper(
            make_uinteger_squence
            <
                package_size_v<Args...>
            >(),
            args
        );
    }
};

template<typename Ret, typename T, typename... Args>
Wrapper(const T& object, Ret (T::*ptr)(Args...), std::vector<Argument> args) -> Wrapper<Ret, T, Args...>;

#endif