#pragma once


#include "ifb-engine-core.cpp"
#include "ifb-engine-asset.cpp"

#include "ifb-engine-internal.hpp"

ifb_external const IFBEngineHandle 
ifb_engine::engine_startup(
    const RMemoryReservationHandle r_memory_reservation_handle) {

    //sanity check
    r_b8 result = (
        r_memory_reservation_handle != NULL);

    if (!result) {
        return(NULL);
    }

    //configurations
    const r_size core_arena_size        = r_mem::size_megabytes(64);
    const r_size core_arena_count       = 2; 
    const r_size asset_data_arena_size  = r_mem::size_kilobytes(64);
    const r_size asset_data_arena_count = 1024;

    //get a region for the engine core
    const RMemoryRegionHandle r_region_engine_core = 
        r_mem::region_create_arena_pool(
            r_memory_reservation_handle,
            "IFB ENGINE CORE",
            core_arena_size,
            core_arena_count);

    result &= r_region_engine_core != NULL;

    //commit the arenas for the core memory
    const RMemoryArenaHandle r_arena_handle_system = r_mem::arena_commit(r_region_engine_core);
    const RMemoryArenaHandle r_arena_handle_frame  = r_mem::arena_commit(r_region_engine_core);
    
    //push the engine struct onto the arena
    const r_size engine_size      = sizeof(IFBEngine);
    const r_size engine_alignment = alignof(IFBEngine);
    _ifb_engine_ptr = 
        (IFBEngine*)r_mem::arena_push_aligned(
            r_arena_handle_system,
            engine_size,
            engine_alignment);
    result &= _ifb_engine_ptr != NULL;

    //initialize the engine core
    result &= ifb_engine::core_initialize(
        r_memory_reservation_handle,
        r_region_engine_core,
        r_arena_handle_system,
        r_arena_handle_frame,
        _ifb_engine_ptr->core);

    //initialize the asset manager
    result &= ifb_engine::asset_manager_create(
        asset_data_arena_size,
        asset_data_arena_count,
        _ifb_engine_ptr->asset_manager);

    //we're done
    return(result ? _ifb_engine_ptr : NULL);
}

ifb_external const ifb_b8
ifb_engine::engine_shutdown(
    const IFBEngineHandle ifb_engine_handle) {

    //TODO(SAM)

    return(true);
}