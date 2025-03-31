#pragma once

#include "ifb-engine-memory.hpp"

/**********************************************************************************/
/* ENGINE MEMORY                                                                  */
/**********************************************************************************/

ifb_internal engine_memory_t* 
engine::memory_allocate(
    const memory_t& stack_memory) {

    //create stack handle 
    memory_stack_h global_stack_handle = memory::stack_create(stack_memory);

    //memory sizes
    const u32  memory_size_struct             = engine::_globals_memory.memory_struct;
    const u16  memory_size_singleton_buffer   = engine::_globals_memory.singleton_buffer;
    const u32  memory_size_arena_handle_array = engine::_globals_memory.arena_handle_array;
    const u32  memory_size_arena              = engine::_globals_memory.total_arena;
    const u32  memory_count_arena             = engine::_globals_memory.arena_count;
    const u64  memory_size_reservation        = engine::_globals_memory.total_reservation;

    //allocate stack memory
    const ptr ptr_engine_memory               = memory::stack_push_bytes_absolute_pointer (global_stack_handle, memory_size_struct);
    const ptr ptr_singleton_buffer            = memory::stack_push_bytes_absolute_pointer (global_stack_handle, memory_size_singleton_buffer);
    const ptr ptr_arena_array                 = memory::stack_push_bytes_absolute_pointer (global_stack_handle, memory_size_arena_handle_array);

    //cast pointers
    engine_memory_t* engine_memory               = (engine_memory_t*)ptr_engine_memory;
    byte*            singleton_buffer            = (byte*)ptr_singleton_buffer;
    memory_arena_h*  arena_handle_array          = (memory_arena_h*)ptr_arena_array;

    //reserve system memory
    memory_reservation_h system_reservation_handle = memory::reserve_system_memory(
        global_stack_handle,
        memory_size_reservation,
        memory_size_arena);

    //commit arenas
    for (
        u32 index = 0;
            index < memory_count_arena;
          ++index) {

        arena_handle_array[index] = memory::arena_commit(system_reservation_handle);
    }

    //initialize the memory struct
    engine_memory->stack.global_stack_handle             = global_stack_handle;
    engine_memory->stack.singleton_buffer                = singleton_buffer;
    engine_memory->reservation.system_reservation_handle = system_reservation_handle;
    engine_memory->reservation.arena_handle_array        = arena_handle_array; 

    //we're done
    return(engine_memory);
}