#pragma once

#include "ifb-memory-internal.hpp"

/**********************************************************************************/
/* RESET                                                                          */
/**********************************************************************************/

IFBVoid
ifb_memory::arena_reset_all(
    const IFBHNDArena arena_handle) {

    IFBArena* ptr_arena = ifb_memory::context_get_arena(arena_handle);

    ptr_arena->position_committed = 0;
    ptr_arena->position_reserved  = 0;
}

IFBVoid
ifb_memory::arena_reset_committed_space(
    const IFBHNDArena arena_handle) {

    IFBArena* ptr_arena = ifb_memory::context_get_arena(arena_handle);

    ptr_arena->position_committed = 0;
}

IFBVoid
ifb_memory::arena_reset_reserved_space(
    const IFBHNDArena arena_handle) {

    IFBArena* ptr_arena = ifb_memory::context_get_arena(arena_handle);

    ptr_arena->position_reserved = 0;
}

/**********************************************************************************/
/* POINTERS                                                                       */
/**********************************************************************************/

const IFBPtr
ifb_memory::arena_get_pointer(
    const IFBHNDArena arena_handle,
    const IFBU32      offset) {

    //get the arena
    IFBArena* ptr_arena = ifb_memory::context_get_arena(arena_handle);
    
    //calculate the pointer, if its valid
    const IFBAddr address = ptr_arena->start + offset;
    const IFBPtr  pointer = offset < ptr_arena->size
        ? (IFBPtr)address
        : NULL;

    //we're done
    return(pointer);
}

const IFBB8
ifb_memory::arena_get_info(
    const IFBHNDArena   arena_handle,
          IFBArenaInfo* arena_info_ptr) {

    return(false);
}

const IFBAddr
ifb_memory::arena_get_start(
    const IFBHNDArena arena_handle) {

    //get the arena
    IFBArena* ptr_arena = ifb_memory::context_get_arena(arena_handle);

    //get the start address
    const IFBAddr start = ptr_arena->start;

    //we're done
    return(start);
}

/**********************************************************************************/
/* RESERVE/RELEASE (BOTTOM -> TOP)                                                */
/**********************************************************************************/

const IFBPtr
ifb_memory::arena_reserve_bytes_absolute(
    const IFBHNDArena arena_handle,
    const IFBU32      size,
    const IFBU32      alignment) {

    IFBPtr ptr_result = NULL;
    
    //get the arena
    IFBArena* ptr_arena = ifb_memory::context_get_arena(arena_handle);
    
    //sanity check
    if (size == 0) return(NULL);

    //calculate the new reserved position
    const IFBU32 reservation_size_aligned     = ifb_macro_align_a_to_b(size,alignment);
    const IFBU32 reservation_position_current = ptr_arena->position_reserved;
    const IFBU32 reservation_position_new     = reservation_position_current + reservation_size_aligned;
        
    //calculate the address
    const IFBAddr reservation_address = ptr_arena->start + reservation_position_current;
    
    //this reservation is valid IF...
    IFBB8 is_valid = true;
    is_valid &= (reservation_position_new < ptr_arena->size);               // it doesn't overflow the arena
    is_valid &= (reservation_position_new < ptr_arena->position_committed); // it doesn't overflow into commit space

    //if its valid, update the position and calculate the pointer
    if (is_valid) {
        ptr_arena->position_reserved = reservation_position_new;
        ptr_result = (IFBPtr)reservation_address;
    }

    //we're done
    return(ptr_result);
}

