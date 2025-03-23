#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-manager.cpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

struct IFBMemoryArenaPushBytes;

namespace ifb_memory {

    //arena push bytes
    IFBVoid arena_push_step_0_validate_args            (IFBMemoryArenaPushBytes& push_ref);
    IFBVoid arena_push_step_1_cache_manager_properties (IFBMemoryArenaPushBytes& push_ref);
    IFBVoid arena_push_step_2_push_bytes_relative      (IFBMemoryArenaPushBytes& push_ref);
    IFBVoid arena_push_step_2_push_bytes_absolute      (IFBMemoryArenaPushBytes& push_ref);
};

/**********************************************************************************/
/* DEFINITIONS                                                                    */
/**********************************************************************************/

struct IFBMemoryArenaPushBytes {
    IFBB64                     result;
    
    struct {
        IFBAddr                handle_stack;
        IFBU32                 handle_manager;
        IFBU32                 handle_arena;
        IFBU32                 size;
        IFBU32                 alignment;
    } args;
    
    struct {
        IFBMemoryManagerArrays arrays;
        IFBU32                 arena_size;
        IFBU32                 arena_count;
    } manager_cache;
    
    union {
        IFBU32                 relative_offset;
        IFBPtr                 absolute_pointer;
    } arena_memory;
};

/**********************************************************************************/
/* ARENA PUSH STEPS                                                               */
/**********************************************************************************/

inline IFBVoid
ifb_memory::arena_push_step_0_validate_args(
    IFBMemoryArenaPushBytes& push_ref) {

    push_ref.result  = true;
    push_ref.result &= (push_ref.args.handle_stack   != 0);
    push_ref.result &= (push_ref.args.handle_manager != 0);
    push_ref.result &= (push_ref.args.handle_arena   != 0);
    push_ref.result &= (push_ref.args.size           != 0);
    push_ref.result &= (push_ref.args.alignment      != 0);
}

inline IFBVoid
ifb_memory::arena_push_step_1_cache_manager_properties(
    IFBMemoryArenaPushBytes& push_ref) {

    if (push_ref.result) {

        //get the memory manager
        IFBMemoryManagerInternal* memory_manager = ifb_memory::manager_load(
            push_ref.args.handle_stack,
            push_ref.args.handle_manager);

        //cache properties
        ifb_memory::manager_load_arrays(memory_manager,&push_ref.arrays);
        push_ref.manager_cache.arena_size  = memory_manager->size_arena;
        push_ref.manager_cache.arena_count = memory_manager->count_arenas;
    }
}

inline IFBVoid
ifb_memory::arena_push_step_2_push_bytes_relative(
    IFBMemoryArenaPushBytes& push_ref) {

    if (push_ref.result) {

        //calculate the aligned the push size
        const IFBU32 push_size_aligned = ifb_macro_align_a_to_b(
            push_ref.args.size,
            push_ref.args.alignment);

        //calculate the new position
        const IFBU32 arena_index        = push_ref.args.handle_arena;
        const IFBU32 arena_size         = push_ref.manager_cache.arena_size;
        const IFBU32 arena_offset       = push_ref.manager_cache.arrays.arena_position[arena_index];
        const IFBU32 arena_position_new = arena_offset + push_size_aligned;

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

        //calculate the aligned the push size
        const IFBU32 push_size_aligned = ifb_macro_align_a_to_b(
            push_ref.args.size,
            push_ref.args.alignment);

        //calculate the new position
        const IFBU32 arena_index        = push_ref.args.handle_arena;
        const IFBU32 arena_size         = push_ref.manager_cache.arena_size;
        const IFBU32 arena_offset       = push_ref.manager_cache.arrays.arena_position[arena_index];
        const IFBU32 arena_position_new = arena_offset + push_size_aligned;

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
