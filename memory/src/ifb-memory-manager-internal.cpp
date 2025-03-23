#pragma once

#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryManagerArrays;
struct IFBMemoryManagerInit;
struct IFBMemoryManagerArenaCommit;

namespace ifb_memory {

    //initialization
    IFBVoid manager_init_step_0_validate_args                     (IFBMemoryManagerInit& init_ref);
    IFBVoid manager_init_step_1_get_system_info                   (IFBMemoryManagerInit& init_ref);
    IFBVoid manager_init_step_3_calculate_sizes                   (IFBMemoryManagerInit& init_ref);
    IFBVoid manager_init_step_2_allocate_manager                  (IFBMemoryManagerInit& init_ref);
    IFBVoid manager_init_step_4_reserve_system_memory             (IFBMemoryManagerInit& init_ref);
    IFBVoid manager_init_step_5_set_properties                    (IFBMemoryManagerInit& init_ref);
    IFBVoid manager_init_step_6_cleanup                           (IFBMemoryManagerInit& init_ref);

    //validation
    IFBVoid manager_assert_valid                                  (IFBMemoryManager* memory_manager);

    //arena commit
    IFBVoid manager_arena_commit_step_0_validate_args             (IFBMemoryManagerArenaCommit& commit_ref);
    IFBVoid manager_arena_commit_step_1_load_arena_start_array    (IFBMemoryManagerArenaCommit& commit_ref);
    IFBVoid manager_arena_commit_step_2_find_free_arena           (IFBMemoryManagerArenaCommit& commit_ref);
    IFBVoid manager_arena_commit_step_3_calculate_arena_start     (IFBMemoryManagerArenaCommit& commit_ref);
    IFBVoid manager_arena_commit_step_4_commit_memory             (IFBMemoryManagerArenaCommit& commit_ref);
    IFBVoid manager_arena_commit_step_5_load_arena_position_array (IFBMemoryManagerArenaCommit& commit_ref);
    IFBVoid manager_arena_commit_step_6_update_arrays             (IFBMemoryManagerArenaCommit& commit_ref);
};

/**********************************************************************************/
/* DEFINITIONS                                                                    */
/**********************************************************************************/

struct IFBMemoryManager {
    IFBAddr reserved_memory_start;
    IFBU32  count_arenas;
    IFBU32  size_arena;
    IFBU32  size_page;
    IFBU32  size_granularity;
    struct {
        IFBU32 start;
        IFBU32 position;
    } arena_array_offsets;
};

struct IFBMemoryManagerArrays {
    IFBAddr* start;
    IFBU32*  position;
};

struct IFBMemoryManagerInit {
    IFBB64                result;
    IFBMemoryManagerArgs* args;
    IFBMemoryManager*     manager;
    IFBPtr                reservation;
    IFBSystemMemoryInfo   sys_info;
    struct {
        IFBU32  aligned_size_reservation;
        IFBU32  aligned_size_arena;
        IFBU32  count_arenas;
        IFBU32  commit_size_total;
        IFBU32  commit_size_manager_struct;
        IFBU32  commit_size_array_arena_start;
        IFBU32  commit_size_array_arena_position;
        IFBByte padding[4];
    } cache;
};

struct IFBMemoryManagerArenaCommit {
    IFBB64      result;
    struct {
        IFBAddr start_memory;
        IFBAddr start_reservation;
        IFBU32  arena_count;
        IFBU32  arena_size;
        IFBU32  offset_arena_start;
        IFBU32  offset_arena_position;
    } manager_cache;
    struct {
        IFBAddr* start;
        IFBU32*  position;
    } arena_arrays;
    struct {
        IFBAddr  start;
        IFBU32   index;
        IFBByte  padding[4];
    } arena;
};

/**********************************************************************************/
/* INITIALIZATION                                                                 */
/**********************************************************************************/

inline IFBVoid 
ifb_memory::manager_init_step_0_validate_args(
    IFBMemoryManagerInit& init_ref) {
    
    init_ref.result = (init_ref.args != NULL);
    if (init_ref.result) {
        
        init_ref.result &= (init_ref.args->stack            != NULL);
        init_ref.result &= (init_ref.args->size_reservation != NULL);
        init_ref.result &= (init_ref.args->size_arena       != NULL);
    }
}

inline IFBVoid 
ifb_memory::manager_init_step_1_get_system_info(
    IFBMemoryManagerInit& init_ref) {

    init_ref.result &= ifb_platform::system_get_info_memory(&init_ref.sys_info);
    init_ref.result &= init_ref.sys_info.allocation_granularity != 0;
    init_ref.result &= init_ref.sys_info.page_size              != 0;
}

