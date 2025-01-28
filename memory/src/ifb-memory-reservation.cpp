#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.hpp"

inline const ifb_b8
ifb_memory::reserve(
          IFBMemory* memory_ptr,
    const ifb_u64    reservation_size_minimum) {

    //sanity check
    if (!memory_ptr) return(false);

    //cache reservation
    IFBMemoryReservation& reservation_ref = memory_ptr->reservation;

    //get platform memory reservation
    const ifb_u32 page_size              = ifb_memory::platform_page_size();
    const ifb_u32 allocation_granularity = ifb_memory::platform_allocation_granularity();
    const ifb_u64 reservation_size       = ifb_macro_align_a_to_b(reservation_size_minimum,allocation_granularity);
    const ifb_ptr reservation_ptr        = ifb_memory::platform_memory_reserve(reservation_size);

    //sanity check
    if (!reservation_ptr) return(false);

    //initialize the reservation
    reservation_ref.start           = (ifb_address)reservation_ptr;
    reservation_ref.size            = reservation_size;
    reservation_ref.page_size       = page_size;
    reservation_ref.pages_total     = reservation_size / page_size;
    reservation_ref.pages_committed = 0;

    //we're done
    return(true);
}

inline const ifb_b8
ifb_memory::release(
    IFBMemory* memory_ptr) {

    //get reservation start and size if we have it
    const ifb_ptr reservation_start = memory_ptr ? (ifb_ptr)memory_ptr->reservation.start : NULL;
    const ifb_u64 reservation_size  = memory_ptr ? memory_ptr->reservation.size           : 0;

    //tell the platform to release the memory
    const ifb_b8 result = ifb_memory::platform_memory_release(
        reservation_start,
        reservation_size);

    //we're done
    return(result);
}

inline const ifb_address
ifb_memory::reservation_get_start_address(
    const IFBMemory* memory_ptr) {

    const ifb_address reservation_start = memory_ptr 
        ? memory_ptr->reservation.start
        : 0;

    return(reservation_start);
}

inline const ifb_ptr
ifb_memory::reservation_get_start_pointer(
    const IFBMemory* memory_ptr) {

    const ifb_ptr reservation_start = memory_ptr 
        ? (ifb_ptr)memory_ptr->reservation.start
        : NULL;

    return(reservation_start);
}

inline const ifb_u32
ifb_memory::reservation_get_page_size(
    const IFBMemory* memory_ptr) {

    const ifb_u32 page_size = memory_ptr
        ? memory_ptr->reservation.page_size
        : 0;

    return(page_size);
}

inline const ifb_u32
ifb_memory::reservation_get_pages_total(
    const IFBMemory* memory_ptr) {

    const ifb_u32 page_count = memory_ptr
        ? memory_ptr->reservation.pages_total
        : 0;

    return(page_count);

}

inline const ifb_u32
ifb_memory::reservation_get_pages_committed(
    const IFBMemory* memory_ptr) {

    const ifb_u32 page_count = memory_ptr
        ? memory_ptr->reservation.pages_committed
        : 0;

    return(page_count);
}

inline const ifb_u64
ifb_memory::reservation_get_size_total(
    const IFBMemory* memory_ptr) {

    if (!memory_ptr) return(0);

    const ifb_u64 page_count = memory_ptr->reservation.pages_total;
    const ifb_u64 page_size  = memory_ptr->reservation.page_size;
    const ifb_u64 total_size = page_count * page_size;

    return(reservation_size);
}  

inline const ifb_u64
ifb_memory::reservation_get_size_committed(
    const IFBMemory* memory_ptr) {

    if (!memory_ptr) return(0);

    const ifb_u64 page_count     = memory_ptr->reservation.pages_committed;
    const ifb_u64 page_size      = memory_ptr->reservation.page_size;
    const ifb_u64 committed_size = page_count * page_size;

    return(committed_size);
}
