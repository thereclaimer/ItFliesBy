#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.cpp"

namespace ifb_memory {

    IFBVoid reservation_assert_valid(const IFBMemoryReservation* reservation);
}

/**********************************************************************************/
/* MEMORY RESERVATION                                                             */
/**********************************************************************************/

IFBMEMReservation
ifb_memory::reserve_system_memory(
          IFBMemoryStack* stack,
    const IFBU64          size_reservation,
    const IFBU32          size_arena) {

    //validate args
    ifb_macro_assert(stack);
    ifb_macro_assert(size_reservation);
    ifb_macro_assert(size_arena);

    //get system info
    IFBSystemMemoryInfo sys_mem_info;
    ifb_platform::system_get_info_memory(&sys_mem_info);

    //align sizes to system info
    const IFBU64 size_aligned_reservation = ifb_macro_align_a_to_b(size_reservation,(IFBU64)sys_mem_info.allocation_granularity);
    const IFBU32 size_aligned_arena       = ifb_macro_align_a_to_b(size_arena,              sys_mem_info.page_size);

    //reserve system memory
    const IFBPtr  system_memory_pointer = ifb_platform::memory_reserve(size_aligned_reservation);
    const IFBAddr system_memory_start   = (IFBAddr)system_memory_pointer;
    ifb_macro_assert(system_memory_pointer);

    //get the stack start
    const IFBAddr stack_start = (IFBAddr)stack;

    //push the reservation struct on the stack
    IFBMemoryReservation* reservation = ifb_memory_macro_stack_push_reservation(stack);
    ifb_macro_assert(reservation);

    //calculate the struct offset
    const IFBAddr address_stack_start       = (IFBAddr)stack;
    const IFBAddr address_stack_reservation = (IFBAddr)reservation;
    const IFBAddr address_stack_offset      = address_stack_reservation - address_stack_start;  

    //initialize the reservation
    reservation->arenas_committed    = NULL;
    reservation->arenas_decommitted  = NULL;
    reservation->system_memory_start = system_memory_start;
    reservation->page_count_used     = 0;
    reservation->stack_offset        = address_stack_offset;
    reservation->size_arena          = size_aligned_arena;
    reservation->size_page           = sys_mem_info.page_size;
    reservation->size_granularity    = sys_mem_info.allocation_granularity;

    //we're done
    return(reservation);
}

const IFBB8      
ifb_memory::release_system_memory(
    IFBMemoryReservation* reservation) {
    
    ifb_macro_panic();

    return(false);
}
