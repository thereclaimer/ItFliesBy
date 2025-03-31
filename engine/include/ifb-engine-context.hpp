#ifndef IFB_ENGINE_CONTEXT_HPP
#define IFB_ENGINE_CONTEXT_HPP

#include "ifb-engine.hpp"
#include "ifb-engine-memory.hpp"

namespace ifb {

    struct engine_context_t {
        engine_memory_t* memory;
    };
};
#endif //IFB_ENGINE_CONTEXT_HPP