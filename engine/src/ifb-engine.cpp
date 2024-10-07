#pragma once

#include "ifb-engine-internal.hpp"

#include "ifb-engine-core.cpp"
#include "ifb-engine-asset.cpp"

ifb_external const IFBEngineHandle 
ifb_engine::engine_startup(
    const RHNDMemoryReservation r_memory_reservation_handle) {

    //sanity check
    r_b8 result = (
        r_memory_reservation_handle != NULL);

    if (!result) {
        return(NULL);
    }

    //configurations
    const r_size core_arena_size  = r_mem::size_megabytes(64);
    const r_size core_arena_count = 2; 

    //get a region for the engine core
    const RHNDMemoryRegion r_region_engine_core = 
        r_mem::region_create_arena_pool(
            r_memory_reservation_handle,
            "IFB ENGINE CORE",
            core_arena_size,
            core_arena_count);

    result &= r_region_engine_core != NULL;

    //commit the arenas for the core memory
    const RHNDMemoryArena r_arena_handle_system = r_mem::arena_commit(r_region_engine_core);
    const RHNDMemoryArena r_arena_handle_frame  = r_mem::arena_commit(r_region_engine_core);
    
    //push the engine struct onto the arena
    const r_size engine_size      = sizeof(IFBEngine);
    const r_size engine_alignment = alignof(IFBEngine);
    IFBEngine* engine_ptr = 
        (IFBEngine*)r_mem::arena_push_aligned(
            r_arena_handle_system,
            engine_size,
            engine_alignment);
    result &= engine_ptr != NULL;

    //initialize the engine core
    result &= ifb_engine::core_initialize(
        r_memory_reservation_handle,
        r_region_engine_core,
        r_arena_handle_system,
        r_arena_handle_frame,
        engine_ptr->core);

    //we're done
    return(result ? engine_ptr : NULL);
}

ifb_external const ifb_b8
ifb_engine::engine_shutdown(
    const IFBEngineHandle ifb_engine_handle) {

    //TODO(SAM)

    return(true);
}