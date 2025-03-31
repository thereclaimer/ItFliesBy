#pragma once

#include "ifb-engine-memory.hpp"

/**********************************************************************************/
/* ENGINE MEMORY                                                                  */
/**********************************************************************************/

ifb_internal IFBEngineMemory* 
ifb_engine::memory_allocate(
    const memory_t& stack_memory) {

    //create stack handle 
    IFBMEMStack global_stack_handle = ifb_memory::stack_create(stack_memory);

    //memory sizes
    const ifb::u32  memory_size_struct             = ifb_engine::_global_memory_sizes.memory_struct;
    const ifb::u16  memory_size_singleton_buffer   = ifb_engine::_global_memory_sizes.singleton_buffer;
    const ifb::u32  memory_size_arena_handle_array = ifb_engine::_global_memory_sizes.arena_handle_array;
    const ifb::u32  memory_size_arena              = ifb_engine::_global_memory_sizes.total_arena;
    const ifb::u32  memory_count_arena             = ifb_engine::_global_memory_sizes.arena_count;
    const ifb::u64  memory_size_reservation        = ifb_engine::_global_memory_sizes.total_reservation;

    //allocate stack memory
    const ifb::ptr ptr_engine_memory               = ifb_memory::stack_push_bytes_absolute_pointer (global_stack_handle, memory_size_struct);
    const ifb::ptr ptr_singleton_buffer            = ifb_memory::stack_push_bytes_absolute_pointer (global_stack_handle, memory_size_singleton_buffer);
    const ifb::ptr ptr_arena_array                 = ifb_memory::stack_push_bytes_absolute_pointer (global_stack_handle, memory_size_arena_handle_array);

    //cast pointers
    IFBEngineMemory* engine_memory               = (IFBEngineMemory*)ptr_engine_memory;
    ifb::byte*         singleton_buffer            = (ifb::byte*)ptr_singleton_buffer;
    IFBMEMArena*     arena_handle_array          = (IFBMEMArena*)ptr_arena_array;

    //reserve system memory
    IFBMEMReservation system_reservation_handle = ifb_memory::reserve_system_memory(
        global_stack_handle,
        memory_size_reservation,
        memory_size_arena);

    //commit arenas
    for (
        ifb::u32 index = 0;
               index < memory_count_arena;
             ++index) {

        arena_handle_array[index] = ifb_memory::arena_commit(system_reservation_handle);
    }

    //initialize the memory struct
    engine_memory->stack.global_stack_handle             = global_stack_handle;
    engine_memory->stack.singleton_buffer                = singleton_buffer;
    engine_memory->reservation.system_reservation_handle = system_reservation_handle;
    engine_memory->reservation.arena_handle_array        = arena_handle_array; 

    //we're done
    return(engine_memory);
}