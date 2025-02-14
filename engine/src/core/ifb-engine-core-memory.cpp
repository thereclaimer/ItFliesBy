#pragma once

#include "ifb-engine-internal-context.hpp"

/**********************************************************************************/
/* RESERVE/RELEASE                                                                */
/**********************************************************************************/

inline const ifb_b8
ifb_engine::context_memory_reserve(
          IFBEngineCore* core_ptr,
    const ifb_u32        size) {
    
    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(size);

    //reserve the memory
    const IFBMemoryReservationHandle reservation_handle = ifb_memory::reserve_memory(size);
    if (ifb_memory_macro_handle_valid(reservation_handle)) return(false);

    //get the actual reservation size
    IFBMemoryReservationInfo reservation_info;
    ifb_b8 result = ifb_memory::reservation_get_info(
        reservation_handle,
        &reservation_info);
    ifb_macro_assert(result);

    //initialize the reservation structure 
    core_ptr->memory.reservation.handle = reservation_handle; 
    core_ptr->memory.reservation.size   = reservation_info.size_total;
    
    //we're done
    return(result);
}

inline const ifb_b8
ifb_engine::context_memory_release(
    IFBEngineCore* core_ptr) {

    //sanity check
    ifb_macro_assert(core_ptr);

    //cache the reservation
    IFBEngineCoreMemoryReservation& reservation_ref = core_ptr->memory.reservation;

    //release it
    const ifb_b8 result = ifb_memory::release_memory(reservation_ref.handle);

    //null the structure
    reservation_ref.handle.offset = 0;
    reservation_ref.size          = 0;

    //we're done
    return(result);
}   

/**********************************************************************************/
/* SINGLETONS                                                                     */
/**********************************************************************************/

inline const IFBEngineSingletonHandle
ifb_engine::core_memory_singleton_commit(
          IFBEngineCore* core_ptr,
    const ifb_u32        size,
    const ifb_u32        alignment) {

    ifb_b8 result = true;

    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(size);

    //create the handle
    IFBEngineSingletonHandle singleton_handle;
    singleton_handle.value = ifb_memory::stack_push(size, alignment);

    //we're done
    return(singleton_handle);
}

inline const ifb_ptr
ifb_engine::core_memory_singleton_load(
          IFBEngineCore*           core_ptr,
    const IFBEngineSingletonHandle singleton_handle) {

    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(singleton_handle.value);

    //get the singleton pointer from the stack
    const ifb_ptr singleton_ptr = ifb_memory::stack_get_pointer(singleton_handle.value);

    //we're done    
    return(singleton_ptr);
}

/**********************************************************************************/
/* ARENAS                                                                         */
/**********************************************************************************/

inline const IFBMemoryArenaHandle
ifb_engine::core_memory_arena_commit_unmanaged(
          IFBEngineCore* core_ptr,
    const ifb_u32        size) {

    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(size);

    //cache the reservation
    IFBEngineCoreMemoryReservation& reservation_ref = core_ptr->memory.reservation;

    //commit the arena
    const IFBMemoryArenaHandle arena_handle = ifb_memory::reservation_commit_arena(
        reservation_ref.handle,
        size);

    //sanity check
    const ifb_b8 result = ifb_memory_macro_handle_valid(arena_handle);
    ifb_macro_assert(result);

    //we're done
    return(arena_handle);
}

inline const IFBMemoryLinearArenaHandle
ifb_engine::core_memory_arena_commit_linear(
          IFBEngineCore* core_ptr,
    const ifb_u32        size) {

    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(size);

    //cache the reservation
    IFBEngineCoreMemoryReservation& reservation_ref = core_ptr->memory.reservation;

    //commit the arena
    const IFBMemoryLinearArenaHandle linear_arena_handle = ifb_memory::reservation_commit_linear_arena(
        reservation_ref.handle,
        size);

    //sanity check
    const ifb_b8 result = ifb_memory_macro_handle_valid(linear_arena_handle);
    ifb_macro_assert(result);

    //we're done
    return(linear_arena_handle);
}

inline const IFBMemoryBlockArenaHandle
ifb_engine::core_memory_arena_commit_block(
          IFBEngineCore* core_ptr,
    const ifb_u32        block_size,
    const ifb_u32        block_count) {

    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(block_size);
    ifb_macro_assert(block_count);

    //cache the reservation
    IFBEngineCoreMemoryReservation& reservation_ref = core_ptr->memory.reservation;

    //commit the arena
    const IFBMemoryBlockArenaHandle block_arena_handle = ifb_memory::reservation_commit_linear_arena(
        reservation_ref.handle,
        block_size,
        block_count);

    //sanity check
    const ifb_b8 result = ifb_memory_macro_handle_valid(block_arena_handle);
    ifb_macro_assert(result);

    //we're done
    return(block_arena_handle);
}