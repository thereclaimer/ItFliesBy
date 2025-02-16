#pragma once

#include "ifb-engine-internal-core.hpp"

#include "ifb-engine-core-memory.cpp"

inline IFBEngineCore*
ifb_engine::core_create(
    const ifb_byte* core_stack_memory_ptr,
    const ifb_u32   core_stack_memory_size) {

    //sanity check
    ifb_macro_assert(core_stack_memory_ptr);
    ifb_macro_assert(core_stack_memory_size);

    //get the platform api
    const IFBPlatformApi* ptr_platform_api = ifb_platform::get_api();

    //create the memory context
    const ifb_b8 memory_context_created = ifb_memory::context_create(
        ptr_platform_api,
        core_stack_memory_ptr,
        core_stack_memory_size);
    if (!memory_context_created) return(NULL);

    //allocate the core
    const ifb_u32 core_stack_offset = ifb_memory_macro_stack_push_struct(IFBEngineCore);
    if (core_stack_offset == 0) return(NULL);

    //get the pointer
    IFBEngineCore* core_ptr = (IFBEngineCore*)ifb_memory::stack_get_pointer(core_stack_offset);
    ifb_macro_assert(core_ptr);

    //initialize the core structure
    core_ptr->stack_offset      = core_stack_offset;
    core_ptr->memory.stack.data = (ifb_byte*)core_stack_memory_ptr;
    core_ptr->memory.stack.size = core_stack_memory_size;

    //we're done
    return(core_ptr);
}

inline const ifb_b8
ifb_engine::core_destroy(
    IFBEngineCore* core_ptr) {
    
    ifb_macro_assert(core_ptr);

    ifb_b8 result = true;

    //destroy the memory context
    result &= ifb_memory::context_destroy();

    return(result);
}