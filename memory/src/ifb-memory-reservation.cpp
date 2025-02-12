#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_memory {

    inline IFBMemoryReservation* reservation_get_pointer_from_handle (const IFBMemoryReservationHandle reservation_handle);
};

/**********************************************************************************/
/* RESERVE/RELEASE                                                                */
/**********************************************************************************/

ifb_internal inline const IFBMemoryReservationHandle
ifb_memory::reserve_memory(
    const ifb_u64 size_minimum) {

    //get the reservation list and system info
    IFBMemoryReservationList& reservation_list_ref = ifb_memory::context_get_reservation_list();
    IFBMemorySystemInfo&      system_info_ref      = ifb_memory::context_get_system_info(); 

    //get platform memory reservation
    const ifb_u32 page_size              = system_info_ref.page_size;
    const ifb_u64 allocation_granularity = system_info_ref.granularity;
    const ifb_u64 reservation_size       = ifb_macro_align_a_to_b(size_minimum,allocation_granularity);
    const ifb_u32 reservation_page_count = (ifb_u32)(reservation_size / page_size);
    const ifb_ptr reservation_start_ptr  = ifb_platform::memory_reserve(reservation_size);

    //sanity check
    if (!reservation_start_ptr) return({0});

    //allocate a reservation on the stack
    IFBMemoryReservationHandle reservation_handle;
    reservation_handle.offset = ifb_memory_macro_stack_push_struct(IFBMemoryReservation); 

    //get the reservation pointer
    IFBMemoryReservation* reservation_ptr = ifb_memory_macro_stack_get_type_pointer(
        reservation_handle.offset,
        IFBMemoryReservation);

    //sanity check
    ifb_macro_assert(reservation_ptr);

    //initialize the reservation
    reservation_ptr->offset               = reservation_handle.offset;
    reservation_ptr->next                 = NULL;
    reservation_ptr->start                = (ifb_address)reservation_start_ptr;
    reservation_ptr->page_count_total     = reservation_page_count;
    reservation_ptr->page_count_committed = 0;
    reservation_ptr->arena_list           = {0};

    //get reservation list status
    const ifb_b8 is_first_reservation = reservation_list_ref.count == 0; 

    //if this is the first reservation, initialize the list
    if (is_first_reservation) {

        //sanity check
        ifb_macro_assert(reservation_list_ref.first == NULL);
        ifb_macro_assert(reservation_list_ref.last  == NULL);

        //set the first and last element to the new reservation
        reservation_list_ref.first = reservation_ptr;
        reservation_list_ref.last  = reservation_ptr;
        reservation_list_ref.count = 1;
        
        //we're done
        return(reservation_handle);
    } 

    //otherwise, we need to add it to the end of the list
    //make sure the list has been initialized
    ifb_macro_assert(reservation_list_ref.first);
    ifb_macro_assert(reservation_list_ref.last);

    //add the new reservation to the end of the list
    reservation_list_ref.last->next = reservation_ptr;
    reservation_list_ref.last       = reservation_ptr;

    //update the count
    ++reservation_list_ref.count;

    //we're done
    return(reservation_handle);
}

ifb_internal inline const ifb_b8
ifb_memory::release(
    const IFBMemoryReservationHandle reservation_handle) {

    //get the reservation
    IFBMemoryReservation* reservation_ptr = ifb_memory::reservation_get_pointer_from_handle(reservation_handle);

    //get reservation start and size if we have it
    const ifb_ptr reservation_start = (ifb_ptr)reservation_ptr->start;
    const ifb_u64 reservation_size  = reservation_ptr->size;          

    //tell the platform to release the memory
    const ifb_b8 result = ifb_platform::memory_release(
        reservation_start,
        reservation_size);

    //we're done
    return(result);  
}

/**********************************************************************************/
/* ARENA COMMIT                                                                   */
/**********************************************************************************/

struct IFBReservationArenaCommitInfo {
    ifb_address commit_start;
    ifb_u32     size_requested;
    ifb_u32     size_actual;
    ifb_u32     page_start;
    ifb_u32     page_count;
    ifb_u32     page_offset;
};

