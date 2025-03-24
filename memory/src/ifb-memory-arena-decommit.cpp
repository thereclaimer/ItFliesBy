#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.cpp"

/**********************************************************************************/
/* ARENA DECOMMIT STEPS                                                           */
/**********************************************************************************/

inline IFBVoid
ifb_memory::arena_decommit_step_0_validate_args(
    IFBMemoryArenaDecommit& decommit_ref) {

    ifb_macro_assert(decommit_ref.context);

    decommit_ref .result  = true;
    decommit_ref.result &= ifb_memory_macro_is_handle_valid_stack   (decommit_ref.context->handle_stack);
    decommit_ref.result &= ifb_memory_macro_is_handle_valid_manager (decommit_ref.context->handle_manager);
    decommit_ref.result &= ifb_memory_macro_is_handle_valid_arena   (decommit_ref.context->handle_arena);
}

inline IFBVoid
ifb_memory::arena_decommit_step_1_cache_manager_properties(
    IFBMemoryArenaDecommit& decommit_ref) {

    if (decommit_ref.result) { 

        //get the memory manager
        IFBMemoryManager* memory_manager_internal = ifb_memory::manager_load_and_assert_valid(
            decommit_ref.context->handle_stack,
            decommit_ref.context->handle_manager);

        //cache the properties we need for the arena decommit
        decommit_ref.cache.arena_start_array = ifb_memory::manager_load_array_arena_start(memory_manager_internal);
        decommit_ref.cache.arena_size        = memory_manager_internal->size_arena;
        decommit_ref.cache.arena_count       = memory_manager_internal->count_arenas;
    
        //make sure our arena index is valid
        const IFBU32 arena_index = decommit_ref.context->handle_arena.h32;
        const IFBU32 arena_count = decommit_ref.cache.arena_count; 
        decommit_ref.result &= (arena_index < arena_count);
    }
}

inline IFBVoid
ifb_memory::arena_decommit_step_3_decommit_memory(
    IFBMemoryArenaDecommit& decommit_ref) {

    if (decommit_ref.result) {

        //get the commit pointer
        const IFBU32  arena_index      = decommit_ref.context->handle_arena.h32;
        const IFBAddr arena_start_addr = decommit_ref.cache.arena_start_array[arena_index];
        const IFBPtr  arena_start_ptr  = (IFBPtr)arena_start_addr;

        //decommit the memory
        decommit_ref.result &= ifb_platform::memory_decommit(
            arena_start_ptr,
            decommit_ref.cache.arena_size);
    }
}

inline IFBVoid 
ifb_memory::arena_decommit_step_4_update_arena_start_array(
    IFBMemoryArenaDecommit& decommit_ref) {

    if (decommit_ref.result) {

        //update the array        
        const IFBU32 arena_index = decommit_ref.context->handle_arena.h32;
        decommit_ref.cache.arena_start_array[arena_index] = 0;
    }
}