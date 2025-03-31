#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.cpp"

using namespace ifb;
using namespace ifb::memory;

memory_arena_t*
memory::arena_commit(
    memory_reservation_t* reservation) {

    //validate the reservation
    memory::validate_reservation(reservation);

    //get the stack
    memory_stack_t* stack = reservation->stack; 
    
    memory_arena_t* arena = NULL;
    //first, see if there is an arena on the list of decommitted arenas
    if (reservation->arenas.decommitted != NULL) {
        
        //if there is, we need to update the list
        arena = reservation->arenas.decommitted;
        memory_arena_t* new_first_arena = arena->next;
        new_first_arena->prev = NULL;
        reservation->arenas.decommitted = new_first_arena;
    }
    else {
        
        // otherwise, we need to do the following:
        //  1) push an arena on the stack
        //  2) determine the address
        
        //push the arena
        arena = macro_stack_push_arena(stack);
        ifb_macro_assert(arena);

        //determine the address
        arena->page_number = reservation->page_count_used;

    }
    
    //either way, we should have an arena
    ifb_macro_assert(arena);

    //calculate the commit parameters
    const u32  page_offset    = arena->page_number * reservation->sizes.page;
    const u32  page_count     = reservation->sizes.arena / reservation->sizes.page;
    const addr page_address   = reservation->start + page_offset;
    const ptr  commit_request = (ptr)page_address; 
    const u32  commit_size    = reservation->sizes.arena;

    //do the commit
    const ptr commit_result = platform::memory_commit(
        commit_request,
        commit_size);

    //sanity check
    ifb_macro_assert(commit_request == commit_result);

    //get the current committed arena list
    memory_arena_t* committed_arena_list = reservation->arenas.committed;
    
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

const b8
memory::arena_decommit(
    memory_arena_t* arena) {

    memory::validate_arena(arena);

    ifb_macro_panic();

    return(false);
}

const b8
memory::arena_reset(
    memory_arena_t* arena) {

    memory::validate_arena(arena);

    arena->position = 0;

    return(false);
}

const u32
memory::arena_push_bytes_relative(
    memory_arena_t*  arena,
    const u32 size) {

    memory::validate_arena(arena);
    ifb_macro_assert(size);

    //get the new arena size
    memory_reservation_t* reservation = arena->reservation;
    const u32 arena_size         = reservation->sizes.arena;
    const u32 arena_offset       = arena->position;
    const u32 arena_position_new = arena_offset + size;
    
    //make sure we can do the push
    ifb_macro_assert(arena_position_new < arena_size);

    //we're done
    //return the offset prior to the push
    return(arena_offset);
}

const ptr
memory::arena_push_bytes_absolute_pointer(
    memory_arena_t*  arena,
    const u32 size) {

    //validate args
    memory::validate_arena(arena);
    ifb_macro_assert(size);

    //get the new arena size
    memory_reservation_t* reservation = arena->reservation;
    const u32 arena_size         = reservation->sizes.arena;
    const u32 arena_offset       = arena->position;
    const u32 arena_position_new = arena_offset + size;

    //make sure we can do the push
    ifb_macro_assert(arena_position_new < arena_size);

    //get the pointer
    const addr result_address = arena->start + arena_offset;
    const ptr  result_pointer = (ptr)result_address;

    //update the arena position
    arena->position = arena_position_new;

    //we're done
    return(result_pointer);
}

const addr
memory::arena_push_bytes_absolute_address(
    memory_arena_t*  arena,
    const u32 size) {

    //validate args
    memory::validate_arena(arena);
    ifb_macro_assert(size);

    //get the new arena size
    memory_reservation_t* reservation        = arena->reservation;
    const u32      arena_size         = reservation->sizes.arena;
    const u32      arena_offset       = arena->position;
    const u32      arena_position_new = arena_offset + size;

    //make sure we can do the push
    ifb_macro_assert(arena_position_new < arena_size);

    //get the pointer
    const addr result_address = arena->start + arena_offset;

    //update the arena position
    arena->position = arena_position_new;

    //we're done
    return(result_address);
}

const b8
memory::arena_pull_bytes(
    memory_arena_t* arena,
    const u32    size) {

    //validate args
    memory::validate_arena(arena);
    ifb_macro_assert(size);

    ifb_macro_assert(arena->position > size);

    arena->position -= size;

    return(true);
}