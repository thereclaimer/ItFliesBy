#pragma once

#include "ifb-engine-internal-core.hpp"

#include "ifb-engine-core-memory.cpp"

inline IFBEngineCore*
ifb_engine::core_create(
    IFBMemoryContext* memory_context) {

    //sanity check
    ifb_macro_assert(memory_context);

    //allocate the core
    const IFBU32 core_size  = ifb_macro_align_size_struct(IFBEngineCore);
    IFBEngineCore* core_ptr = (IFBEngineCore*)ifb_memory::context_stack_commit_absolute(memory_context,core_size);
    ifb_macro_assert(core_ptr);

    //initialize the core structure
    core_ptr->memory.ptr_context     = memory_context; 
    core_ptr->memory.ptr_reservation = NULL; 

    //result for the next steps
    IFBU32 result = true;

    const IFBU64 platform_memory_size = ifb_macro_size_gigabytes(4);

    //reserve the platform memory
    result &= ifb_engine::core_memory_reserve_platform_memory(
        core_ptr,
        platform_memory_size);
    ifb_macro_assert(result);

    //we're done
    return(core_ptr);
}

inline const IFBB8
ifb_engine::core_destroy(
    IFBEngineCore* core_ptr) {
    
    ifb_macro_assert(core_ptr);

    IFBB8 result = true;

    //destroy the memory context
    result &= ifb_memory::context_destroy(core_ptr->memory.ptr_context);

    return(result);
}