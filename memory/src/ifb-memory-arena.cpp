#pragma once

#include "ifb-memory-internal.hpp"

//arena commit
const IFBHNDArena
ifb_memory::reservation_commit_arena(
    const IFBHNDReservation reservation_handle,
    const IFBU32            size_minimum) {

    IFBHNDArena arena_handle;
    arena_handle.offset = 0;

    //sanity check
    IFBB8 result = true;
    result &= reservation_handle.offset != 0;
    result &= size_minimum              != 0;
    if (!result) return(arena_handle);

    //get the reservation
    IFBReservation* ptr_reservation = ifb_memory::context_get_reservation(reservation_handle); 
    ifb_macro_assert(ptr_reservation);

    //align the size
    const IFBU32 page_size   = ptr_reservation->page_size;
    const IFBU32 commit_size = ifb_macro_align_a_to_b(size_minimum,page_size);
    const IFBU32 page_count  = size_aligned / page_size;
    
    //calculate the commit start
    const IFBU32  commit_offset     = ptr_reservation->page_count_committed * page_size; 
    const IFBAddr commit_start_addr = ptr_reservation->start                + commit_offset;
    const IFBPtr  commit_start_ptr  = (IFBPtr)commit_address;

    //do the commit
    const IFBPtr commit_result = ifb_platform::memory_commit(
        commit_start_ptr,
        commit_size);
    
    //make sure we got the expected result
    if (commit_result != commit_start) return(arena_handle);

    //search the list for arenas to recycle
    IFBArenaList* ptr_arena_list = ifb_memory::context_get_arena_list();
    IFBArena*     ptr_arena      = NULL;
    for (
        IFBArena* ptr_arena_current = ptr_arena_list->first;
        ptr_arena_current != NULL;
        ptr_arena_current = ptr_arena_current->next) {
            
        //if the arena has no reservation and no start address
        //it is free to use
        IFBB8 arena_is_free = true;
        arena_is_free &= (ptr_arena_current->handle_reservation.offset == 0);
        arena_is_free &= (ptr_arena_current->start                     == 0);
        if (arena_is_free) {
            ptr_arena = ptr_arena_current;
            break;
        }
    }
    
    //if we didn't find an arena struct, we need to commit a new one
    if (!ptr_arena) {

        //commit reservation structure
        const IFBU32 arena_struct_size = ifb_macro_align_size_struct(IFBArena); 
        arena_handle.offset            = ifb_memory::context_stack_commit_relative(arena_struct_size);
        
        //get the pointer
        ptr_arena = ifb_memory::context_get_arena(arena_handle);
    }
     
    //we should always have an arena at this point
    ifb_macro_assert(ptr_arena);

    //initialize the arena
    ptr_arena->handle_reservation = reservation_handle;
    ptr_arena->handle_arena       = arena_handle;
    ptr_arena->ptr_next           = NULL;
    ptr_arena->start              = (IFBAddr)commit_result;
    ptr_arena->size               = commit_size;
    ptr_arena->position           = 0;
    
    //if this is the first one, we need to initialize the list
    if (ptr_arena_list->count == 0) {

        //pointers should be null
        ifb_macro_assert(ptr_arena_list->first == NULL);
        ifb_macro_assert(ptr_arena_list->last  == NULL);

        //initialize the list
        ptr_arena_list->first = ptr_arena;
        ptr_arena_list->last  = ptr_arena;
        ptr_arena_list->count = 1;
    }
    else {

        //first and last elements should NOT be null
        ifb_macro_assert(ptr_arena_list->first);
        ifb_macro_assert(ptr_arena_list->last);
        
        //cache first and last elements
        IFBArena* first_element = ptr_arena_list->first; 
        IFBArena* last_element  = ptr_arena_list->last; 
        
        //if we are adding a second element, make sure
        //we update the next pointer for the first element
        if (ptr_arena_list->count == 1) {
            ifb_macro_assert(first_element->next == NULL);
            first_element->next = ptr_arena;
        }
        
        //update the end of the list
        ifb_macro_assert(first_element->next);
        last_element->next   = ptr_arena;
        ptr_arena_list->last = ptr_arena;

        //update the count
        ++ptr_arena_list->count;                        
    }

    //update the reservation
    ptr_reservation->page_count_committed + page_count;

    //we're done
    return(arena_handle);
}

//info
const IFBB8
ifb_memory::reservation_get_info(
    const IFBHNDReservation   reservation_handle,
          IFBReservationInfo* reservation_info_ptr) {

    //sanity check
    if (!reservation_info_ptr) return(false);

    //get the reservation
    IFBReservation* ptr_reservation = ifb_memory::context_get_reservation(reservation_handle); 
    ifb_macro_assert(ptr_reservation);    

    //set the info
    const IFBU32 page_size = ptr_reservation->page_size;
    reservation_info_ptr->page_count_total     = ptr_reservation->page_count_total;
    reservation_info_ptr->page_count_committed = ptr_reservation->page_count_committed;
    reservation_info_ptr->size_total           = ptr_reservation->page_count_total     * page_size;
    reservation_info_ptr->size_committed       = ptr_reservation->page_count_committed * page_size;

    //we're done
    return(true);
}