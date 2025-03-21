#pragma once

#include "ifb-memory.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryManagerArrays;
struct IFBMemoryManagerInit;

//initialization steps
namespace ifb_memory {

    IFBVoid manager_init_step_0_validate_args         (IFBMemoryManagerInit& init_ref);
    IFBVoid manager_init_step_1_get_system_info       (IFBMemoryManagerInit& init_ref);
    IFBVoid manager_init_step_3_calculate_sizes       (IFBMemoryManagerInit& init_ref);
    IFBVoid manager_init_step_2_allocate_manager      (IFBMemoryManagerInit& init_ref);
    IFBVoid manager_init_step_4_reserve_system_memory (IFBMemoryManagerInit& init_ref);
    IFBVoid manager_init_step_5_set_properties        (IFBMemoryManagerInit& init_ref);
    IFBVoid manager_init_step_6_cleanup               (IFBMemoryManagerInit& init_ref);
};

/**********************************************************************************/
/* DEFINITIONS                                                                    */
/**********************************************************************************/

struct IFBMemoryManager {
    IFBAddr reserved_memory_start;
    IFBU32  count_arenas;
    IFBU32  count_pages;
    IFBU32  size_arena;
    IFBU32  size_page;
    IFBU32  size_granularity;
    struct {
        IFBU32 start;
        IFBU32 position_committed;
        IFBU32 position_reserved;
    } arena_array_offsets;
};

struct IFBMemoryManagerArrays {
    IFBAddr* start;
    IFBU32*  position_committed;
    IFBU32*  position_reserved;    
};

struct IFBMemoryManagerInit {
    IFBB64                result;
    IFBMemoryManagerArgs* args;
    IFBMemoryManager*     manager;
    IFBPtr                reservation;
    IFBSystemMemoryInfo   sys_info;
    struct {
        IFBU64 aligned_size_reservation;
        IFBU64 aligned_size_arena;
        IFBU32 count_pages;
        IFBU32 count_arenas;
        IFBU32 commit_size_total;
        IFBU32 commit_size_manager_struct;
        IFBU32 commit_size_array_arena_start;
        IFBU32 commit_size_array_arena_position_committed;
        IFBU32 commit_size_array_arena_position_reserved;
    } cache;
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
        init_ref.cache.count_pages  = init_ref.cache.aligned_size_reservation / init_ref.sys_info.page_size;
        init_ref.cache.count_arenas = init_ref.cache.aligned_size_reservation / init_ref.cache.aligned_size_arena;

        //property sizes    
        const IFBU32 size_position_array = sizeof(IFBU32) * init_ref.cache.count_arenas; 
        init_ref.cache.commit_size_manager_struct                 = ifb_macro_align_size_struct(IFBMemoryManager);
        init_ref.cache.commit_size_array_arena_start              = size_position_array;
        init_ref.cache.commit_size_array_arena_position_committed = size_position_array;
        init_ref.cache.commit_size_array_arena_position_reserved  = size_position_array;
     
        //total commit size
        init_ref.cache.commit_size_total = 
            init_ref.cache.commit_size_manager_struct                 +
            init_ref.cache.commit_size_array_arena_start              +
            init_ref.cache.commit_size_array_arena_position_committed +
            init_ref.cache.commit_size_array_arena_position_reserved;

        //sanity check, make sure all sizes are non-zero
        init_ref.result &= (init_ref.cache.aligned_size_reservation                   != 0);
        init_ref.result &= (init_ref.cache.aligned_size_arena                         != 0);
        init_ref.result &= (init_ref.cache.count_pages                                != 0);
        init_ref.result &= (init_ref.cache.count_arenas                               != 0);
        init_ref.result &= (init_ref.cache.commit_size_total                          != 0);
        init_ref.result &= (init_ref.cache.commit_size_manager_struct                 != 0);
        init_ref.result &= (init_ref.cache.commit_size_array_arena_start              != 0);
        init_ref.result &= (init_ref.cache.commit_size_array_arena_position_committed != 0);
        init_ref.result &= (init_ref.cache.commit_size_array_arena_position_reserved  != 0);
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
    init_ref.manager->count_pages           = init_ref.cache.count_pages;
    init_ref.manager->size_arena            = init_ref.cache.aligned_size_arena;
    init_ref.manager->size_page             = init_ref.sys_info.page_size;
    init_ref.manager->size_granularity      = init_ref.sys_info.allocation_granularity;

    //offsets
    init_ref.manager->arena_array_offsets.start              = init_ref.cache.commit_size_manager_struct;
    init_ref.manager->arena_array_offsets.position_committed = init_ref.cache.commit_size_array_arena_start              + init_ref.manager->arena_array_offsets.start; 
    init_ref.manager->arena_array_offsets.position_reserved  = init_ref.cache.commit_size_array_arena_position_committed + init_ref.manager->arena_array_offsets.position_committed;

    //sanity check, make sure the properties are non-zero
    init_ref.result &= (init_ref.manager->reserved_memory_start                  != 0);
    init_ref.result &= (init_ref.manager->count_arenas                           != 0);
    init_ref.result &= (init_ref.manager->count_pages                            != 0);
    init_ref.result &= (init_ref.manager->size_arena                             != 0);
    init_ref.result &= (init_ref.manager->size_page                              != 0);
    init_ref.result &= (init_ref.manager->size_granularity                       != 0);
    init_ref.result &= (init_ref.manager->arena_array_offsets.start              != 0);
    init_ref.result &= (init_ref.manager->arena_array_offsets.position_committed != 0);
    init_ref.result &= (init_ref.manager->arena_array_offsets.position_reserved  != 0);
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