inline IFBVoid 
ifb_memory::manager_init_step_3_calculate_sizes(
    IFBMemoryManagerInit& init_ref) {
    
    if (init_ref.result) {

        //align the reservation size to the allocation granularity
        init_ref.cache.aligned_size_reservation = ifb_macro_align_a_to_b(
            init_ref.args->size_reservation,
            (IFBU64)init_ref.sys_info.allocation_granularity);

        //align the arena size to a page size
        init_ref.cache.aligned_size_arena = ifb_macro_align_a_to_b(
            (IFBU32)init_ref.args->size_arena,
            init_ref.sys_info.page_size);

        //page and arena counts
        init_ref.cache.count_arenas = init_ref.cache.aligned_size_reservation / init_ref.cache.aligned_size_arena;

        //property sizes    
        init_ref.cache.commit_size_manager_struct       = ifb_macro_align_size_struct(IFBMemoryManager);
        init_ref.cache.commit_size_array_arena_start    = sizeof(IFBAddr) * init_ref.cache.count_arenas;
        init_ref.cache.commit_size_array_arena_position = sizeof(IFBU32)  * init_ref.cache.count_arenas;
     
        //total commit size
        init_ref.cache.commit_size_total = 
            init_ref.cache.commit_size_manager_struct    +
            init_ref.cache.commit_size_array_arena_start +
            init_ref.cache.commit_size_array_arena_position;

        //sanity check, make sure all sizes are non-zero
        init_ref.result &= (init_ref.cache.aligned_size_reservation         != 0);
        init_ref.result &= (init_ref.cache.aligned_size_arena               != 0);
        init_ref.result &= (init_ref.cache.count_arenas                     != 0);
        init_ref.result &= (init_ref.cache.commit_size_total                != 0);
        init_ref.result &= (init_ref.cache.commit_size_manager_struct       != 0);
        init_ref.result &= (init_ref.cache.commit_size_array_arena_start    != 0);
        init_ref.result &= (init_ref.cache.commit_size_array_arena_position != 0);
    }
}

inline IFBVoid 
ifb_memory::manager_init_step_2_allocate_manager(
    IFBMemoryManagerInit& init_ref) {

    if (init_ref.result) {

        //do the stack commit
        init_ref.manager = (IFBMemoryManager*)ifb_memory::stack_push_bytes_absolute(
            init_ref.args->stack,
            init_ref.cache.commit_size_total);

        //make sure we have the manager
        init_ref.result &= (init_ref.manager != NULL); 
    }
}

inline IFBVoid 
ifb_memory::manager_init_step_4_reserve_system_memory(
    IFBMemoryManagerInit& init_ref) {

    if (init_ref.result) {

        //make the reservation
        init_ref.reservation = ifb_platform::memory_reserve(
            init_ref.cache.aligned_size_reservation);

        //make sure we got it
        init_ref.result &= (init_ref.reservation != NULL);
    }
}

inline IFBVoid 
ifb_memory::manager_init_step_5_set_properties(
    IFBMemoryManagerInit& init_ref) {
        
    //set the properties
    init_ref.manager->reserved_memory_start = (IFBAddr)init_ref.reservation;
    init_ref.manager->count_arenas          = init_ref.cache.count_arenas;
    init_ref.manager->size_arena            = init_ref.cache.aligned_size_arena;
    init_ref.manager->size_page             = init_ref.sys_info.page_size;
    init_ref.manager->size_granularity      = init_ref.sys_info.allocation_granularity;

    //offsets
    init_ref.manager->arena_array_offsets.start    = init_ref.cache.commit_size_manager_struct;
    init_ref.manager->arena_array_offsets.position = init_ref.cache.commit_size_array_arena_start              + init_ref.manager->arena_array_offsets.start; 

    //sanity check, make sure the properties are non-zero
    init_ref.result &= (init_ref.manager->reserved_memory_start        != 0);
    init_ref.result &= (init_ref.manager->count_arenas                 != 0);
    init_ref.result &= (init_ref.manager->size_arena                   != 0);
    init_ref.result &= (init_ref.manager->size_page                    != 0);
    init_ref.result &= (init_ref.manager->size_granularity             != 0);
    init_ref.result &= (init_ref.manager->arena_array_offsets.start    != 0);
    init_ref.result &= (init_ref.manager->arena_array_offsets.position != 0);
}

inline IFBVoid 
ifb_memory::manager_init_step_6_cleanup(
    IFBMemoryManagerInit& init_ref) {

    //if we were not able to create the manager,
    //we need to release any aquired memory
    const IFBB8 should_release_memory_reservation = (!init_ref.result && init_ref.reservation != NULL); 
    const IFBB8 should_release_memory_stack       = (!init_ref.result && init_ref.manager     != NULL); 

    //platform memory
    if (should_release_memory_reservation) {

        //release the memory        
        const IFBB8 released = ifb_platform::memory_release(
            init_ref.reservation,
            init_ref.cache.aligned_size_reservation);

        //we should AlWAYS be able to release memory        
        ifb_macro_assert(released);
    }

    //stack memory
    if (should_release_memory_stack) {

        //release the memory
        const IFBB8 released = ifb_memory::stack_pull_bytes(
            init_ref.args->stack,
            init_ref.cache.commit_size_total);

        //we should AlWAYS be able to release memory        
        ifb_macro_assert(released);
    }

    //make sure the reserved pointers are null
    init_ref.manager     = NULL;
    init_ref.reservation = NULL;    
}

