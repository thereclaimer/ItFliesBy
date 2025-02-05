#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* RESERVE/RELEASE                                                                */
/**********************************************************************************/

inline const ifb_b8
ifb_memory::reserve(
    const IFBMemoryHandle memory_handle,
    const ifb_u64         reservation_size_minimum) {

    //cast the handle
    IFBMemory* memory_ptr = (IFBMemory*)memory_handle;
    ifb_macro_assert(memory_ptr);

    //cache reservation
    IFBMemoryReservation& reservation_ref = memory_ptr->reservation;

    //get platform memory reservation
    const ifb_u32 page_size              = ifb_memory::platform_page_size();
    const ifb_u32 allocation_granularity = ifb_memory::platform_allocation_granularity();
    const ifb_u64 reservation_size       = ifb_macro_align_a_to_b(reservation_size_minimum,(ifb_u64)allocation_granularity);
    const ifb_ptr reservation_ptr        = ifb_memory::platform_memory_reserve(reservation_size);

    //sanity check
    if (!reservation_ptr) return(false);

    //initialize the reservation
    reservation_ref.start           = (ifb_address)reservation_ptr;
    reservation_ref.size            = reservation_size;
    reservation_ref.granularity     = allocation_granularity;
    reservation_ref.page_size       = page_size;
    reservation_ref.pages_total     = reservation_size / page_size;
    reservation_ref.pages_committed = 0;

    //we're done
    return(true);
}

inline const ifb_b8
ifb_memory::release(
    const IFBMemoryHandle memory_handle) {

    //cast the handle
    IFBMemory* memory_ptr = (IFBMemory*)memory_handle;
    ifb_macro_assert(memory_ptr);

    //cache the reservation
    IFBMemoryReservation& reservation_ref = memory_ptr->reservation;

    //get reservation start and size if we have it
    const ifb_ptr reservation_start = (ifb_ptr)reservation_ref.start;
    const ifb_u64 reservation_size  = reservation_ref.size;          

    //tell the platform to release the memory
    const ifb_b8 result = ifb_memory::platform_memory_release(
        reservation_start,
        reservation_size);

    //we're done
    return(result);  
}

/**********************************************************************************/
/* ALIGNMENT                                                                      */
/**********************************************************************************/

inline const ifb_u32
ifb_memory::reservation_size_align_to_page(
    const IFBMemoryHandle memory_handle,
    const ifb_u32         size) {

    //cast the handle
    IFBMemory* memory_ptr = (IFBMemory*)memory_handle;
    ifb_macro_assert(memory_ptr);

    //calculate the aligned size
    const ifb_u32 page_size    = memory_ptr->reservation.page_size;
    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,page_size); 

    //we're done
    return(size_aligned);
}
 
inline const ifb_u32
ifb_memory::reservation_size_align_to_granularity(
    const IFBMemoryHandle memory_handle,
    const ifb_u32         size) {

    //cast the handle
    IFBMemory* memory_ptr = (IFBMemory*)memory_handle;
    ifb_macro_assert(memory_ptr);

    //calculate the aligned size
    const ifb_u32 granularity  = memory_ptr->reservation.granularity;
    const ifb_u32 size_aligned = ifb_macro_align_a_to_b(size,granularity); 

    //we're done
    return(size_aligned);
}

/**********************************************************************************/
/* PAGES                                                                          */
/**********************************************************************************/

inline const ifb_u32
ifb_memory::reservation_get_page_size(
    const IFBMemoryHandle memory_handle) {

    //cast the handle
    IFBMemory* memory_ptr = (IFBMemory*)memory_handle;
    ifb_macro_assert(memory_ptr);

    //get the page size
    const ifb_u32 page_size = memory_ptr->reservation.page_size;

    //we're done
    return(page_size);
}

inline const ifb_u32
ifb_memory::reservation_get_page_count_total(
    const IFBMemoryHandle memory_handle) {

    //cast the handle
    IFBMemory* memory_ptr = (IFBMemory*)memory_handle;
    ifb_macro_assert(memory_ptr);

    //get the page count
    const ifb_u32 page_count = memory_ptr->reservation.pages_total;

    //we're done
    return(page_count);
}

