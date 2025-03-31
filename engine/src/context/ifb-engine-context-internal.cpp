#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-context.hpp"
#include "ifb-engine-core.hpp"


using namespace ifb;

namespace ifb::engine {

    engine_core_t* context_memory_push_core (const engine_context_t* engine_context);
    void           context_memory_reset     (const engine_context_t* engine_context);
};

inline engine_core_t*
engine::context_memory_push_core(
    const engine_context_t* engine_context) {

    //push a core struct on the arena
    engine_core_t* core = (engine_core_t*)engine::memory_arena_push_bytes_absolute_pointer(
        engine_context->memory,
        engine_memory_arena_e_context,
        engine::_globals_core.core_struct_size);

    //read the core data
    core->memory   = engine_context->memory;
    core->graphics = engine::memory_stack_get_core_graphics (engine_context->memory);
    core->threads  = engine::memory_stack_get_core_threads  (engine_context->memory);
    core->files    = engine::memory_stack_get_core_files    (engine_context->memory);

    //we're done
    return(core);
}

inline void
engine::context_memory_reset(
    const engine_context_t* engine_context) {

    engine::memory_arena_reset(
        engine_context->memory,
        engine_memory_arena_e_context);
}
