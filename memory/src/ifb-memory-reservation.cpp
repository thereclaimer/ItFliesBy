#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.cpp"

namespace ifb_memory {

    void reservation_assert_valid(const IFBMemoryReservation* reservation);
}

/**********************************************************************************/
/* MEMORY RESERVATION                                                             */
/**********************************************************************************/

IFBMEMReservation
ifb_memory::reserve_system_memory(
          IFBMemoryStack* stack,
    const ifb::u64          size_reservation,
    const ifb::u32          size_arena) {

    //validate args
    ifb_macro_assert(stack);
    ifb_macro_assert(size_reservation);
    ifb_macro_assert(size_arena);

    //get system info
    IFBSystemMemoryInfo sys_mem_info;
    ifb_platform::system_get_info_memory(&sys_mem_info);

    //align sizes to system info
    const ifb::u64 size_aligned_reservation = ifb_macro_align_a_to_b(size_reservation,(ifb::u64)sys_mem_info.allocation_granularity);
    const ifb::u32 size_aligned_arena       = ifb_macro_align_a_to_b(size_arena,              sys_mem_info.page_size);

    //reserve system memory
    const ifb::ptr  system_memory_pointer = ifb_platform::memory_reserve(size_aligned_reservation);
    const ifb::addr system_memory_start   = (ifb::addr)system_memory_pointer;
    ifb_macro_assert(system_memory_pointer);

    //get the stack start
    const ifb::addr stack_start = (ifb::addr)stack;

    //push the reservation struct on the stack
    IFBMemoryReservation* reservation = ifb_memory_macro_stack_push_reservation(stack);
    ifb_macro_assert(reservation);

    //calculate the struct offset
    const ifb::addr address_stack_start       = (ifb::addr)stack;
    const ifb::addr address_stack_reservation = (ifb::addr)reservation;
    const ifb::addr address_stack_offset      = address_stack_reservation - address_stack_start;  

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

const ifb::b8      
ifb_memory::release_system_memory(
    IFBMemoryReservation* reservation) {
    
    ifb_macro_panic();

    return(false);
}
