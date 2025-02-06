#pragma once

#include <ifb-memory.hpp>

#include "ifb-engine-internal-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

#define IFB_ENGINE_MEMORY_SINGLETON_STACK_SIZE 0xFFFF

namespace ifb_engine {

    ifb_global IFBStack* _memory_singleton_stack_ptr;

    const ifb_b8 memory_singleton_stack_commit(const IFBMemoryHandle memory_handle);
};


/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline const ifb_b8
ifb_engine::memory_singleton_stack_commit(
    const IFBMemoryHandle memory_handle) {

    //sanity check
    ifb_macro_assert(memory_handle);

    //calculate the stack allocation size
    const ifb_u32 singleton_stack_size            = IFB_ENGINE_MEMORY_SINGLETON_STACK_SIZE;
    const ifb_u32 signleton_stack_allocation_size = ifb_data::stack_allocation_size(singleton_stack_size); 

    //allocate the stack
    const ifb_ptr stack_base_ptr = ifb_memory::stack_push(memory_handle,signleton_stack_allocation_size);;

    //create the stack
    _memory_singleton_stack_ptr = ifb_data::stack_create(
        stack_base_ptr,
        singleton_stack_size);

    //we're done
    return(_memory_singleton_stack_ptr != NULL);
}
