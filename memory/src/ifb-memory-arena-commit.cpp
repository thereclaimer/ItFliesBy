#pragma once

#include "ifb-memory.hpp"

#include "ifb-memory-manager.cpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryArenaCommit;

namespace ifb_memory {

    IFBVoid arena_commit_step_0_validate_args              (IFBMemoryArenaCommit& commit_ref);
    IFBVoid arena_commit_step_1_cache_manager_properties   (IFBMemoryArenaCommit& commit_ref);
    IFBVoid arena_commit_step_2_find_free_arena            (IFBMemoryArenaCommit& commit_ref);
    IFBVoid arena_commit_step_3_calculate_arena_start      (IFBMemoryArenaCommit& commit_ref);
    IFBVoid arena_commit_step_4_commit_memory              (IFBMemoryArenaCommit& commit_ref);
    IFBVoid arena_commit_step_5_update_arrays              (IFBMemoryArenaCommit& commit_ref);
};

/**********************************************************************************/
/* DEFINITIONS                                                                    */
/**********************************************************************************/

struct IFBMemoryArenaCommit {
    IFBB64      result;
    struct {
        IFBAddr stack;
        IFBU32  manager;
        IFBByte padding[4];
    } handles;
    struct {
        IFBAddr  start_reservation;
        IFBAddr* arena_array_start;
        IFBU32*  arena_array_position;
        IFBU32   arena_count;
        IFBU32   arena_size;
    } manager_cache;
    struct {
        IFBAddr  start;
        IFBU32   index;
        IFBByte  padding[4];
    } arena;
};

/**********************************************************************************/
/* COMMIT STEPS                                                                   */
/**********************************************************************************/


inline IFBVoid 
ifb_memory::arena_commit_step_0_validate_args(
    IFBMemoryArenaCommit& commit_ref) {

    commit_ref.result =  true;
    commit_ref.result &= (commit_ref.handles.stack   != 0);
    commit_ref.result &= (commit_ref.handles.manager != 0);
}

inline IFBVoid
ifb_memory::arena_commit_step_1_cache_manager_properties(
    IFBMemoryArenaCommit& commit_ref) {

    //get the memory manager
    IFBMemoryManagerInternal* memory_manager = ifb_memory::manager_load(
        commit_ref.handles.stack,
        commit_ref.handles.manager);

    //make sure our memory manager is valid
    commit_ref.result &= (memory_manager != NULL);
    if (commit_ref.result) {

        //cache the properties we need for the arena commit
        const IFBAddr start_memory                     = (IFBAddr)memory_manager;
        commit_ref.manager_cache.start_reservation     = memory_manager->reserved_memory_start;
        commit_ref.manager_cache.arena_array_start     = (IFBAddr*)ifb_memory::get_pointer(start_memory, memory_manager->offset_arena_array_start);
        commit_ref.manager_cache.arena_array_position  =  (IFBU32*)ifb_memory::get_pointer(start_memory, memory_manager->offset_arena_array_position);
        commit_ref.manager_cache.arena_count           = memory_manager->count_arenas;
        commit_ref.manager_cache.arena_size            = memory_manager->size_arena;
    
        //make sure the properties are non-zero
        commit_ref.result &= (commit_ref.manager_cache.start_reservation     != 0);
        commit_ref.result &= (commit_ref.manager_cache.arena_array_start     != NULL);
        commit_ref.result &= (commit_ref.manager_cache.arena_array_position  != NULL);
        commit_ref.result &= (commit_ref.manager_cache.arena_count           != 0);
        commit_ref.result &= (commit_ref.manager_cache.arena_size            != 0);
    }
}

inline IFBVoid
ifb_memory::arena_commit_step_2_find_free_arena(
    IFBMemoryArenaCommit& commit_ref) {

    if (commit_ref.result) {

        //result will be set to true if we find a free arena
        commit_ref.result = false;

        //cache constant properties
        const IFBAddr* arena_start_array = commit_ref.manager_cache.arena_array_start;  
        const IFBU32   arena_count       = commit_ref.manager_cache.arena_count; 

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
                //and the result to true
                commit_ref.arena.index = arena_index;
                commit_ref.result      = true;

                //we're done
                //break and continue to the next step
                break;
            }
        } 
    }
}

inline IFBVoid 
ifb_memory::arena_commit_step_3_calculate_arena_start(
    IFBMemoryArenaCommit& commit_ref) {

    if (commit_ref.result) {

        //calculate the arena offset
        const IFBU32 arena_index  = commit_ref.arena.index;
        const IFBU32 arena_size   = commit_ref.manager_cache.arena_size;
        const IFBU32 arena_offset = (arena_index * arena_size);

        //calculate the arena start
        const IFBAddr start_reservation = commit_ref.manager_cache.start_reservation;
        commit_ref.arena.start = start_reservation + arena_offset;
    }
}

inline IFBVoid 
ifb_memory::arena_commit_step_4_commit_memory(
    IFBMemoryArenaCommit& commit_ref) {

    if (commit_ref.result) {
     
        //do the commit
        const IFBPtr commit_request = (IFBPtr)commit_ref.arena.start;
        const IFBPtr commit_result  = ifb_platform::memory_commit(commit_request,commit_ref.manager_cache.arena_size);

        //if the result matches the commit request, we're good
        commit_ref.result &= (commit_result == commit_request);
    }
}


inline IFBVoid
ifb_memory::arena_commit_step_5_update_arrays(
    IFBMemoryArenaCommit& commit_ref) {

    if (commit_ref.result) {
    
        //get arena values
        const IFBU32 arena_index = commit_ref.arena.index;
        const IFBU32 arena_start = commit_ref.arena.start;

        //update the arrays
        commit_ref.manager_cache.arena_array_start    [arena_index] = arena_start;
        commit_ref.manager_cache.arena_array_position [arena_index] = 0;
    }
}
