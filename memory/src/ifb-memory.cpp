#pragma once

#include "ifb-memory-internal.hpp"

#include "ifb-memory-arena-base.cpp"
#include "ifb-memory-arena-block.cpp"
#include "ifb-memory-arena-linear.cpp"
#include "ifb-memory-reservation.cpp"
#include "ifb-memory-stack.cpp"

inline IFBMemory*
ifb_memory::create(
    const IFBPlatformApi& platform_api_ref,
    const ifb_byte*       stack_memory,
    const ifb_u32         stack_size) {

    //initialize the platform api
    ifb_memory::platform_memory_reserve         = platform_api_ref.memory.reserve;
    ifb_memory::platform_memory_release         = platform_api_ref.memory.release;
    ifb_memory::platform_memory_commit          = platform_api_ref.memory.commit;
    ifb_memory::platform_page_size              = platform_api_ref.system.page_size;
    ifb_memory::platform_allocation_granularity = platform_api_ref.system.allocation_granularity;

    //calculate the size of the memory struct
    const ifb_u32 memory_struct_size = ifb_macro_align_size_struct(IFBMemory);

    //make sure the api methods are defined and the stack is valid and large enough
    ifb_b8 result = true;
    result &= ifb_memory::platform_memory_reserve         != NULL;
    result &= ifb_memory::platform_memory_release         != NULL;
    result &= ifb_memory::platform_memory_commit          != NULL;
    result &= ifb_memory::platform_page_size              != NULL;
    result &= ifb_memory::platform_allocation_granularity != NULL;
    result &= stack_memory                                != NULL;
    result &= stack_size >= memory_struct_size;

    //if everything isn't valid, we're done
    if (!result) return(NULL);

    //cast the stack memory to the memory struct
    IFBMemory* memory_ptr = (IFBMemory*)stack_memory;

    //cache the properties
    IFBMemoryStack&     stack_ref      = memory_ptr->stack;
    IFBMemoryArenaList& arena_list_ref = memory_ptr->arena_list;

    //initialize the stack
    stack_ref.position = memory_struct_size;
    stack_ref.size     = stack_size;

    //clear the arena list
    arena_list_ref.first = NULL;
    arena_list_ref.last  = NULL;
    arena_list_ref.count = 0;

    //we're done
    return(memory_ptr);
}

inline const ifb_b8
ifb_memory::destroy(
    IFBMemory* memory_ptr) {

    //sanity check
    ifb_macro_assert(memory_ptr);

    //release the reservation
    const ifb_b8 result = ifb_memory::release(memory_ptr);

    //clear the stack
    const ifb_u32 stack_size  = memory_ptr->stack.size;
    const ifb_ptr stack_start = (ifb_ptr)memory_ptr; 
    memset(stack_start,0,stack_size);

    //we're done
    return(result);
}