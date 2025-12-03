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
        ~Derived() = default;

        Base* get_copy() override {
            return new Derived(value);
        }

        T get_value() const {
            return value;
        }
    };


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
    std::unique_ptr<Base> value;

    Holder() = default;

    template<typename T>
    Holder(const T& value) 
        : value(std::make_unique<Derived<T>>(value)) {}

    Holder(const Holder& other)
        : value(other.value->get_copy()) {}
    
    Holder(Holder&& other)
        : value(std::move(other.value)) {}

    Holder& operator=(const Holder& other) {
        if(this == &other) {
            return *this;
        }
        value.reset(other.value->get_copy());
        return *this;
    }

    Holder& operator=(Holder&& other) {
        if(this == &other) {
            return *this;
        }
        value = std::move(other.value);
        return *this;
    }

    template<typename U>
    Holder& operator=(U new_value) {
        value.reset();
        value = std::make_unique
                <
                    Derived<std::remove_reference_t<U>>
                > 
                (std::forward<U>(new_value));
        return *this;
    }
};

template <typename T>
T holder_cast(const Holder& holder) {
    return holder.get_as<T>();
};



#endif