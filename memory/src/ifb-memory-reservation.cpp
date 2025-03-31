#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.cpp"

using namespace ifb;
using namespace ifb::memory;

/**********************************************************************************/
/* MEMORY RESERVATION                                                             */
/**********************************************************************************/

reservation_t*
memory::reserve_system_memory(
    stack_t*  stack,
    const u64 size_reservation,
    const u32 size_arena) {

    //validate args
    ifb_macro_assert(stack);
    ifb_macro_assert(size_reservation);
    ifb_macro_assert(size_arena);

    //get system info
    platform::system_info_memory_t sys_mem_info;
    platform::system_get_info_memory(&sys_mem_info);

    //align sizes to system info
    const u64 size_aligned_reservation = ifb_macro_align_a_to_b(size_reservation,(u64)sys_mem_info.allocation_granularity);
    const u32 size_aligned_arena       = ifb_macro_align_a_to_b(size_arena,           sys_mem_info.page_size);

    //reserve system memory
    const ptr  system_memory_pointer = platform::memory_reserve(size_aligned_reservation);
    const addr system_memory_start   = (addr)system_memory_pointer;    

    ifb_macro_assert(system_memory_pointer);

    //get the stack start
    const addr stack_start = (addr)stack;

    //push the reservation struct on the stack
    reservation_t* reservation = macro_stack_push_reservation(stack);
    ifb_macro_assert(reservation);

    //calculate the struct offset
    const addr address_stack_start       = (addr)stack;
    const addr address_stack_reservation = (addr)reservation;
    const addr address_stack_offset      = address_stack_reservation - address_stack_start;  

    //initialize the reservation
    reservation->arenas.committed   = NULL;
    reservation->arenas.decommitted = NULL;
    reservation->start              = system_memory_start;
    reservation->page_count_used    = 0;
    reservation->stack              = stack;
    reservation->sizes.arena        = size_aligned_arena;
    reservation->sizes.page         = sys_mem_info.page_size;
    reservation->sizes.granularity  = sys_mem_info.allocation_granularity;

    //we're done
    return(reservation);
}

const b8      
memory::release_system_memory(
    reservation_t* reservation) {
    
    ifb_macro_panic();

    return(false);
}
