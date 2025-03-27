#pragma once

#include "ifb-engine-memory.hpp"


ifb_internal IFBEngineMemoryManager* 
ifb_engine::memory_manager_create(
    const IFBMEM64Stack global_stack) {

    //allocate memory manager
    IFBEngineMemoryManager* memory_manager = ifb_memory_macro_stack_push_struct_absolute(global_stack, IFBEngineMemoryManager);
    ifb_macro_assert(memory_manager);

    //sizes
    const IFBU64 size_reservation = ifb_macro_size_gigabytes((IFBU64)IFB_MEMORY_MANAGER_SIZE_GB_RESERVATION);
    const IFBU32 size_arena       = ifb_macro_size_kilobytes(IFB_MEMORY_MANAGER_SIZE_KB_ARENA);

    //reservation context
    IFBMemoryReservationContext reservation_context;
    reservation_context.handle_stack = global_stack;

    //reserve the memory
    IFBB8 result = ifb_memory::reserve_system_memory(
        reservation_context,
        size_reservation,
        size_arena);
    ifb_macro_assert(result);

    //set the memory manager properties
    memory_manager->global_stack       = global_stack;
    memory_manager->system_reservation = reservation_context.handle_reservation;

    ifb_memory::arena_commit()

    //we're done
    return(memory_manager);
}    

