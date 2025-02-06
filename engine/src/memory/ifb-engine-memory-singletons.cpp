#pragma once

#include <ifb-memory.hpp>
#include <ifb-data-structures.hpp>

#include "ifb-engine-internal-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

//max u16
#define IFB_ENGINE_MEMORY_SINGLETON_STACK_SIZE 0xFFFF

namespace ifb_engine {

    ifb_global IFBStack* _memory_singleton_stack_ptr;

    const ifb_b8 memory_singleton_stack_commit(const IFBMemoryHandle memory_handle);
};

/**********************************************************************************/
/* SINGLETONS                                                                     */
/**********************************************************************************/

inline const IFBEngineMemorySingletonId
ifb_engine::memory_singleton_commit(
    const ifb_u32 size,
    const ifb_u32 alignment) {

    //calculate sizes
    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,alignment);
    const ifb_u32 size_stack   = IFB_ENGINE_MEMORY_SINGLETON_STACK_SIZE;

    //do the push
    const ifb_u32 stack_offset = ifb_stack::push_relative(
        _memory_singleton_stack_ptr,
        size_aligned);

    //make sure the offset fits within the stack
    ifb_macro_assert(stack_offset < size_stack);

    //cast the offset to a singleton id
    const ifb_u16 singleton_id = *((ifb_u16*)&stack_offset);

    //we're done
    return(singleton_id);
}

inline const ifb_ptr
ifb_engine::memory_singleton_get_pointer(
    const ifb_u16 singleton_id) {

    //sanity check
    ifb_macro_assert(_memory_singleton_stack_ptr);
    ifb_macro_assert(singleton_id < IFB_ENGINE_MEMORY_SINGLETON_STACK_SIZE);

    //get the pointer
    const ifb_ptr pointer = ifb_stack::get_pointer(
        _memory_singleton_stack_ptr,
        singleton_id);

    //we're done
    return(pointer);
}

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
    const ifb_u32 singleton_stack_allocation_size = ifb_stack::allocation_size(singleton_stack_size); 

    //allocate the stack
    const ifb_ptr stack_base_ptr = ifb_memory::stack_push(memory_handle,signleton_stack_allocation_size);;

    //create the stack
    _memory_singleton_stack_ptr = ifb_stack::create(
        stack_base_ptr,
        singleton_stack_size);

    //we're done
    return(_memory_singleton_stack_ptr != NULL);
}