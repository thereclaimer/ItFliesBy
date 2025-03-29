#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-context.hpp"

namespace ifb_engine {

    IFBEngineContext* context_initialize             (IFBMEMStack stack);
    IFBEngineMemory*  context_allocate_engine_memory (IFBMEMStack stack);
    IFBEngineCore*    context_frame_alloc_core       (const IFBEngineContext* engine_context);
};

inline IFBEngineContext* 
ifb_engine::context_initialize(
    IFBMEMStack stack) {

    IFBEngineContext* context = ifb_memory_macro_stack_push_struct_absolute(stack,IFBEngineContext); 
    ifb_macro_assert(context);
    return(context);    
}

inline IFBEngineMemory*
ifb_engine::context_allocate_engine_memory(
    IFBMEMStack stack) {

    //allocate memory
    IFBEngineMemory* memory = ifb_engine::memory_allocate(stack);

    return(memory);
}

inline IFBEngineCore*
ifb_engine::context_frame_alloc_core(
    const IFBEngineContext* engine_context) {

    const IFBEngineMemory* memory = engine_context->memory;

    IFBMEMArena  frame_arena      = ifb_engine::memory_arena_frame(memory->arenas);
    const IFBU32 frame_alloc_size = ifb_engine::_global_core.core_struct_size;

    //push a core struct on the arena
    IFBEngineCore* core = (IFBEngineCore*)ifb_memory::arena_push_bytes_absolute_pointer(
        frame_arena,
        frame_alloc_size);

    //read the core data
    ifb_engine::memory_stack_get_core(memory->stack,core);

    //we're done
    return(core);
}
