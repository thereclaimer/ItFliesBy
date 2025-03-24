#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.cpp"

inline IFBVoid
ifb_memory::arena_pull_step_0_validate_args(
    IFBMemoryArenaPullBytes& pull_ref) {

    ifb_macro_assert(pull_ref.context);
    
    pull_ref.result  = true;
    pull_ref.result &= ifb_memory_macro_is_handle_valid_stack   (reset_ref.context->handles.stack);
    pull_ref.result &= ifb_memory_macro_is_handle_valid_manager (reset_ref.context->handles.manager);
    pull_ref.result &= ifb_memory_macro_is_handle_valid_arena   (reset_ref.context->handles.arena);
}

inline IFBVoid
ifb_memory::arena_pull_step_1_cache_properties(
    IFBMemoryArenaPullBytes& pull_ref) {

    if (pull_ref.result) {

        //get the memory manager
        IFBMemoryManager* memory_manager = ifb_memory::manager_load_and_assert_valid(
            pull_ref.context->stack,
            pull_ref.context->handles.manager);

        //cache the properties
        pull_ref.cache.arena_position_array = ifb_memory::manager_load_array_arena_position(memory_manager);
        pull_ref.cache.arena_count          = memory_manager->count_arenas;
    }
}

inline IFBVoid
ifb_memory::arena_pull_step_2_pull_bytes(
    IFBMemoryArenaPullBytes& pull_ref) {
     
    const IFBU32 arena_pull  = pull_ref.context->input.size;
    const IFBU32 arena_index = pull_ref.context->handles.arena;
    const IFBU32 arena_count = pull_ref.cache.arena_count;
    
    //make sure the index is valid
    pull_ref.result &= (arena_index < arena_count); 
    if (pull_ref.result) {

        //make sure we can do the pull
        const IFBU32 arena_position_current = pull_ref.cache.arena_position_array[arena_index]; 
        pull_ref.result &= (arena_position_current >= arena_pull);
        if (pull_ref.result) {
            
            //update the array
            const IFBU32 arena_position_new = arena_position_current - arena_pull;
            pull_ref.cache.arena_position_array[arena_index] = arena_position_new;
        }
    }
}