ifb_internal inline const IFBMemoryArenaHandle       
ifb_memory::reservation_commit_arena(
    const IFBMemoryReservationHandle reservation_handle,
    const ifb_u32                    arena_size_minimum) {

    //get the reservation
    IFBMemoryReservation* reservation_ptr = ifb_memory::reservation_get_pointer_from_handle(reservation_handle);

    //page align the size
    const ifb_u32 arena_size = ifb_memory::context_align_size_to_page(arena_size_minimum);

    //get the start of the commit
    const ifb_u32     arena_page_number   = reservation_ptr->page_count_committed;
    const ifb_u32     arena_page_count    = ifb_memory::context_get_page_count_from_size(arena_size); 
    const ifb_u32     arena_page_offset   = ifb_memory::context_get_size_from_page_count(page_start_number); 
    const ifb_address arena_start_address = reservation_ptr->start + page_start_offset;
    const ifb_ptr     arena_start_pointer = (ifb_ptr)page_start_address; 

    //commit the arena size at the starting page
    const ifb_ptr arena_commit = ifb_platform::memory_commit(
        arena_start_pointer,
        arena_size);

    //sanity check
    if (arena_commit != arena_start_pointer) return({0});

    //allocate an arena on the stack
    const ifb_u32 stack_position = ifb_memory_macro_stack_push_struct(IFBMemoryArena);

    //get the arena pointer
    IFBMemoryArena* arena_ptr = ifb_memory_macro_stack_get_type_pointer(stack_position,IFBMemoryArena);
    ifb_macro_assert(arena_ptr);

    //create the handle
    IFBMemoryArenaHandle arena_handle;
    arena_handle.offset = stack_position;

    //initialize the arena
    arena_ptr->reservation    = reservation_ptr; 
    arena_ptr->next           = NULL;
    arena_ptr->type           = IFBMemoryArenaType_Base;
    arena_ptr->page_start     = arena_page_number;
    arena_ptr->page_count     = arena_page_count;
    arena_ptr->stack_position = stack_position;

    //add the arena to the list
    IFBMemoryArenaList& arena_list_ref = reservation_ptr->arena_list;

    //get the arena status
    const ifb_b8 is_first_arena  = arena_list_ref.count == 0;
    const ifb_b8 is_second_arena = arena_list_ref.count == 1;

    //if this is the first arena, we need to initialize the list 
    if (is_first_arena) {

        //sanity check
        //the list should be empty
        ifb_macro_assert(arena_list_ref.first == NULL);
        ifb_macro_assert(arena_list_ref.last  == NULL);

        //initialize the list
        arena_list_ref.first = arena_ptr;
        arena_list_ref.last  = arena_ptr;        
        arena_list_ref.count = 1;

        //we're done
        return(arena_handle);
    }

    //otherwise, add it to the end of the list
    //the lists should not be empty in this case
    ifb_macro_assert(arena_list_ref.first);
    ifb_macro_assert(arena_list_ref.last);

    //if this is the second element, we need to update the first pointer
    if (is_second_arena) {

        //there shouldn't be a pointer here
        ifb_macro_assert(arena_list_ref.first->next == NULL);
        arena_list_ref.first->next = arena_ptr;
    }

    //at this point, we should have a second pointer
    ifb_macro_assert(arena_list_ref.first->next);

    //add the arena to the end of the list
    arena_list_ref.last->next = arena_ptr;
    arena_list_ref.last       = arena_ptr;

    //update the count
    ++arena_list_ref.count;

    //we're done
    return(arena_handle);
}


ifb_internal inline const IFBMemoryLinearArenaHandle 
ifb_memory::reservation_commit_linear_arena(
    const IFBMemoryReservationHandle reservation_handle,
    const ifb_u32                    arena_size_minimum) {

    //commit the arena
    
}

ifb_internal inline const IFBMemoryBlockArenaHandle  
ifb_memory::reservation_commit_block_arena(
    const IFBMemoryReservationHandle reservation_handle,
    const ifb_u32                    block_size_minimum,
    const ifb_u32                    block_count) {

    //get the reservation
    IFBMemoryReservation* reservation_ptr = ifb_memory::reservation_get_pointer_from_handle(reservation_handle);



}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

ifb_internal inline IFBMemoryReservation* 
ifb_memory::reservation_get_pointer_from_handle(
    const IFBMemoryReservationHandle reservation_handle) {

    //get the stack
    IFBMemoryStack& stack_ref = ifb_memory::context_get_stack();

    //get the pointer
    IFBMemoryReservation* reservation_ptr = ifb_memory_macro_stack_get_type_pointer(
        reservation_handle.offset,
        IFBMemoryReservation);

    //sanity check
    ifb_macro_assert(reservation_ptr);

    //we're done
    return(reservation_ptr);
}