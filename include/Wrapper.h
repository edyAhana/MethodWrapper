#ifndef WRAPPER_H
#define WRAPPER_H

template<typename Ret, typename T, typename... Args>
class Wrapper {
public:
    using Pointer = Ret (T::*)(Args...);
private:
    T object;
    Pointer ptr;
public:
    Wrapper() = delete;
    Wrapper(const T& object, Pointer ptr)
        : object(object);
        , ptr(ptr) {}

    ~Wrapper() = default;
};

template<typename Ret, typename T, typename... Args>
Wrapper(const T& object, Ret (T::*ptr)(Args...)) -> Wrapper<Ret, T, Args...>;

#endif