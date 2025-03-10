#pragma once

#include "ifb-engine-internal-core.hpp"

#include "ifb-engine-core-memory.cpp"

inline IFBEngineCore*
ifb_engine::core_create(
    const IFBByte* core_stack_memory_ptr,
    const IFBU32   core_stack_memory_size,
    const IFBU64   core_reserved_memory_size) {

    //sanity check
    ifb_macro_assert(core_stack_memory_ptr);
    ifb_macro_assert(core_stack_memory_size);
    ifb_macro_assert(core_reserved_memory_size);

    //get the system infoc
    IFBSystemInfo system_info;
    const IFBB8 system_info_valid = ifb_platform::system_get_info(&system_info); 
    if (!system_info_valid) return(NULL);

    //create the memory context
    IFBMemoryContext* ptr_memory_context = ifb_memory::context_create(
        &system_info.memory,
        core_stack_memory_ptr,
        core_stack_memory_size);
    if (!ptr_memory_context) return(NULL);

    //allocate the core
    const IFBU32 core_size  = ifb_macro_align_size_struct(IFBEngineCore);
    IFBEngineCore* core_ptr = (IFBEngineCore*)ifb_memory::context_stack_commit_absolute(ptr_memory_context,core_size);
    ifb_macro_assert(core_ptr);
    
    //reserve the platform memory
    ifb_engine::core_memory_reserve_platform_memory(
        core_ptr,
        core_reserved_memory_size);

    //initialize the core structure
    core_ptr->system_info               = system_info;
    core_ptr->memory.ptr_memory_context = ptr_memory_context; 
    core_ptr->memory.stack.data         = (IFBByte*)core_stack_memory_ptr;
    core_ptr->memory.stack.size         = core_stack_memory_size;

    //we're done
    return(core_ptr);
}

inline const IFBB8
ifb_engine::core_destroy(
    IFBEngineCore* core_ptr) {
    
    ifb_macro_assert(core_ptr);

    IFBB8 result = true;

    //destroy the memory context
    result &= ifb_memory::context_destroy(core_ptr->memory.ptr_memory_context);

    return(result);
}