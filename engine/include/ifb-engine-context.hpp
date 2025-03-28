#ifndef IFB_ENGINE_CONTEXT_HPP
#define IFB_ENGINE_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-memory.hpp"

struct IFBEngineContext {
    IFBEngineMemoryManager* memory_manager;
};

#endif //IFB_ENGINE_CONTEXT_HPP