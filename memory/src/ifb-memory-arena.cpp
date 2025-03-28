#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.cpp"

IFBMemoryArena*
ifb_memory::arena_commit(
    IFBMemoryReservation* reservation) {

    //validate the reservation
    ifb_memory::validate_reservation(reservation);

    //get the stack
    IFBMemoryStack* stack = reservation->stack; 
    
    IFBMemoryArena* arena = NULL;
    //first, see if there is an arena on the list of decommitted arenas
    if (reservation->arenas.decommitted != NULL) {
        
        //if there is, we need to update the list
        arena = reservation->arenas.decommitted;
        IFBMemoryArena* new_first_arena = arena->next;
        new_first_arena->prev = NULL;
        reservation->arenas.decommitted = new_first_arena;
    }
    else {
        
        // otherwise, we need to do the following:
        //  1) push an arena on the stack
        //  2) determine the address
        
        //push the arena
        arena = ifb_memory_macro_stack_push_arena(stack);
        ifb_macro_assert(arena);

        //determine the address
        arena->page_number = reservation->page_count_used;

    }
    
    //either way, we should have an arena
    ifb_macro_assert(arena);

    //calculate the commit parameters
    const IFBU32  page_offset    = arena->page_number * reservation->sizes.page;
    const IFBU32  page_count     = reservation->sizes.arena / reservation->sizes.page;
    const IFBAddr page_address   = reservation->start + page_offset;
    const IFBPtr  commit_request = (IFBPtr)page_address; 
    const IFBU32  commit_size    = reservation->sizes.arena;

    //do the commit
    const IFBPtr commit_result = ifb_platform::memory_commit(
        commit_request,
        commit_size);

    //sanity check
    ifb_macro_assert(commit_request == commit_result);

    //get the current committed arena list
    IFBMemoryArena* committed_arena_list = reservation->arenas.committed;
    
    //initialize the arena
    arena->prev        = NULL;
    arena->reservation = reservation; 
    arena->position    = 0;
    arena->start       = page_address; 

    //add the arena to the front of the committed list
    if (committed_arena_list) {
        committed_arena_list->prev = arena;
    }
    arena->next = committed_arena_list;
    reservation->arenas.committed = arena;

    //update the pages used
    reservation->page_count_used += page_count; 

    //we're done
    return(arena);
}

const IFBB8
ifb_memory::arena_decommit(
    IFBMemoryArena* arena) {

    ifb_memory::validate_arena(arena);

    ifb_macro_panic();

    return(false);
}

const IFBB8
ifb_memory::arena_reset(
    IFBMemoryArena* arena) {

    ifb_memory::validate_arena(arena);

    arena->position = 0;

    return(false);
}


const IFBU32
ifb_memory::arena_push_bytes_relative(
          IFBMemoryArena* arena,
    const IFBU32          size) {

    ifb_memory::validate_arena(arena);
    ifb_macro_assert(size);

    //get the new arena size
    IFBMemoryReservation* reservation = arena->reservation;
    const IFBU32 arena_size         = reservation->sizes.arena;
    const IFBU32 arena_offset       = arena->position;
    const IFBU32 arena_position_new = arena_offset + size;
    
    //make sure we can do the push
    ifb_macro_assert(arena_position_new < arena_size);

    //we're done
    //return the offset prior to the push
    return(arena_offset);
}

const IFBPtr
ifb_memory::arena_push_bytes_absolute(
          IFBMemoryArena* arena,
    const IFBU32          size) {

    //validate args
    ifb_memory::validate_arena(arena);
    ifb_macro_assert(size);

    //get the new arena size
    IFBMemoryReservation* reservation = arena->reservation;
    const IFBU32 arena_size         = reservation->sizes.arena;
    const IFBU32 arena_offset       = arena->position;
    const IFBU32 arena_position_new = arena_offset + size;

    //make sure we can do the push
    ifb_macro_assert(arena_position_new < arena_size);

    //get the pointer
    const IFBAddr result_address = arena->start + arena_offset;
    const IFBPtr  result_pointer = (IFBPtr)result_address;

    //we're done
    return(result_pointer);
}

const IFBB8
ifb_memory::arena_pull_bytes(
          IFBMemoryArena* arena,
    const IFBU32          size) {

    //validate args
    ifb_memory::validate_arena(arena);
    ifb_macro_assert(size);

    ifb_macro_assert(arena->position > size);

    arena->position -= size;

    return(true);
}