/**********************************************************************************/
/* VALIDATION                                                                     */
/**********************************************************************************/

inline IFBVoid
ifb_memory::manager_assert_valid(
    IFBMemoryManager* memory_manager) {

    ifb_macro_assert(memory_manager);
    ifb_macro_assert(memory_manager->reserved_memory_start        != 0);
    ifb_macro_assert(memory_manager->count_arenas                 != 0);
    ifb_macro_assert(memory_manager->size_arena                   != 0);
    ifb_macro_assert(memory_manager->size_page                    != 0);
    ifb_macro_assert(memory_manager->size_granularity             != 0);
    ifb_macro_assert(memory_manager->arena_array_offsets.start    != 0);
    ifb_macro_assert(memory_manager->arena_array_offsets.position != 0);
}

/**********************************************************************************/
/* ARENA COMMIT                                                                   */
/**********************************************************************************/

inline IFBVoid 
ifb_memory::manager_arena_commit_step_0_validate_args(
    IFBMemoryManagerArenaCommit& commit_ref) {

    commit_ref.result =  true;
    commit_ref.result &= (commit_ref.manager_cache.start_memory);
    commit_ref.result &= (commit_ref.manager_cache.start_reservation);
    commit_ref.result &= (commit_ref.manager_cache.arena_count);
    commit_ref.result &= (commit_ref.manager_cache.arena_size);
    commit_ref.result &= (commit_ref.manager_cache.offset_arena_start);
    commit_ref.result &= (commit_ref.manager_cache.offset_arena_position);
}

inline IFBVoid
ifb_memory::manager_arena_commit_step_1_load_arena_start_array(
    IFBMemoryManagerArenaCommit& commit_ref) {

    //calculate the array address
    const IFBAddr memory_start             = commit_ref.manager_cache.start_memory;
    const IFBU32  arena_start_array_offset = commit_ref.manager_cache.offset_arena_start;
    const IFBAddr arena_start_array_addr   = memory_start + arena_start_array_offset;

    //cache the pointer
    commit_ref.arena_arrays.start = (IFBAddr*)arena_start_array_addr; 
}

inline IFBVoid
ifb_memory::manager_arena_commit_step_2_find_free_arena(
    IFBMemoryManagerArenaCommit& commit_ref) {

    if (commit_ref.result) {

        //result will be set to true if we find a free arena
        commit_ref.result = false;

        for (
            IFBU32 arena_index = 0;
                   arena_index < commit_ref.manager_cache.arena_count;
                 ++arena_index) {

            //if the address is zero, we have found a free arena
            if (commit_ref.arena_arrays.start[arena_index] == 0) {
                
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
ifb_memory::manager_arena_commit_step_3_calculate_arena_start(
    IFBMemoryManagerArenaCommit& commit_ref) {

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
ifb_memory::manager_arena_commit_step_4_commit_memory(
    IFBMemoryManagerArenaCommit& commit_ref) {

    if (commit_ref.result) {
     
        //do the commit
        const IFBPtr commit_request = (IFBPtr)commit_ref.arena.start;
        const IFBPtr commit_result  = ifb_platform::memory_commit(commit_request,commit_ref.manager_cache.arena_size);

        //if the result matches the commit request, we're good
        commit_ref.result &= (commit_result == commit_request);
    }
}

inline IFBVoid
ifb_memory::manager_arena_commit_step_5_load_arena_position_array(
    IFBMemoryManagerArenaCommit& commit_ref) {

    if (commit_ref.result) {
    
        //calculate address
        const IFBAddr start_memory   = commit_ref.manager_cache.start_memory;
        const IFBAddr start_position = commit_ref.manager_cache.offset_arena_position;

        //cast the pointer
        commit_ref.arena_arrays.position = (IFBU32*)start_position;
    }
}

inline IFBVoid
ifb_memory::manager_arena_commit_step_6_update_arrays(
    IFBMemoryManagerArenaCommit& commit_ref) {

    if (commit_ref.result) {
    
        //get arena values
        const IFBU32 arena_index = commit_ref.arena.index;
        const IFBU32 arena_start = commit_ref.arena.start;

        //update the arrays
        commit_ref.arena_arrays.start    [arena_index] = arena_start;
        commit_ref.arena_arrays.position [arena_index] = 0;
    }
}
