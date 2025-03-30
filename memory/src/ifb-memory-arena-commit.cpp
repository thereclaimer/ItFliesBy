#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-reservation.cpp"

/**********************************************************************************/
/* ARENA COMMIT STEPS                                                             */
/**********************************************************************************/

inline void 
ifb_memory::arena_commit_step_0_validate_args(
    IFBMemoryArenaCommit& commit_ref) {

    ifb_macro_assert(commit_ref.context);

    //initial values
    commit_ref.result  = true;
    commit_ref.result &= ifb_memory_macro_is_handle_valid_stack   (commit_ref.context->handle_stack);
    commit_ref.result &= ifb_memory_macro_is_handle_valid_reservation (commit_ref.context->handle_reservation);
}

inline void
ifb_memory::arena_commit_step_1_cache_reservation_properties(
    IFBMemoryArenaCommit& commit_ref) {

    if (commit_ref.result) {

        //get the memory reservation
        IFBMemoryReservation* reservation_internal = ifb_memory::reservation_load_and_assert_valid(
            commit_ref.context->handle_stack,
            commit_ref.context->handle_reservation);

        //load the arrays
        ifb_memory::reservation_load_arrays(reservation_internal,&commit_ref.cache.arrays);
        
        //cache the other properties
        commit_ref.cache.reservation_start = reservation_internal->reserved_memory_start;
        commit_ref.cache.arena_count       = reservation_internal->count_arenas;
        commit_ref.cache.arena_size        = reservation_internal->size_arena;
    
        //make sure the properties are non-zero
        commit_ref.result &= (commit_ref.cache.reservation_start     != 0);
        commit_ref.result &= (commit_ref.cache.arrays.arena_start    != NULL);
        commit_ref.result &= (commit_ref.cache.arrays.arena_position != NULL);
        commit_ref.result &= (commit_ref.cache.arena_count           != 0);
        commit_ref.result &= (commit_ref.cache.arena_size            != 0);
    }
}

inline void
ifb_memory::arena_commit_step_2_find_free_arena(
    IFBMemoryArenaCommit& commit_ref) {

    if (commit_ref.result) {

        //initial arena id
        commit_ref.context->handle_arena.h32 = IFB_MEMORY_INVALID_HANDLE_32;

        //cache constant properties
        const ifb::addr* arena_start_array = commit_ref.cache.arrays.arena_start;  
        const ifb::u32   arena_count       = commit_ref.cache.arena_count; 

        //search for a free arena
        for (
            ifb::u32 arena_index = 0;
                   arena_index < arena_count;
                 ++arena_index) {

            //if the address is zero, we have found a free arena
            if (arena_start_array[arena_index] == 0) {
                
                //we have a free arena, set the index
                commit_ref.context->handle_arena.h32 = arena_index;
                break;
            }
        } 
    
        //check if we found an id
        commit_ref.result &= (commit_ref.context->handle_arena.h32 != IFB_MEMORY_INVALID_HANDLE_32); 
    }
}

inline void 
ifb_memory::arena_commit_step_3_commit_memory(
    IFBMemoryArenaCommit& commit_ref) {

    if (commit_ref.result) {

        //calculate the arena offset
        const ifb::u32 arena_index        = commit_ref.context->handle_arena.h32;
        const ifb::u32 arena_size         = commit_ref.cache.arena_size;
        const ifb::u32 arena_offset       = (arena_index * arena_size);

        //calculate the arena start
        const ifb::addr start_reservation = commit_ref.cache.reservation_start;
        const ifb::addr start_arena       = start_reservation + arena_offset; 

        //do the commit
        const ifb::ptr commit_request     = (ifb::ptr)start_arena;
        const ifb::ptr commit_result      = ifb_platform::memory_commit(commit_request,arena_size);

        //update the arena address and make sure the request and result match
        commit_ref.cache.arena_start = start_arena; 
        commit_ref.result &= (commit_request == commit_result);
    }
}

inline void
ifb_memory::arena_commit_step_4_update_arrays(
    IFBMemoryArenaCommit& commit_ref) {

    if (commit_ref.result) {
    
        //get arena values
        const ifb::u32 arena_index = commit_ref.context->handle_arena.h32;
        const ifb::u32 arena_start = commit_ref.cache.arena_start;

        //update the arrays
        commit_ref.cache.arrays.arena_start    [arena_index] = arena_start;
        commit_ref.cache.arrays.arena_position [arena_index] = 0;
    }
}