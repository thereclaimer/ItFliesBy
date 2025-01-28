#pragma once

#include "ifb-memory-internal.hpp"

#include "ifb-memory-arena.cpp"
#include "ifb-memory-reservation.cpp"

inline IFBMemory*
ifb_memory::create(
    const IFBPlatformApi& platform_api_ref,
    const ifb_byte*       stack_memory,
    const ifb_u32         stack_size,
    const ifb_u32         arena_count) {

    ifb_b8 result = true;

    //initialize the platform api
    ifb_memory::platform_memory_reserve         = platform_api_ref.memory.reserve;
    ifb_memory::platform_memory_release         = platform_api_ref.memory.release;
    ifb_memory::platform_memory_commit          = platform_api_ref.memory.commit;
    ifb_memory::platform_page_size              = platform_api_ref.system.page_size;
    ifb_memory::platform_allocation_granularity = platform_api_ref.system.allocation_granularity;

    //sanity check
    result &= ifb_memory::platform_memory_reserve;
    result &= ifb_memory::platform_memory_release;
    result &= ifb_memory::platform_memory_commit;
    result &= ifb_memory::platform_page_size;
    result &= ifb_memory::platform_allocation_granularity;
    result &= stack_memory != NULL;

    if (!result) return(NULL);

    //calculate the size of the memory struct
    const ifb_u32 memory_struct_size = ifb_macro_align_size_struct(IFBMemory);

    //cast the stack memory to the memory struct
    IFBMemory* memory_ptr = (IFBMemory*)stack_memory;

    //cache the properties
    IFBMemoryStack&      stack_ref       = memory_ptr->stack;
    IFBMemoryArenaTable& arena_table_ref = memory_ptr->arena_table;

    //initialize the stack
    stack_ref.position = memory_struct_size;
    stack_ref.size     = stack_size;

    //initialize the arena table
    arena_table_ref.arena_array_handle = ifb_memory::stack_push_arenas(memory_ptr,arena_count);
    arena_table_ref.arena_array        = ifb_memory::stack_get_pointer(memory_ptr,arena_table_ref.arena_array_handle);
    arena_table_ref.count_total        = arena_count;
    arena_table_ref.count_used         = 0;

    //sanity check
    if (arena_table_ref.arena_array == NULL) return(NULL);

    //initialize the arenas
    for (
        ifb_u32 arena_index = 0;
        arena_index < arena_count;
        ++arena_index) {

        IFBMemoryArena& arena_ref = arena_array_ptr[arena_index];
        arena_ref.allocators = {0};
        arena_ref.start      = 0;
        arena_ref.index      = arena_index;
        arena_ref.position   = 0;
        arena_ref.page_count = 0;
        arena_ref.page_start = 0;
    }

    //we're done
    return(memory_ptr);
}

inline const ifb_b8
ifb_memory::destroy(
    IFBMemory* memory_ptr) {

    ifb_b8 result = true;

    result &= ifb_memory::release(memory_ptr);

    const ifb_u32 stack_size  = memory_ptr->stack.size;
    const ifb_ptr stack_start = (ifb_ptr)memory_ptr; 

    memset(stack_start,0,stack_start);

    return(result);
}