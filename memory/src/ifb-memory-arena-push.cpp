#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-reservation.cpp"

/**********************************************************************************/
/* ARENA PUSH STEPS                                                               */
/**********************************************************************************/

inline IFBVoid
ifb_memory::arena_push_step_0_validate_args(
    IFBMemoryArenaPushBytes& push_ref) {

    ifb_macro_assert(push_ref.context);

    push_ref.result  = true;
    push_ref.result &= ifb_memory_macro_is_handle_valid_stack   (push_ref.context->handle_stack);
    push_ref.result &= ifb_memory_macro_is_handle_valid_reservation (push_ref.context->handle_reservation);
    push_ref.result &= ifb_memory_macro_is_handle_valid_arena   (push_ref.context->handle_arena);
}

inline IFBVoid
ifb_memory::arena_push_step_1_cache_reservation_properties(
    IFBMemoryArenaPushBytes& push_ref) {

    if (push_ref.result) {

        //get the memory reservation
        IFBMemoryReservation* reservation = ifb_memory::reservation_load_and_assert_valid(
            push_ref.context->handle_stack,
            push_ref.context->handle_reservation);

        //cache properties
        ifb_memory::reservation_load_arrays(reservation,&push_ref.cache.arrays);
        push_ref.cache.arena_size  = reservation->size_arena;
        push_ref.cache.arena_count = reservation->count_arenas;
    }
}

inline IFBVoid
ifb_memory::arena_push_step_2_push_bytes_relative(
    IFBMemoryArenaPushBytes& push_ref) {

    if (push_ref.result) {

        //calculate the new position
        const IFBU32 arena_index        = push_ref.context->handle_arena.h32;
        const IFBU32 arena_size         = push_ref.cache.arena_size;
        const IFBU32 arena_offset       = push_ref.cache.arrays.arena_position[arena_index];
        const IFBU32 arena_position_new = arena_offset + push_ref.push_size;

        //make sure we can fit
        push_ref.result &= (arena_position_new < arena_size);
        if (push_ref.result) {

            //if we can, update the position
            push_ref.cache.arrays.arena_position[arena_index] = arena_position_new;
        
            //update the memory
            push_ref.memory.relative_offset = arena_offset;
        }
    }
}

inline IFBVoid
ifb_memory::arena_push_step_2_push_bytes_absolute(
    IFBMemoryArenaPushBytes& push_ref) {

    if (push_ref.result) {

        //calculate the new position
        const IFBU32 arena_index        = push_ref.context->handle_arena.h32;
        const IFBU32 arena_size         = push_ref.cache.arena_size;
        const IFBU32 arena_offset       = push_ref.cache.arrays.arena_position[arena_index];
        const IFBU32 arena_position_new = arena_offset + push_ref.push_size;

        //make sure we can fit
        push_ref.result &= (arena_position_new < arena_size);
        if (push_ref.result) {

            //if we can, update the position
            push_ref.cache.arrays.arena_position[arena_index] = arena_position_new;
        
            //update the memory
            const IFBAddr arena_start           = push_ref.cache.arrays.arena_start[arena_index];
            const IFBAddr arena_memory_absolute = arena_start + arena_offset;
            push_ref.memory.absolute_pointer    = (IFBPtr)arena_memory_absolute;
        }
    }
}