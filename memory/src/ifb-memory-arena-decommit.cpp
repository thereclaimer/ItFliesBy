#pragma once

#include "ifb-memory.hpp"

#include "ifb-memory-internal.cpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryArenaDecommit;

namespace ifb_memory {
   
    IFBVoid arena_decommit_step_0_validate_args            (IFBMemoryArenaDecommit& decommit_ref);
    IFBVoid arena_decommit_step_1_cache_manager_properties (IFBMemoryArenaDecommit& decommit_ref);
    IFBVoid arena_decommit_step_2_load_arena_start_array   (IFBMemoryArenaDecommit& decommit_ref);
    IFBVoid arena_decommit_step_3_decommit_memory          (IFBMemoryArenaDecommit& decommit_ref);
    IFBVoid arena_decommit_step_4_update_arena_start_array (IFBMemoryArenaDecommit& decommit_ref);
};

/**********************************************************************************/
/* DEFINITIONS                                                                    */
/**********************************************************************************/

struct IFBMemoryArenaDecommit {
    IFBB64       result;
    struct {
        IFBAddr  handle_stack;
        IFBU32   handle_manager;
        IFBU32   handle_arena;
    } args;
    struct {
        IFBAddr* arena_start_array;
        IFBU32   arena_size;
        IFBU32   arena_count;
    } manager_cache;
};

/**********************************************************************************/
/* DECOMMIT STEPS                                                                 */
/**********************************************************************************/

inline IFBVoid
ifb_memory::arena_decommit_step_0_validate_args(
    IFBMemoryArenaDecommit& decommit_ref) {

    decommit_ref.result  = true;
    decommit_ref.result &= (decommit_ref.args.handle_stack   != 0); 
    decommit_ref.result &= (decommit_ref.args.handle_manager != 0);
}

inline IFBVoid
ifb_memory::arena_decommit_step_1_cache_manager_properties(
    IFBMemoryArenaDecommit& decommit_ref) {

    //get the memory manager
    IFBMemoryManagerInternal* memory_manager = ifb_memory::manager_load(
        decommit_ref.args.handle_stack,
        decommit_ref.args.handle_manager);

    //make sure our memory manager is valid
    decommit_ref.result &= (memory_manager != NULL);
    if (decommit_ref.result) { 

        //cache the properties we need for the arena decommit
        decommit_ref.manager_cache.arena_start_array = (IFBAddr*)ifb_memory::get_pointer((IFBAddr)memory_manager, memory_manager->offset_arena_array_start);
        decommit_ref.manager_cache.arena_size        = memory_manager->size_arena;
        decommit_ref.manager_cache.arena_count       = memory_manager->count_arenas;
    
        //make sure our arena index is valid
        const IFBU32 arena_index = decommit_ref.args.handle_arena;
        const IFBU32 arena_count = decommit_ref.manager_cache.arena_count; 
        decommit_ref.result &= (arena_index < arena_count);
    }
}

inline IFBVoid
ifb_memory::arena_decommit_step_3_decommit_memory(
    IFBMemoryArenaDecommit& decommit_ref) {

    if (decommit_ref.result) {

        //get the commit pointer
        const IFBU32  arena_index      = decommit_ref.args.handle_arena;
        const IFBAddr arena_start_addr = decommit_ref.manager_cache.arena_start_array[arena_index];
        const IFBPtr  arena_start_ptr  = (IFBPtr)arena_start_addr;

        //decommit the memory
        decommit_ref.result &= ifb_platform::memory_decommit(
            arena_start_ptr,
            decommit_ref.manager_cache.arena_size);
    }
}

inline IFBVoid 
ifb_memory::arena_decommit_step_4_update_arena_start_array(
    IFBMemoryArenaDecommit& decommit_ref) {

    if (decommit_ref.result) {

        //update the array        
        const IFBU32 arena_index = decommit_ref.args.handle_arena;
        decommit_ref.manager_cache.arena_start_array[arena_index] = 0;
    }
}