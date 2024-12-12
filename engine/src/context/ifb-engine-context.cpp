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

inline IFBEngineContextHandles&
ifb_engine::context_get_handles(
    ifb_void) {

    return(_engine_context.handles);
}

inline IFBEngineContextStats&
ifb_engine::context_get_stats(
    ifb_void) {

    return(_engine_context.stats);
}

inline ifb_void 
ifb_engine::context_initialize_managers(
    const IFBEngineConfig* config_ptr) {

    //get the manager pointers
    IFBEngineTagManager*   tag_manager_ptr   = ifb_engine::context_handles_get_tag_manager();
    IFBEngineArenaManager* arena_manager_ptr = ifb_engine::context_handles_get_arena_manager();

    //tag manager    
    ifb_engine::tag_manager_initialize(
        tag_manager_ptr,
        config_ptr->tag_c_str_length,
        config_ptr->tag_count_max);

    //arena manager
    ifb_engine::arena_manager_initialize(
        arena_manager_ptr,
        config_ptr->arena_minimum_kb,
        config_ptr->arena_count_max);
}

inline ifb_void 
ifb_engine::context_initialize_memory(
    const IFBEngineConfig* config_ptr) {

    //get the memory pointer
    IFBEngineMemory* ptr_memory = ifb_engine::context_handles_get_memory();

    //reserve memory
    ifb_engine::memory_reserve(
        ptr_memory,
        config_ptr->memory_minimum_gb,
        config_ptr->memory_commit_count_max);
}

inline const ifb_ptr 
ifb_engine::context_get_pointer(
    const ifb_u32 reservation_offset) {

    //get memory
    IFBEngineMemory* engine_memory_ptr = ifb_engine::context_handles_get_memory();

    //get the pointer
    const ifb_ptr pointer = ifb_engine::memory_get_pointer(engine_memory_ptr,reservation_offset);
    
    //we're done
    return(pointer);
}
