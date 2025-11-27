#ifndef HOLDER_H
#define HOLDER_H

#include <memory>
#include <string>
#include <exception>

class Holder;

template <typename T>
T holder_cast(const Holder& holder);

class Holder {
private:
    struct Base {
        virtual Base* get_copy() = 0;
        virtual ~Base() = default;
    };

    template<typename T>
    struct Derived : Base{
        T value;
        Derived(const T& value): value(value) {}
        Derived(T&& value): value(std::move(value)) {}
        ~Derived() = default;

        Base* get_copy() override {
            return new Derived(value);
        }

        T get_value() const {
            return value;
        }
    };

    uint8_t index;
    std::unique_ptr<Base> value;

    template<typename T>
    T get_as() const {
        Derived<T>* arg = dynamic_cast<Derived<T>*>(value.get());
        if(!arg) {
            throw std::runtime_error("type of argument is not correct");
        }
        return arg->get_value();
    }

    template<typename U>
    friend U holder_cast(const Holder& holder);
public:
    Holder() = delete;

    template<typename T>
    Holder(std::string str, const T& value) 
        : index(str.back())
        , value(std::make_unique<Derived<T>>(value)) {}
    
    Holder(const Holder& other)
        : index(other.index)
        , value(other.value->get_copy()) {}
    
    Holder(Holder&& other)
        : index(other.index)
        , value(std::move(other.value)) {}


    Holder& operator=(const Holder& other) {
        if(this == &other) {
            return *this;
        }
        value.reset(other.value->get_copy());
        index = other.index;
        return *this;
    }

    Holder& operator=(Holder&& other) {
        if(this == &other) {
            return *this;
        }
        value = std::move(other.value);
        index = other.index;
        return *this;
    }


    uint8_t get_index() const {
        return index;
    }
};

template <typename T>
T holder_cast(const Holder& holder) {
    return holder.get_as<T>();
};

#endif