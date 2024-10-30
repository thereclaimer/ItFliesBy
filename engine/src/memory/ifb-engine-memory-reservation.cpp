#pragma once

#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-internal-platform.hpp"

ifb_internal const ifb_b8 
ifb_engine::memory_reserve(
    IFBEngineMemoryReservation& reservation_ref) {

    //get the platform reservation
    const ifb_size   reservation_size  = ifb_engine::memory_size_gigabytes(IFB_ENGINE_MEMORY_RESERVATION_SIZE_GIGABYTES);
    const ifb_memory reservation_start = ifb_engine::platform_memory_pages_reserve(reservation_size);  

    //initialize the struct
    reservation_ref.size_total = reservation_size;
    reservation_ref.size_used  = 0;
    reservation_ref.start      = reservation_start;

    //we're done
    return(reservation_start != NULL);
}

ifb_internal const ifb_b8 
ifb_engine::memory_release(
    IFBEngineMemoryReservation& reservation_ref) {

    //release the reservation
    const ifb_b8 result = ifb_engine::platform_memory_pages_release(
        reservation_ref.start,
        reservation_ref.size_total);

    //we're done
    return(result);
}