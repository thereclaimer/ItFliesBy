#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-manager.cpp"

/**********************************************************************************/
/* ARENA COMMIT STEPS                                                             */
/**********************************************************************************/

inline IFBVoid 
ifb_memory::arena_commit_step_0_validate_args(
    IFBMemoryArenaCommit& commit_ref) {

    ifb_macro_assert(commit_ref.context);

    //initial values
    commit_ref.result  =  true;
    commit_ref.result &= (commit_ref.context->ids.stack   != 0);
    commit_ref.result &= (commit_ref.context->ids.manager != 0);
    commit_ref.result &= (commit_ref.context->ids.manager != IFB_MEMORY_INVALID_VALUE);
}

inline IFBVoid
ifb_memory::arena_commit_step_1_cache_manager_properties(
    IFBMemoryArenaCommit& commit_ref) {

    if (commit_ref.result) {

        //get the memory manager
        IFBMemoryManager* memory_manager_internal = ifb_memory::manager_load_and_assert_valid(
            commit_ref.context->ids.stack,
            commit_ref.context->ids.manager);

        //load the arrays
        ifb_memory::manager_load_arrays(memory_manager_internal,&commit_ref.cache.arrays);
        
        //cache the other properties
        commit_ref.cache.reservation_start = memory_manager_internal->reserved_memory_start;
        commit_ref.cache.arena_count       = memory_manager_internal->count_arenas;
        commit_ref.cache.arena_size        = memory_manager_internal->size_arena;
    
        //make sure the properties are non-zero
        commit_ref.result &= (commit_ref.cache.reservation_start     != 0);
        commit_ref.result &= (commit_ref.cache.arrays.arena_start    != NULL);
        commit_ref.result &= (commit_ref.cache.arrays.arena_position != NULL);
        commit_ref.result &= (commit_ref.cache.arena_count           != 0);
        commit_ref.result &= (commit_ref.cache.arena_size            != 0);
    }
}

inline IFBVoid
ifb_memory::arena_commit_step_2_find_free_arena(
    IFBMemoryArenaCommit& commit_ref) {

    if (commit_ref.result) {

        //initial arena id
        commit_ref.context->ids.arena = IFB_MEMORY_INVALID_VALUE;

        //cache constant properties
        const IFBAddr* arena_start_array = commit_ref.cache.arrays.arena_start;  
        const IFBU32   arena_count       = commit_ref.cache.arena_count; 

        //search for a free arena
        for (
            IFBU32 arena_index = 0;
                   arena_index < arena_count;
                 ++arena_index) {

            //if the address is zero, we have found a free arena
            if (arena_start_array[arena_index] == 0) {
                
                //huzzah!
                //we have a free arena
                //set the index
                commit_ref.context->ids.arena = arena_index;
                break;
            }
        } 
    
        //check if we found an id
        commit_ref.result &= (commit_ref.context->ids.arena != IFB_MEMORY_INVALID_VALUE); 
    }
}

inline IFBVoid 
ifb_memory::arena_commit_step_3_commit_memory(
    IFBMemoryArenaCommit& commit_ref) {

    if (commit_ref.result) {

        //calculate the arena offset
        const IFBU32 arena_index        = commit_ref.context->ids.arena;
        const IFBU32 arena_size         = commit_ref.cache.arena_size;
        const IFBU32 arena_offset       = (arena_index * arena_size);

        //calculate the arena start
        const IFBAddr start_reservation = commit_ref.cache.reservation_start;
        const IFBAddr start_arena       = start_reservation + arena_offset; 

        //do the commit
        const IFBPtr commit_request     = (IFBPtr)start_arena;
        const IFBPtr commit_result      = ifb_platform::memory_commit(commit_request,arena_size);

        //update the arena address and make sure the request and result match
        commit_ref.cache.arena_start = start_arena; 
        commit_ref.result &= (commit_request == commit_result);
    }
}

inline IFBVoid
ifb_memory::arena_commit_step_4_update_arrays(
    IFBMemoryArenaCommit& commit_ref) {

    if (commit_ref.result) {
    
        //get arena values
        const IFBU32 arena_index = commit_ref.context->ids.arena;
        const IFBU32 arena_start = commit_ref.cache.arena_start;

        //update the arrays
        commit_ref.cache.arrays.arena_start    [arena_index] = arena_start;
        commit_ref.cache.arrays.arena_position [arena_index] = 0;
    }
}