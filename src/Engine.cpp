#include <exception>

#include "Engine.h"

void Engine::register_command(ICallable* func, const std::string& name) {
    if(func_list.contains(name)) {
        throw std::invalid_argument("this method is already exists");
    }
    func_list[name] = func;
    return;
}

Holder Engine::execute(const std::string& name, std::vector<Argument> args) {
    if(!func_list.contains(name)) {
        throw std::runtime_error("there is no such method");
    }
    
    return func_list[name]->call(args);
}