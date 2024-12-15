#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-context.hpp"

inline ifb_void 
ifb_engine::context_reset(
    ifb_void) {

    memset(&_engine_context,0,sizeof(IFBEngineContext));
}

inline IFBEngineContextStack&
ifb_engine::context_get_stack(
    ifb_void) {

    return(_engine_context.stack);
}

inline IFBEngineContextManagers&
ifb_engine::context_get_managers(
    ifb_void) {

    return(_engine_context.managers);
}

inline IFBEngineContextCore&
ifb_engine::context_get_core(
    ifb_void) {

    return(_engine_context.core);
}

inline ifb_void 
ifb_engine::context_initialize_stack(
    const IFBEngineConfig* config_ptr) {

    //get the stack
    IFBEngineContextStack& stack_ref = ifb_engine::context_get_stack();

    const ifb_u32 stack_size = ifb_macro_size_kilobytes(config_ptr->global_stack_kb);

    stack_ref.size     = stack_size;
    stack_ref.position = 0;
    ifb_macro_assert(stack_ref.memory);
}

inline ifb_void 
ifb_engine::context_initialize_memory(
    const IFBEngineConfig* config_ptr) {

    //get the memory pointer
    IFBEngineMemory* ptr_memory = ifb_engine::context_get_memory();

    //reserve memory
    ifb_engine::memory_reserve(
        ptr_memory,
        config_ptr->memory_minimum_gb,
        config_ptr->memory_commit_count_max);
}

inline const ifb_ptr 
ifb_engine::context_get_pointer(
    const IFBHND& handle) {

    //get memory
    IFBEngineMemory* engine_memory_ptr = ifb_engine::context_get_memory();

    //get the pointer
    const ifb_ptr pointer = ifb_engine::memory_get_pointer(engine_memory_ptr,handle);
    
    //we're done
    return(pointer);
}
