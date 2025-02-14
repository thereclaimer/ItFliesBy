#pragma once

#include "ifb-engine-internal-context.hpp"


inline const ifb_b8
ifb_engine::context_memory_reserve(
    const ifb_byte* stack_buffer,
    const ifb_u32   stack_size,
    const ifb_u64   reservation_size) {

    ifb_b8 result = true;

    //sanity check
    ifb_macro_assert(stack_buffer);

    //get the memory properties
    IFBEngineContextMemory&            memory_ref      = ifb_engine::context_get_memory(); 
    IFBEngineContextMemoryReservation& reservation_ref = memory_ref.reservation;
    IFBEngineContextMemoryStack&       stack_ref       = memory_ref.stack;

    //create the memory context
    result &= ifb_memory::context_create(stack_buffer, stack_size);   

    //initialize the stack
    stack_ref.data = stack_buffer;
    stack_ref.size = stack_size;

    //reserve the memory
    const IFBMemoryReservationHandle reservation_handle = ifb_memory::reserve_memory(reservation_size);
    result &= ifb_memory_macro_handle_valid(reservation_handle);

    //initialize the reservation
    reservation_ref.handle = reservation_handle;
    reservation_ref.size   = reservation_size;

    //we're done
    return(result);
}

inline const ifb_b8
ifb_engine::context_memory_singleton_commit(
    const ifb_u32                          count,                   
    const IFBEngineSizeAndAlignment*       size_and_alignment_array,
          IFBEngineContextSingletonHandle* singleton_handle_array) {

    ifb_b8 result = true;

    //sanity check
    ifb_macro_assert(count > 0);
    ifb_macro_assert(size_and_alignment_array);
    ifb_macro_assert(singleton_handle_array);

    for (
        ifb_u32 singleton_index = 0;
        singleton_index < count;
        ++singleton_index) {

        //get the current singleton info
        const IFBEngineSizeAndAlignment& current_size_and_alignment = size_and_alignment_array [singleton_index];
        IFBEngineContextSingletonHandle& current_singleton_handle   = singleton_handle_array   [singleton_index]; 

        //commit the singleton
        current_singleton_handle.value = ifb_memory::stack_push(
            current_size_and_alignment.size,
            current_size_and_alignment.alignment);

        //validate the handle
        result &= ifb_memory_macro_handle_valid(current_singleton_handle);
    }

    //we're done
    return(result);
}

inline const ifb_ptr
ifb_engine::context_memory_singleton_load(
    const ifb_u32 offset) {

    //get the singleton pointer from the stack
    const ifb_ptr singleton_ptr = ifb_memory::stack_get_pointer(offset);
    return(singleton_ptr);
}