inline const ifb_u32
ifb_memory::reservation_get_page_count_committed(
    const IFBMemoryHandle memory_handle) {

    //cast the handle
    IFBMemory* memory_ptr = (IFBMemory*)memory_handle;
    ifb_macro_assert(memory_ptr);

    //get the page count
    const ifb_u32 page_count = memory_ptr->reservation.pages_committed;

    //we're done
    return(page_count);
}

/**********************************************************************************/
/* SIZE                                                                           */
/**********************************************************************************/

inline const ifb_u64
ifb_memory::reservation_get_size_total(
    const IFBMemoryHandle memory_handle) {

    //cast the handle
    IFBMemory* memory_ptr = (IFBMemory*)memory_handle;
    ifb_macro_assert(memory_ptr);

    //get the size
    const ifb_u64 total_size = memory_ptr->reservation.size; 

    //we're done
    return(total_size);
}  

inline const ifb_u64
ifb_memory::reservation_get_size_committed(
    const IFBMemoryHandle memory_handle) {

    //cast the handle
    IFBMemory* memory_ptr = (IFBMemory*)memory_handle;
    ifb_macro_assert(memory_ptr);

    //calculate the committed size
    const ifb_u64 page_count     = memory_ptr->reservation.pages_committed;
    const ifb_u64 page_size      = memory_ptr->reservation.page_size;
    const ifb_u64 committed_size = page_count * page_size;

    //we're done
    return(committed_size);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline const ifb_ptr
ifb_memory::reservation_get_page_start_next(
    const IFBMemory* memory_ptr) {

    //sanity check
    ifb_macro_assert(memory_ptr);

    //calculate the start of the next page
    const ifb_u32 page_number = memory_ptr->reservation.pages_committed;
    const ifb_ptr page_start  = ifb_memory::reservation_get_page_start(
        memory_ptr,
        page_number);

    //we're done
    return(page_start);
}

inline const ifb_ptr 
ifb_memory::reservation_get_page_start(
    const IFBMemory* memory_ptr,
    const ifb_u32    page_number) {

    //sanity check
    ifb_macro_assert(memory_ptr);

    //cache the reservation
    const IFBMemoryReservation& reservation_ref = memory_ptr->reservation;

    //make sure the page number is within our reservation
    if (page_number >= reservation_ref.pages_total) return(NULL);

    //calculate the pointer
    const ifb_u32     page_offset        = reservation_ref.page_size * page_number;
    const ifb_address page_start_address = reservation_ref.start     + page_offset;
    const ifb_ptr     page_start_pointer = (ifb_ptr)page_start_address;  

    //we're done
    return(page_start_pointer);
}

inline const ifb_b8
ifb_memory::reservation_page_commit(
    IFBMemory*           memory_ptr,
    IFBMemoryPageCommit& page_commit_ref) {

    //sanity check
    if (!memory_ptr || page_commit_ref.size == 0) {
        return(false);
    }

    //cache reservation
    IFBMemoryReservation& reservation_ref = memory_ptr->reservation;

    //align the size
    const ifb_u32 page_commit_size = ifb_memory::reservation_size_align_to_page(
        memory_ptr,
        page_commit_ref.size);

    //calculate the page count and numbers
    const ifb_u32 page_commit_count  = page_commit_size / reservation_ref.page_size;
    const ifb_u32 page_commit_number = reservation_ref.pages_committed;
    const ifb_u32 page_committed_new = page_commit_number + page_commit_ref.page_count;

    //make sure we can do the commit
    if (page_committed_new > reservation_ref.pages_total) return(false);

    //get the start address of the commit
    const ifb_ptr page_commit_start = ifb_memory::reservation_get_page_start_next(memory_ptr);

    //do the commit
    const ifb_ptr page_commit_result = ifb_memory::platform_memory_commit(
        page_commit_start,
        page_commit_size);

    //sanity check
    if (page_commit_result != page_commit_start) return(false);

    //update the page commit reference
    page_commit_ref.start       = (ifb_address)page_commit_result; 
    page_commit_ref.size        = page_commit_size; 
    page_commit_ref.page_number = page_commit_number; 
    page_commit_ref.page_count  = page_commit_count; 

    //we're done
    return(true);
}