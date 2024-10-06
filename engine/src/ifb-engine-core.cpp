#include "ifb-engine-internal-core.hpp"

ifb_internal const r_b8 
ifb_engine::core_initialize(
    const RHNDMemoryReservation in_rhnd_reservation_ifb,
    const RHNDMemoryRegion      in_rhnd_region_engine_core,
    const RHNDMemoryArena       in_rhnd_arena_system,
    const RHNDMemoryArena       in_rhnd_arena_frame,
            IFBEngineCore&     out_engine_core_ref) {

    //sanity check
    ifb_b8 result = (
        in_rhnd_reservation_ifb    != NULL &&
        in_rhnd_region_engine_core != NULL &&
        in_rhnd_arena_system       != NULL &&
        in_rhnd_arena_frame        != NULL);

    //initialize the memory struct
    IFBEngineCoreMemory& core_memory_ref    = out_engine_core_ref.memory;
    core_memory_ref.rhnd_reservation_ifb    = in_rhnd_reservation_ifb;
    core_memory_ref.rhnd_region_engine_core = in_rhnd_region_engine_core;
    core_memory_ref.rhnd_arena_system       = in_rhnd_arena_system;
    core_memory_ref.rhnd_arena_frame        = in_rhnd_arena_frame;

    return(result);
}