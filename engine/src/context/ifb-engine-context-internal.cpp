#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-context.hpp"

namespace ifb_engine {

    IFBEngineCore* context_memory_push_core (const IFBEngineContext* engine_context);
    void        context_memory_reset     (const IFBEngineContext* engine_context);
};

inline IFBEngineCore*
ifb_engine::context_memory_push_core(
    const IFBEngineContext* engine_context) {

    //push a core struct on the arena
    IFBEngineCore* core = (IFBEngineCore*)ifb_engine::memory_arena_push_bytes_absolute_pointer(
        engine_context->memory,
        IFBEngineArena_Context,
        ifb_engine::_global_core.core_struct_size);

    //read the core data
    core->memory   = engine_context->memory;
    core->graphics = ifb_engine::memory_stack_get_manager_graphics (engine_context->memory);
    core->threads  = ifb_engine::memory_stack_get_manager_threads  (engine_context->memory);
    core->files    = ifb_engine::memory_stack_get_manager_files    (engine_context->memory);

    //we're done
    return(core);
}

inline void
ifb_engine::context_memory_reset(
    const IFBEngineContext* engine_context) {

    ifb_engine::memory_arena_reset(
        engine_context->memory,
        IFBEngineArena_Context);
}