const IFBU32
ifb_memory::arena_reserve_bytes_relative(
    const IFBHNDArena arena_handle,
    const IFBU32      size,
    const IFBU32      alignment) {
        
    //get the arena
    IFBArena* ptr_arena = ifb_memory::context_get_arena(arena_handle);
    
    //we use the arena size as an invalid offset since using it will return null
    IFBU32 offset_result = ptr_arena->size;
    
    //sanity check
    if (size == 0) return(offset_result);
    
    //calculate the new reserved position
    const IFBU32 reservation_size_aligned     = ifb_macro_align_a_to_b(size,alignment);
    const IFBU32 reservation_position_current = ptr_arena->position_reserved;
    const IFBU32 reservation_position_new     = reservation_position_current + reservation_size_aligned;
    
    //this reservation is valid IF...
    IFBB8 is_valid = true;
    is_valid &= (reservation_position_new < ptr_arena->size);               // it doesn't overflow the arena
    is_valid &= (reservation_position_new < ptr_arena->position_committed); // it doesn't overflow into commit space

    //if its valid, update the position and offset
    //the offset is the position prior to the update
    if (is_valid) {
        ptr_arena->position_reserved = reservation_position_new;
        offset_result = reservation_position_current; 
    }

    //we're done
    return(offset_result);
}

const IFBB8
ifb_memory::arena_release_bytes(
    const IFBHNDArena arena_handle,
    const IFBU32      size,
    const IFBU32      alignment) {

    //get the arena
    IFBArena* ptr_arena = ifb_memory::context_get_arena(arena_handle);
    
    //determine if we can release the bytes
    //we can release if we aren't releasing more than we have reserved
    const IFBU32 release_size_aligned = ifb_macro_align_a_to_b(size,alignment);
    IFBB8        release_is_valid     = release_size_aligned < ptr_arena->position_reserved;

    //if we can release, update the arena
    if (release_is_valid) {
        ptr_arena->position_reserved -= release_size_aligned;
    }

    //we're done
    return(release_is_valid);
}

/**********************************************************************************/
/* COMMIT (BOTTOM <- TOP)                                                         */
/**********************************************************************************/

const IFBPtr 
ifb_memory::arena_commit_bytes_absolute(
    const IFBHNDArena arena_handle,
    const IFBU32      size,
    const IFBU32      alignment) {

    IFBPtr ptr_commit_result = NULL;

    //get the arena
    IFBArena* ptr_arena = ifb_memory::context_get_arena(arena_handle);

    //determine if we can commit
    //we can commit if the commit size is smaller than the difference
    //between the committed and reserved space
    const IFBU32 commit_size_aligned      = ifb_macro_align_a_to_b(size,alignment);
    const IFBU32 commit_position_current  = ptr_arena->position_committed;
    const IFBU32 reserve_position_current = ptr_arena->position_reserved;
    const IFBU32 position_difference      = commit_position_current - reserve_position_current; 
    const IFBU32 commit_is_valid          = commit_size_aligned < position_difference;

    //if we can do the commit, 
    //update the position and pointer
    if (commit_is_valid) {

        //calculate the address
        const IFBU32  commit_position_new = commit_position_current - commit_size_aligned; 
        const IFBAddr commit_address      = commit_position_new     + ptr_arena->start; 
        ptr_commit_result = (IFBPtr)commit_address;

        //update the arena
        ptr_arena->position_committed = commit_position_new;
    }

    //we're done
    return(ptr_commit_result);
}

const IFBU32 
ifb_memory::arena_commit_bytes_relative(
    const IFBHNDArena arena_handle,
    const IFBU32      size,
    const IFBU32      alignment) {
        
    //get the arena
    IFBArena* ptr_arena = ifb_memory::context_get_arena(arena_handle);
    
    //we use the arena size as an invalid offset since using it will return null
    IFBU32 offset_result = ptr_arena->size;

    //determine if we can commit
    //we can commit if the commit size is smaller than the difference
    //between the committed and reserved space
    const IFBU32 commit_size_aligned      = ifb_macro_align_a_to_b(size,alignment);
    const IFBU32 commit_position_current  = ptr_arena->position_committed;
    const IFBU32 reserve_position_current = ptr_arena->position_reserved;
    const IFBU32 position_difference      = commit_position_current - reserve_position_current; 
    const IFBU32 commit_is_valid          = commit_size_aligned < position_difference;

    //if we can do the commit, 
    //update the position and pointer
    if (commit_is_valid) {

        //calculate the offset
        offset_result = commit_position_current - commit_size_aligned; 

        //update the arena
        ptr_arena->position_committed = offset_result;
    }

    //we're done
    return(offset_result);
}