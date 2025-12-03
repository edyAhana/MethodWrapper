#ifndef ENGINE_H
#define ENGINE_H

#include <unordered_map>
#include <string>

#include "Wrapper.h"

class Engine {
private:
    std::unordered_map<std::string, ICallable*> func_list; 
public:
    Engine() = default;
    void register_command(ICallable* func, const std::string& name);
    Holder execute(const std::string& name, std::vector<Argument> args = std::vector<Argument>());
};



#endif