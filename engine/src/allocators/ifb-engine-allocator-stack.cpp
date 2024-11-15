#pragma once

#include "ifb-engine-internal-allocators.hpp"

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBEngineStackAllocatorTable* 
ifb_engine::stack_allocator_table_from_handle(
    const ifb_u32 stack_allocator_table_handle) {

    IFBEngineStackAllocatorTable* stack_allocator_table_ptr = 
        (IFBEngineStackAllocatorTable*)ifb_engine::memory_pointer_from_handle(stack_allocator_table_handle);

    return(stack_allocator_table_ptr);
}

const ifb_b8 stack_allocator_table_initialize(const ifb_u32 stack_allocator_table_handle);
