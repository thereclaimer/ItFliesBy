#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.cpp"

inline IFBVoid
ifb_memory::arena_reset_step_0_validate_args(
    IFBMemoryArenaReset& reset_ref) {

    ifb_macro_assert(reset_ref.context);

    reset_ref.result  = true;
    reset_ref.result &= ifb_memory_macro_is_handle_valid_stack   (reset_ref.context->handles.stack);
    reset_ref.result &= ifb_memory_macro_is_handle_valid_manager (reset_ref.context->handles.manager);
    reset_ref.result &= ifb_memory_macro_is_handle_valid_arena   (reset_ref.context->handles.arena);
}

inline IFBVoid
ifb_memory::arena_reset_step_1_cache_properties(
    IFBMemoryArenaReset& reset_ref) {

    if (reset_ref.result) {

        //get the memory manager
        IFBMemoryManager* memory_manager = ifb_memory::manager_load_and_assert_valid(
            reset_ref.context->handles.stack,
            reset_ref.context->handles.manager);
         
        reset_ref.cache.arena_position_array = ifb_memory::manager_load_array_arena_position(memory_manager);
        reset_ref.cache.arena_count          = reset_ref.cache.arena_count;
    }
}

inline IFBVoid
ifb_memory::arena_reset_step_2_reset_arena(
    IFBMemoryArenaReset& reset_ref) {

    //make sure the index is valid
    const IFBU32 arena_index = reset_ref.context->handles.arena.h32;
    const IFBU32 arena_count = reset_ref.cache.arena_count;
    reset_ref.result &= (arena_index < arena_count); 

    //if the index is valid, reset the arena
    if (reset_ref.result) {
        reset_ref.cache.arena_position_array[arena_index] = 0;
    }
}