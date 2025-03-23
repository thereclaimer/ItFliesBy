#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-manager.cpp"

/**********************************************************************************/
/* ARENA PUSH STEPS                                                               */
/**********************************************************************************/

inline IFBVoid
ifb_memory::arena_push_step_0_validate_args(
    IFBMemoryArenaPushBytes& push_ref) {

    ifb_macro_assert(push_ref.args.arena);

    push_ref.result  = true;
    push_ref.result &= (push_ref.args.arena->stack       != 0);
    push_ref.result &= (push_ref.args.arena->ids.manager != 0);
    push_ref.result &= (push_ref.args.arena->ids.arena   != 0);
}

inline IFBVoid
ifb_memory::arena_push_step_1_cache_manager_properties(
    IFBMemoryArenaPushBytes& push_ref) {

    if (push_ref.result) {

        //get the memory manager
        IFBMemoryManager* memory_manager = ifb_memory::manager_load_and_assert_valid(
            push_ref.args.arena->stack,
            push_ref.args.arena->ids.manager);

        //cache properties
        ifb_memory::manager_load_arrays(memory_manager,&push_ref.manager_cache.arrays);
        push_ref.manager_cache.arena_size  = memory_manager->size_arena;
        push_ref.manager_cache.arena_count = memory_manager->count_arenas;
    }
}

inline IFBVoid
ifb_memory::arena_push_step_2_push_bytes_relative(
    IFBMemoryArenaPushBytes& push_ref) {

    if (push_ref.result) {

        //calculate the new position
        const IFBU32 arena_index        = push_ref.args.arena->ids.arena;
        const IFBU32 arena_size         = push_ref.manager_cache.arena_size;
        const IFBU32 arena_offset       = push_ref.manager_cache.arrays.arena_position[arena_index];
        const IFBU32 arena_position_new = arena_offset + push_ref.args.size_aligned;

        //make sure we can fit
        push_ref.result &= (arena_position_new < arena_size);
        if (push_ref.result) {

            //if we can, update the position
            push_ref.manager_cache.arrays.arena_position[arena_index] = arena_position_new;
        
            //update the memory
            push_ref.arena_memory.relative_offset = arena_offset;
        }
    }
}

inline IFBVoid
ifb_memory::arena_push_step_2_push_bytes_absolute(
    IFBMemoryArenaPushBytes& push_ref) {

    if (push_ref.result) {

        //calculate the new position
        const IFBU32 arena_index        = push_ref.args.arena->ids.arena;
        const IFBU32 arena_size         = push_ref.manager_cache.arena_size;
        const IFBU32 arena_offset       = push_ref.manager_cache.arrays.arena_position[arena_index];
        const IFBU32 arena_position_new = arena_offset + push_ref.args.size_aligned;

        //make sure we can fit
        push_ref.result &= (arena_position_new < arena_size);
        if (push_ref.result) {

            //if we can, update the position
            push_ref.manager_cache.arrays.arena_position[arena_index] = arena_position_new;
        
            //update the memory
            const IFBAddr arena_start              = push_ref.manager_cache.arrays.arena_start[arena_index];
            const IFBAddr arena_memory_absolute    = arena_start + arena_offset;
            push_ref.arena_memory.absolute_pointer = (IFBPtr)arena_memory_absolute;
        }
    }
}