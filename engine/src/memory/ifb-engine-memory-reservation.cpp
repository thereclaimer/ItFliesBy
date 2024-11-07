#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-platform.hpp"

/**********************************************************************************/
/* INLINE METHODS                                                                 */
/**********************************************************************************/


inline const ifb_b8 
ifb_engine::memory_reserve(
    IFBEngineMemoryReservation& reservation_ref) {

    //get the platform memory info
    const ifb_size platform_allocation_granularity = ifb_engine::platform_system_allocation_granularity();
    const ifb_size platform_page_size              = ifb_engine::platform_system_page_size();

    //get the platform reservation
    const ifb_size   reservation_size  = ifb_engine::memory_size_gigabytes(IFB_ENGINE_MEMORY_RESERVATION_SIZE_GIGABYTES);
    const ifb_memory reservation_start = ifb_engine::platform_memory_pages_reserve(reservation_size);  

    //initialize the struct
    reservation_ref.platform_allocation_granularity = platform_allocation_granularity;
    reservation_ref.platform_page_size              = platform_page_size;
    reservation_ref.pages_total                     = reservation_size / platform_page_size;
    reservation_ref.pages_used                      = 0;
    reservation_ref.size                            = reservation_size;
    reservation_ref.start                           = reservation_start;

    //we're done
    return(reservation_start != NULL);
}

inline const ifb_b8 
ifb_engine::memory_release(
    IFBEngineMemoryReservation& reservation_ref) {

    //release the reservation
    const ifb_b8 result = ifb_engine::platform_memory_pages_release(
        reservation_ref.start,
        reservation_ref.size);

    //we're done
    return(result);
}

inline const ifb_size
ifb_engine::memory_reservation_next_page(
    IFBEngineMemoryReservation& reservation_ref) {

    return(reservation_ref.pages_used);
}

inline const ifb_memory
ifb_engine::memory_reservation_get_pointer(
          IFBEngineMemoryReservation& reservation_ref, 
    const ifb_u32                     page_number,
    const ifb_u32                     page_offset) {

    const ifb_size page_start         = reservation_ref.platform_page_size * page_number;
    const ifb_size reservation_offset = page_start + page_offset;   
    
    const ifb_memory memory = reservation_ref.start + reservation_offset; 

    return(memory);
}

inline const ifb_size
ifb_engine::memory_reservation_page_count_aligned(
            IFBEngineMemoryReservation& reservation_ref,
    const ifb_size                      size) {

    const ifb_size size_aligned =
        ifb_engine_macro_align_a_to_b(
            size,
            reservation_ref.platform_page_size);

    const ifb_size page_count_aligned = size_aligned / reservation_ref.platform_page_size;

    return(page_count_aligned); 
}

inline const ifb_b8
ifb_engine::memory_reservation_add_pages(
          IFBEngineMemoryReservation& in_reservation_ref,
    const ifb_u32                     in_page_count,
          ifb_u32&                   out_page_start_ref) {

    //calculate the new page count
    const ifb_u32 page_count_new = in_reservation_ref.pages_used + in_page_count;

    //sanity check
    if (
        page_count_new > in_reservation_ref.pages_total ||
        in_page_count == 0) {

        return(false);
    }

    //get the page start as the current used page count
    out_page_start_ref = in_reservation_ref.pages_used;

    //update the used page count
    in_reservation_ref.pages_used = page_count_new;

    //we're done
    return(true);
}

inline const ifb_u32
ifb_engine::memory_reservation_page_offset(
    IFBEngineMemoryReservation& reservation_ref,
    ifb_u32                     page_number) {

    const ifb_u32 page_offset = reservation_ref.platform_page_size * page_number;

    return(page_offset);
}

inline const ifb_memory
ifb_engine::memory_reservation_page_start_pointer(
    IFBEngineMemoryReservation& reservation_ref,
    ifb_u32                     page_number) {

    const ifb_memory page_start = ifb_engine::memory_reservation_get_pointer(
        reservation_ref,
        page_number,
        0);

    return(page_start);
}

inline const ifb_size
ifb_engine::memory_reservation_pages_size(
    IFBEngineMemoryReservation& reservation_ref,
    ifb_u32                     page_count) {

    const ifb_size pages_size = reservation_ref.platform_page_size * page_count;

    return(pages_size);
}