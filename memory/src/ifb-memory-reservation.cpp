#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryReservationPageCommit {
    ifb_address commit_start;
    ifb_u32     size_requested;
    ifb_u32     size_actual;
    ifb_u32     page_start;
    ifb_u32     page_count;
    ifb_u32     page_offset;
};

namespace ifb_memory {

    inline IFBMemoryReservation* reservation_handle_to_pointer (const IFBMemoryReservationHandle reservation_handle);
    inline ifb_b8                reservation_commit_pages            (IFBMemoryReservation*            reservation_ptr,      IFBMemoryReservationPageCommit& page_commit_ref);
    inline ifb_void              reservation_arena_list_add          (IFBMemoryReservationList&        reservation_list_ref, IFBMemoryArena*                 arena_ptr);
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
    IFBMemoryReservation* reservation_ptr = ifb_memory::reservation_handle_to_pointer(reservation_handle);

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

ifb_internal inline const IFBMemoryArenaHandle       
ifb_memory::reservation_commit_arena(
    const IFBMemoryReservationHandle reservation_handle,
    const ifb_u32                    arena_size_minimum) {

    //get the reservation
    IFBMemoryReservation* reservation_ptr = ifb_memory::reservation_handle_to_pointer(reservation_handle);

    //create the handle
    IFBMemoryArenaHandle arena_handle = {0};

    //commit the pages
    IFBMemoryReservationPageCommit page_commit;
    page_commit.size_requested = arena_size_minimum;
    const ifb_b8 commit_result = ifb_memory::reservation_commit_pages(reservation_ptr,page_commit);

    //if that failed, we're done
    if (!commit_result) return(arena_handle);

    //allocate a base arena on the stack
    arena_handle.offset       = ifb_memory_macro_stack_push_struct      (IFBMemoryArena);
    IFBMemoryArena* arena_ptr = ifb_memory_macro_stack_get_type_pointer (arena_handle.offset,IFBMemoryArena);
    ifb_macro_assert(arena_ptr);

    //initialize the arena
    arena_ptr->start          = page_commit.commit_start; 
    arena_ptr->reservation    = reservation_ptr; 
    arena_ptr->next           = NULL;
    arena_ptr->type           = IFBMemoryArenaType_Base;
    arena_ptr->page_start     = page_commit.page_start;
    arena_ptr->page_count     = page_commit.page_count;
    arena_ptr->size_total     = page_commit.size_actual; 
    arena_ptr->stack_position = arena_handle.offset;

    //add the arena to the list
    ifb_memory::reservation_arena_list_add(reservation_ptr,arena_ptr);
    
    //we're done
    return(arena_handle);
}

ifb_internal inline const IFBMemoryLinearArenaHandle 
ifb_memory::reservation_commit_linear_arena(
    const IFBMemoryReservationHandle reservation_handle,
    const ifb_u32                    arena_size_minimum) {

    //get the reservation
    IFBMemoryReservation* reservation_ptr = ifb_memory::reservation_handle_to_pointer(reservation_handle);

    //create the handle
    IFBMemoryLinearArenaHandle linear_arena_handle = {0};

    //commit the pages
    IFBMemoryReservationPageCommit page_commit;
    page_commit.size_requested = arena_size_minimum;
    const ifb_b8 commit_result = ifb_memory::reservation_commit_pages(reservation_ptr,page_commit);

    //if that failed, we're done
    if (!commit_result) return(arena_handle);

    //allocate a base arena on the stack
    linear_arena_handle.offset             = ifb_memory_macro_stack_push_struct      (IFBMemoryLinearArena);
    IFBMemoryLinearArena* linear_arena_ptr = ifb_memory_macro_stack_get_type_pointer (linear_arena_handle.offset,IFBMemoryLinearArena);
    ifb_macro_assert(linear_arena_ptr);

    //initialize the arena
    linear_arena_ptr->start          = page_commit.commit_start; 
    linear_arena_ptr->reservation    = reservation_ptr; 
    linear_arena_ptr->next           = NULL;
    linear_arena_ptr->type           = IFBMemoryArenaType_Linear;
    linear_arena_ptr->page_start     = page_commit.page_start;
    linear_arena_ptr->page_count     = page_commit.page_count;
    linear_arena_ptr->size_total     = page_commit.size_actual; 
    linear_arena_ptr->stack_position = linear_arena_handle.offset;
    linear_arena_ptr->position       = 0;
    linear_arena_ptr->save_point     = 0;

    //add the arena to the list
    ifb_memory::reservation_arena_list_add(reservation_ptr,linear_arena_ptr);
    
    //we're done
    return(linear_arena_handle);
}

ifb_internal inline const IFBMemoryBlockArenaHandle  
ifb_memory::reservation_commit_block_arena(
    const IFBMemoryReservationHandle reservation_handle,
    const ifb_u32                    block_size_minimum,
    const ifb_u32                    block_count) {

    //get the reservation
    IFBMemoryReservation* reservation_ptr = ifb_memory::reservation_handle_to_pointer(reservation_handle);

    //create the handle
    IFBMemoryBlockArenaHandle block_arena_handle = {0};

    //get the actual size of the arena
    const ifb_u32 block_size_actual = ifb_memory::context_align_size_to_page(block_size_minimum);
    const ifb_u32 size_requested    = block_count * block_size_actual;   
    
    //commit the pages
    IFBMemoryReservationPageCommit page_commit;
    page_commit.size_requested = size_requested;
    const ifb_b8 commit_result = ifb_memory::reservation_commit_pages(reservation_ptr,page_commit);

    //if that failed, we're done
    if (!commit_result) return(arena_handle);

    //calculate the allocation size
    const ifb_u32 block_arena_struct_size  = ifb_macro_align_size_struct(IFBMemoryBlockArena);
    const ifb_u32 block_address_array_size = ifb_macro_size_array(ifb_address,block_count); 
    const ifb_u32 push_size_total          = block_arena_struct_size + block_address_array_size;

    //allocate a base arena on the stack
    block_arena_handle.offset = ifb_memory::stack_push(push_size_total);

    //get the pointers
    IFBMemoryBlockArena* block_arena_ptr     = ifb_memory_macro_stack_get_type_pointer(block_arena_handle.offset,                           IFBMemoryBlockArena);
    ifb_address*         block_address_array = ifb_memory_macro_stack_get_type_pointer(block_arena_handle.offset + block_arena_struct_size, ifb_address);

    //sanity check
    ifb_macro_assert(block_arena_ptr);
    ifb_macro_assert(block_address_array);

    //initialize the arena
    block_arena_ptr->start               = page_commit.commit_start; 
    block_arena_ptr->reservation         = reservation_ptr; 
    block_arena_ptr->next                = NULL;
    block_arena_ptr->type                = IFBMemoryArenaType_Block;
    block_arena_ptr->page_start          = page_commit.page_start;
    block_arena_ptr->page_count          = page_commit.page_count;
    block_arena_ptr->size_total          = page_commit.size_actual; 
    block_arena_ptr->stack_position      = block_arena_handle.offset;
    block_arena_ptr->block_address_array = block_address_array;
    block_arena_ptr->block_count         = block_count;
    block_arena_ptr->block_size          = block_size_actual;

    //add the arena to the list
    ifb_memory::reservation_arena_list_add(reservation_ptr,block_arena_ptr);
    
    //we're done
    return(block_arena_handle);
}

/**********************************************************************************/
/* INFO                                                                           */
/**********************************************************************************/

ifb_internal inline const ifb_b8
ifb_memory::reservation_get_info(
    const IFBMemoryReservationHandle reservation_handle,
          IFBMemoryReservationInfo*  reservation_info_ptr) {

    //get the reservation
    IFBMemoryReservation* reservation_ptr = ifb_memory::reservation_handle_to_pointer(reservation_handle);

    //sanity check
    if (!reservation_info_ptr) return(false);

    //calculate sizes
    const ifb_u32 page_count_total     = reservation_ptr->page_count_total;
    const ifb_u32 page_count_committed = reservation_ptr->page_count_committed;
    const ifb_u32 size_total           = ifb_memory::context_get_size_from_page_count(page_count_total);
    const ifb_u32 size_committed       = ifb_memory::context_get_size_from_page_count(page_count_committed);

    //set reservation into
    reservation_info_ptr->page_count_total     = page_count_total;
    reservation_info_ptr->page_count_committed = page_count_committed;
    reservation_info_ptr->size_total           = size_total;
    reservation_info_ptr->size_committed       = size_committed;
    reservation_info_ptr->arena_count          = reservation_ptr->arena_list.count;

    //we're done
    return(true);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

ifb_internal inline IFBMemoryReservation* 
ifb_memory::reservation_handle_to_pointer(
    const IFBMemoryReservationHandle reservation_handle) {

    //get the pointer
    IFBMemoryReservation* reservation_ptr = ifb_memory_macro_stack_get_type_pointer(
        reservation_handle.offset,
        IFBMemoryReservation);

    //sanity check
    ifb_macro_assert(reservation_ptr);

    //we're done
    return(reservation_ptr);
}

ifb_internal inline ifb_b8
ifb_memory::reservation_page_commit(
    IFBMemoryReservation*           reservation_ptr,
    IFBMemoryReservationPageCommit& page_commit_ref) {

    ifb_macro_assert(reservation_ptr);

    //get the start of the commit
    const ifb_u32     commit_size_requested  = page_commit_ref.size_requested;
    const ifb_u32     commit_size_actual     = ifb_memory::context_align_size_to_page(arena_size_minimum);
    const ifb_u32     page_number            = reservation_ptr->page_count_committed;
    const ifb_u32     page_count             = ifb_memory::context_get_page_count_from_size(size_actual); 
    const ifb_u32     page_offset            = ifb_memory::context_get_size_from_page_count(page_start_number); 
    const ifb_address commit_start           = reservation_ptr->start + page_start_offset;
    const ifb_ptr     commit_request_pointer = (ifb_ptr)page_start_address; 

    //make sure the reservation can fit this commit
    const ifb_u32 new_page_commit_count = reservation_ptr->page_count_committed + page_count;
    
    //if we can't, we're done
    if (new_page_commit_count > reservation_ptr->page_count_total) return(false);

    //commit the arena size at the starting page
    const ifb_ptr commit_result_pointer = ifb_platform::memory_commit(
        commit_request_pointer,
        commit_size_actual);

    //sanity check
    if (commit_result_pointer != commit_request_pointer) return(false);

    //update the page commit struct
    page_commit_ref.commit_start = commit_start; 
    page_commit_ref.size_actual  = commit_size_actual; 
    page_commit_ref.page_start   = page_number; 
    page_commit_ref.page_count   = page_count; 
    page_commit_ref.page_offset  = page_offset;

    //update the page commit count
    reservation_ptr->page_count_committed = new_page_commit_count;

    //we're done
    return(true); 
}

ifb_internal inline ifb_void
ifb_memory::reservation_arena_list_add(
    IFBMemoryReservation* reservation_ptr,
    IFBMemoryArena*       arena_ptr) {

    //sanity check
    ifb_macro_assert(reservation_ptr);

    //get the arena list
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
        return;
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
}