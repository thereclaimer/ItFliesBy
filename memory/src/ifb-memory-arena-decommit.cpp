#pragma once

#include "ifb-memory.hpp"
#include "ifb-memory-internal.cpp"

/**********************************************************************************/
/* ARENA DECOMMIT STEPS                                                           */
/**********************************************************************************/

inline void
ifb_memory::arena_decommit_step_0_validate_args(
    IFBMemoryArenaDecommit& decommit_ref) {

    ifb_macro_assert(decommit_ref.context);

    decommit_ref .result  = true;
    decommit_ref.result &= ifb_memory_macro_is_handle_valid_stack   (decommit_ref.context->handle_stack);
    decommit_ref.result &= ifb_memory_macro_is_handle_valid_reservation (decommit_ref.context->handle_reservation);
    decommit_ref.result &= ifb_memory_macro_is_handle_valid_arena   (decommit_ref.context->handle_arena);
}

inline void
ifb_memory::arena_decommit_step_1_cache_reservation_properties(
    IFBMemoryArenaDecommit& decommit_ref) {

    if (decommit_ref.result) { 

        //get the memory reservation
        IFBMemoryReservation* reservation_internal = ifb_memory::reservation_load_and_assert_valid(
            decommit_ref.context->handle_stack,
            decommit_ref.context->handle_reservation);

        //cache the properties we need for the arena decommit
        decommit_ref.cache.arena_start_array = ifb_memory::reservation_load_array_arena_start(reservation_internal);
        decommit_ref.cache.arena_size        = reservation_internal->size_arena;
        decommit_ref.cache.arena_count       = reservation_internal->count_arenas;
    
        //make sure our arena index is valid
        const ifb::u32 arena_index = decommit_ref.context->handle_arena.h32;
        const ifb::u32 arena_count = decommit_ref.cache.arena_count; 
        decommit_ref.result &= (arena_index < arena_count);
    }
}

inline void
ifb_memory::arena_decommit_step_3_decommit_memory(
    IFBMemoryArenaDecommit& decommit_ref) {

    if (decommit_ref.result) {

        //get the commit pointer
        const ifb::u32  arena_index      = decommit_ref.context->handle_arena.h32;
        const ifb::addr arena_start_addr = decommit_ref.cache.arena_start_array[arena_index];
        const ifb::ptr  arena_start_ptr  = (ifb::ptr)arena_start_addr;

        //decommit the memory
        decommit_ref.result &= ifb_platform::memory_decommit(
            arena_start_ptr,
            decommit_ref.cache.arena_size);
    }
}

inline void 
ifb_memory::arena_decommit_step_4_update_arena_start_array(
    IFBMemoryArenaDecommit& decommit_ref) {

    if (decommit_ref.result) {

        //update the array        
        const ifb::u32 arena_index = decommit_ref.context->handle_arena.h32;
        decommit_ref.cache.arena_start_array[arena_index] = 0;
    }
}