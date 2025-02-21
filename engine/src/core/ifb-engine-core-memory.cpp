#pragma once

#include "ifb-engine-internal-core.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_engine {

    IFBEngineCoreMemoryReservation& core_memory_get_and_validate_reservation(IFBEngineCore* core_ptr);
};

/**********************************************************************************/
/* RESERVATION                                                                    */
/**********************************************************************************/

inline const IFBB8
ifb_engine::core_memory_reserve_platform_memory(
          IFBEngineCore* core_ptr,
    const IFBU32         size) {
    
    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(size);

    //reserve the memory
    const IFBHNDReservation reservation_handle = ifb_memory::context_reserve_platform_memory(size);
    if (ifb_memory_macro_handle_valid(reservation_handle)) return(false);

    //get the actual reservation size
    IFBReservationInfo reservation_info;
    IFBB8 result = ifb_memory::reservation_get_info(
        reservation_handle,
        &reservation_info);
    ifb_macro_assert(result);

    //initialize the reservation structure
    IFBEngineCoreMemoryReservation& reservation = core_ptr->memory.reservation;
    reservation.handle        = reservation_handle; 
    reservation.size_reserved = reservation_info.size_total;
    reservation.size_arena    = IFB_ENGINE_CORE_MEMORY_ARENA_SIZE;

    //we're done
    return(result);
}

inline const IFBB8
ifb_engine::core_memory_release_platform_memory(
    IFBEngineCore* core_ptr) {

    //sanity check
    ifb_macro_assert(core_ptr);

    //cache the reservation
    IFBEngineCoreMemoryReservation& reservation_ref = core_ptr->memory.reservation;

    //release it
    const IFBB8 result = ifb_memory::context_release_platform_memory(reservation_ref.handle);
    if (!result) return(false);

    //null the structure
    reservation_ref.handle.offset = 0;
    reservation_ref.size_reserved = 0;

    //we're done
    return(true);
}   

/**********************************************************************************/
/* STACK                                                                          */
/**********************************************************************************/

inline const IFBPtr
ifb_engine::core_memory_commit_bytes_absolute(
          IFBEngineCore* core_ptr,
    const IFBU32         size,
    const IFBU32         alignment) {

    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(size);

    //do the commit 
    const IFBPtr pointer = ifb_memory::context_stack_commit_absolute(size,alignment);

    //sanity check again
    ifb_macro_assert(pointer);

    //we're done
    return(pointer);
}

inline const IFBU32
ifb_engine::core_memory_commit_bytes_relative(
          IFBEngineCore* core_ptr,
    const IFBU32         size,
    const IFBU32         alignment) {
    
    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(size);

    //do the commit 
    const IFBU32 offset = ifb_memory::context_stack_commit_relative(size,alignment);

    //sanity check again
    ifb_macro_assert(offset);

    //we're done
    return(offset);
}

/**********************************************************************************/
/* ARENAS                                                                         */
/**********************************************************************************/

inline const IFBHNDArena 
ifb_engine::core_memory_commit_arena(
    IFBEngineCore* core_ptr) {

    //get the reservation
    IFBEngineCoreMemoryReservation& ref_reservation = ifb_engine::core_memory_get_and_validate_reservation(core_ptr);

    //commit the arena
    const IFBHNDArena arena_handle = ifb_memory::reservation_commit_arena(
        ref_reservation.handle,
        ref_reservation.size_arena);

    //sanity check
    ifb_macro_assert(arena_handle.offset);

    //we're done
    return(arena_handle);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBEngineCoreMemoryReservation&
ifb_engine::core_memory_get_and_validate_reservation(
    IFBEngineCore* core_ptr) {

    //make sure the core pointer is valid
    ifb_macro_assert(core_ptr);
    
    //get the reservation
    IFBEngineCoreMemoryReservation& ref_reservation = core_ptr->memory.reservation;
    
    //make sure the reservation is initialized
    ifb_macro_assert(ref_reservation.handle.offset);
    ifb_macro_assert(ref_reservation.size_arena);
    ifb_macro_assert(ref_reservation.size_reserved);

    //we're done
    return(ref_reservation);
}