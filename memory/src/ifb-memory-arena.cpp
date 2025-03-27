
#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.cpp"

IFBMemoryArena*
ifb_memory::arena_commit(
    const IFBMemoryReservation* reservation) {

    ifb_memory::validate_reservation(reservation);

    //get the stack
    const IFBAddr   address_reservation = (IFBAddr)reservation;
    const IFBAddr   address_stack       = address_reservation - reservation->stack_offset; 
    IFBMemoryStack* stack               = (IFBMemoryStack*)address_stack;

    //first, see if there is an arena on the list of decommitted arenas
    IFBMemoryArena* arena = reservation->arenas_decommitted;
    if (arena) {
        
        //if there is, we need to update the list
        IFBMemoryArena* new_first_arena = arena->next;
        new_first_arena->prev = NULL;
        reservation->arenas_decommitted = new_first_arena;

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
    const IFBU32  page_offset    = page_number * reservation->size_page;
    const IFBAddr page_address   = reservation->system_memory_start + page_offset;
    const IFBPtr  commit_request = (IFBPtr)page_address; 
    const IFBU32  commit_size    = reservation->size_arena;

    //do the commit
    const IFBPtr commit_result = ifb_platform::memory_commit(
        commit_request
        commit_size);

    //sanity check
    ifb_macro_assert(commit_request == commit_result);

    //get the current committed arena list
    IFBMemoryArena* committed_arena_list = reservation->arenas_committed;
    
    //initialize the arena
    arena->prev               = NULL;
    arena->reservation_offset = (IFBAddr)arena - address_reservation;
    arena->position           = 0;

    //add the arena to the front of the committed list
    if (committed_arena_list) {
        committed_arena_list->prev = arena;
    }

    arena->next = committed_arena_list;
    reservation->arenas_committed = arena;

    //we're done
    return(arena);
}

const IFBB8
ifb_memory::arena_decommit(
    IFBMemoryArena* arena) {
  
    //set the args
    IFBMemoryArenaDecommit decommit;
    decommit.context = &arena_context;

    //do the decommit
    ifb_memory::arena_decommit_step_0_validate_args                (decommit);
    ifb_memory::arena_decommit_step_1_cache_reservation_properties (decommit);
    ifb_memory::arena_decommit_step_2_load_arena_start_array       (decommit);
    ifb_memory::arena_decommit_step_3_decommit_memory              (decommit);
    ifb_memory::arena_decommit_step_4_update_arena_start_array     (decommit);

    //we're done
    return(decommit.result ? true : false);
}

const IFBB8
ifb_memory::arena_reset(
    IFBMemoryArena* arena) {

    //set the args
    IFBMemoryArenaReset reset;
    reset.context = &arena_context;

    //do the reset
    ifb_memory::arena_reset_step_0_validate_args    (reset);
    ifb_memory::arena_reset_step_1_cache_properties (reset);
    ifb_memory::arena_reset_step_2_reset_arena      (reset);

    //we're done
    return(reset.result ? true : false);
}


const IFBU32
ifb_memory::arena_push_bytes_relative(
          IFBMemoryArena* arena,
    const IFBU32          size) {

    //set the args
    IFBMemoryArenaPushBytes push;
    push.context = &arena_context;

    //do the push
    ifb_memory::arena_push_step_0_validate_args                (push);
    ifb_memory::arena_push_step_1_cache_reservation_properties (push);
    ifb_memory::arena_push_step_2_push_bytes_relative          (push);

    //get the offset
    const IFBU32 offset = push.result
        ? push.memory.relative_offset
        : IFB_MEMORY_INVALID_HANDLE_32;

    //we're done
    return(offset);
}

const IFBPtr
ifb_memory::arena_push_bytes_absolute(
          IFBMemoryArena* arena,
    const IFBU32           size) {

    //set the args
    IFBMemoryArenaPushBytes push;
    push.context = &arena_context;

    //do the push
    ifb_memory::arena_push_step_0_validate_args                (push);
    ifb_memory::arena_push_step_1_cache_reservation_properties (push);
    ifb_memory::arena_push_step_2_push_bytes_absolute          (push);

    //get the pointer
    const IFBPtr pointer = push.result
        ? push.memory.absolute_pointer
        : NULL;

    //we're done
    return(pointer);
}

const IFBB8
ifb_memory::arena_pull_bytes(
          IFBMemoryArena* arena,
    const IFBU32          size) {

    //set the args
    IFBMemoryArenaPullBytes pull;
    pull.context = &arena_context;

    //do the pull
    ifb_memory::arena_pull_step_0_validate_args    (pull);
    ifb_memory::arena_pull_step_1_cache_properties (pull);
    ifb_memory::arena_pull_step_2_pull_bytes       (pull);

    //we're done
    return(pull.result ? true : false);
}
