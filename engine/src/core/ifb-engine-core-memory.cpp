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
    const IFBU64         size) {
    
    //sanity check
    ifb_macro_assert(core_ptr);
    ifb_macro_assert(size);

    IFBEngineCoreMemory& ref_core_memory = core_ptr->memory;;

    //reserve the memory
    IFBMemoryReservation* ptr_reservation = ifb_memory::context_reserve_platform_memory(
        ref_core_memory.ptr_memory_context,
        size);
    if (!ptr_reservation) return(false);

    //initialize the reservation structure
    IFBEngineCoreMemoryReservation& reservation = core_ptr->memory.reservation;
    reservation.ptr_reservation = ptr_reservation; 
    reservation.size_arena      = IFB_ENGINE_CORE_MEMORY_ARENA_SIZE;

    //we're done
    return(true);
}

inline const IFBB8
ifb_engine::core_memory_release_platform_memory(
    IFBEngineCore* core_ptr) {

    //sanity check
    ifb_macro_assert(core_ptr);

    //cache the reservation
    IFBEngineCoreMemoryReservation& reservation_ref = core_ptr->memory.reservation;

    //release it
    const IFBB8 result = ifb_memory::context_release_platform_memory(reservation_ref.ptr_reservation);
    if (!result) return(false);

    //null the structure
    reservation_ref.ptr_reservation = NULL;

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

    IFBEngineCoreMemory& core_memory_ref = core_ptr->memory;

    //do the commit 
    const IFBPtr pointer = ifb_memory::context_stack_commit_absolute(
        core_memory_ref.ptr_memory_context,
        size,
        alignment);

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

    IFBEngineCoreMemory& core_memory_ref = core_ptr->memory;

    //do the commit 
    const IFBU32 offset = ifb_memory::context_stack_commit_relative(
        core_memory_ref.ptr_memory_context,
        size,
        alignment);

    //sanity check again
    ifb_macro_assert(offset);

    //we're done
    return(offset);
}

/**********************************************************************************/
/* ARENAS                                                                         */
/**********************************************************************************/

inline IFBMemoryArena* 
ifb_engine::core_memory_commit_arena(
    IFBEngineCore* core_ptr) {

    //get the reservation
    IFBEngineCoreMemoryReservation& ref_reservation = ifb_engine::core_memory_get_and_validate_reservation(core_ptr);

    //commit the arena
    IFBMemoryArena* ptr_arena = ifb_memory::reservation_commit_arena(
        ref_reservation.ptr_reservation,
        ref_reservation.size_arena);

    //sanity check
    ifb_macro_assert(ptr_arena);

    //we're done
    return(ptr_arena);
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
    ifb_macro_assert(ref_reservation.ptr_reservation);
    ifb_macro_assert(ref_reservation.size_arena);

    //we're done
    return(ref_reservation);
}