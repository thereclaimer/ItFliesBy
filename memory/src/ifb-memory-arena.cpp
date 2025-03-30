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
    const ifb::u32  page_offset    = arena->page_number * reservation->sizes.page;
    const ifb::u32  page_count     = reservation->sizes.arena / reservation->sizes.page;
    const ifb::addr page_address   = reservation->start + page_offset;
    const ifb::ptr  commit_request = (ifb::ptr)page_address; 
    const ifb::u32  commit_size    = reservation->sizes.arena;

    //do the commit
    const ifb::ptr commit_result = ifb_platform::memory_commit(
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

const ifb::b8
ifb_memory::arena_decommit(
    IFBMemoryArena* arena) {

    ifb_memory::validate_arena(arena);

    ifb_macro_panic();

    return(false);
}

const ifb::b8
ifb_memory::arena_reset(
    IFBMemoryArena* arena) {

    ifb_memory::validate_arena(arena);

    arena->position = 0;

    return(false);
}


const ifb::u32
ifb_memory::arena_push_bytes_relative(
          IFBMemoryArena* arena,
    const ifb::u32          size) {

    ifb_memory::validate_arena(arena);
    ifb_macro_assert(size);

    //get the new arena size
    IFBMemoryReservation* reservation = arena->reservation;
    const ifb::u32 arena_size         = reservation->sizes.arena;
    const ifb::u32 arena_offset       = arena->position;
    const ifb::u32 arena_position_new = arena_offset + size;
    
    //make sure we can do the push
    ifb_macro_assert(arena_position_new < arena_size);

    //we're done
    //return the offset prior to the push
    return(arena_offset);
}

const ifb::ptr
ifb_memory::arena_push_bytes_absolute_pointer(
          IFBMemoryArena* arena,
    const ifb::u32          size) {

    //validate args
    ifb_memory::validate_arena(arena);
    ifb_macro_assert(size);

    //get the new arena size
    IFBMemoryReservation* reservation = arena->reservation;
    const ifb::u32 arena_size         = reservation->sizes.arena;
    const ifb::u32 arena_offset       = arena->position;
    const ifb::u32 arena_position_new = arena_offset + size;

    //make sure we can do the push
    ifb_macro_assert(arena_position_new < arena_size);

    //get the pointer
    const ifb::addr result_address = arena->start + arena_offset;
    const ifb::ptr  result_pointer = (ifb::ptr)result_address;

    //update the arena position
    arena->position = arena_position_new;

    //we're done
    return(result_pointer);
}

const ifb::addr
ifb_memory::arena_push_bytes_absolute_address(
          IFBMemoryArena* arena,
    const ifb::u32          size) {

    //validate args
    ifb_memory::validate_arena(arena);
    ifb_macro_assert(size);

    //get the new arena size
    IFBMemoryReservation* reservation = arena->reservation;
    const ifb::u32 arena_size         = reservation->sizes.arena;
    const ifb::u32 arena_offset       = arena->position;
    const ifb::u32 arena_position_new = arena_offset + size;

    //make sure we can do the push
    ifb_macro_assert(arena_position_new < arena_size);

    //get the pointer
    const ifb::addr result_address = arena->start + arena_offset;

    //update the arena position
    arena->position = arena_position_new;

    //we're done
    return(result_address);
}

const ifb::b8
ifb_memory::arena_pull_bytes(
          IFBMemoryArena* arena,
    const ifb::u32          size) {

    //validate args
    ifb_memory::validate_arena(arena);
    ifb_macro_assert(size);

    ifb_macro_assert(arena->position > size);

    arena->position -= size;

    return(true);
}