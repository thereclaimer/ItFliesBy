#ifndef IFB_ENGINE_INTERNAL_CONTEXT_HPP
#define IFB_ENGINE_INTERNAL_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-internal-memory.hpp"

struct IFBEngineContext {
    IFBEngineMemoryManager memory_manager;
};

namespace ifb_engine {

    IFBEngineMemoryManager& context_get_memory_manager (ifb_void);
};

#endif //IFB_ENGINE_INTERNAL_CONTEXT_HPP