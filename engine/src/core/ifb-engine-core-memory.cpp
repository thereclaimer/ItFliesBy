#pragma once

#include "ifb-engine-internal-core.hpp"

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

inline const IFBB8
ifb_engine::core_memory_reserve(
          IFBEngineCore* core_ptr,
    const IFBU32        size) {
    
    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(size);

    //reserve the memory
    const IFBHNDMemoryReservation reservation_handle = ifb_memory::reserve_memory(size);
    if (ifb_memory_macro_handle_valid(reservation_handle)) return(false);

    //get the actual reservation size
    IFBMemoryReservationInfo reservation_info;
    IFBB8 result = ifb_memory::reservation_get_info(
        reservation_handle,
        &reservation_info);
    ifb_macro_assert(result);

    //initialize the reservation structure 
    core_ptr->memory.reservation.handle = reservation_handle; 
    core_ptr->memory.reservation.size   = reservation_info.size_total;
    
    //we're done
    return(result);
}

inline const IFBB8
ifb_engine::core_memory_release(
    IFBEngineCore* core_ptr) {

    //sanity check
    ifb_macro_assert(core_ptr);

    //cache the reservation
    IFBEngineCoreMemoryReservation& reservation_ref = core_ptr->memory.reservation;

    //release it
    const IFBB8 result = ifb_memory::release_memory(reservation_ref.handle);

    //null the structure
    reservation_ref.handle.offset = 0;
    reservation_ref.size          = 0;

    //we're done
    return(result);
}   

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

inline const IFBPtr
ifb_engine::core_memory_stack_commit_absolute(
          IFBEngineCore* core_ptr,
    const IFBU32        size,
    const IFBU32        alignment) {

    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(size);

    //do the push and get the pointer
    const IFBU32 stack_position = ifb_memory::stack_push(size,alignment);
    const IFBPtr pointer        = ifb_memory::stack_get_pointer(stack_position);

    //sanity check again
    ifb_macro_assert(stack_position);
    ifb_macro_assert(pointer);

    //we're done
    return(pointer);
}

inline const IFBU32
ifb_engine::core_memory_stack_commit_relative(
          IFBEngineCore* core_ptr,
    const IFBU32        size,
    const IFBU32        alignment) {
    
    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(size);

    //do the push and get the pointer
    const IFBU32 stack_position = ifb_memory::stack_push(size,alignment);

    //sanity check again
    ifb_macro_assert(stack_position);

    //we're done
    return(stack_position);
}

/**********************************************************************************/
/* ARENAS                                                                         */
/**********************************************************************************/

inline const IFBHNDMemoryArena
ifb_engine::core_memory_arena_commit_unmanaged(
          IFBEngineCore* core_ptr,
    const IFBU32        size) {

    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(size);

    //cache the reservation
    IFBEngineCoreMemoryReservation& reservation_ref = core_ptr->memory.reservation;

    //commit the arena
    const IFBHNDMemoryArena arena_handle = ifb_memory::reservation_commit_arena_unmanaged(
        reservation_ref.handle,
        size);

    //sanity check
    const IFBB8 result = ifb_memory_macro_handle_valid(arena_handle);
    ifb_macro_assert(result);

    //we're done
    return(arena_handle);
}

inline const IFBHNDMemoryArenaLinear
ifb_engine::core_memory_arena_commit_linear(
          IFBEngineCore* core_ptr,
    const IFBU32        size) {

    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(size);

    //cache the reservation
    IFBEngineCoreMemoryReservation& reservation_ref = core_ptr->memory.reservation;

    //commit the arena
    const IFBHNDMemoryArenaLinear linear_arena_handle = ifb_memory::reservation_commit_arena_linear(
        reservation_ref.handle,
        size);

    //sanity check
    const IFBB8 result = ifb_memory_macro_handle_valid(linear_arena_handle);
    ifb_macro_assert(result);

    //we're done
    return(linear_arena_handle);
}

inline const IFBHNDMemoryArenaBlock
ifb_engine::core_memory_arena_commit_block(
          IFBEngineCore* core_ptr,
    const IFBU32        block_size,
    const IFBU32        block_count) {

    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(block_size);
    ifb_macro_assert(block_count);

    //cache the reservation
    IFBEngineCoreMemoryReservation& reservation_ref = core_ptr->memory.reservation;

    //commit the arena
    const IFBHNDMemoryArenaBlock block_arena_handle = ifb_memory::reservation_commit_arena_block(
        reservation_ref.handle,
        block_size,
        block_count);

    //sanity check
    const IFBB8 result = ifb_memory_macro_handle_valid(block_arena_handle);
    ifb_macro_assert(result);

    //we're done
    return(block_arena_handle);
}