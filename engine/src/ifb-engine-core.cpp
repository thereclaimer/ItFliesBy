#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal.hpp"

#include <string.h>

ifb_internal const r_b8 
ifb_engine::core_initialize(
    const RMemoryReservationHandle in_rhnd_reservation_ifb,
    const RMemoryRegionHandle      in_rhnd_region_engine_core,
    const RMemoryArenaHandle       in_rhnd_arena_system,
    const RMemoryArenaHandle       in_rhnd_arena_frame,
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

ifb_internal ifb_memory 
ifb_engine::core_system_memory_push(
    const ifb_size size) {

    IFBEngineCore& core_ref = ifb_engine::core_ref();

    ifb_memory system_memory = r_mem::arena_push(
        core_ref.memory.rhnd_arena_system,
        size);
    
    return(system_memory);
}

ifb_internal ifb_memory 
ifb_engine::core_system_memory_push_aligned(
    const ifb_size size, 
    const ifb_size alignment) {
    
    IFBEngineCore& core_ref = ifb_engine::core_ref();

    ifb_memory system_memory = r_mem::arena_push_aligned(
        core_ref.memory.rhnd_arena_system,
        size,
        alignment);
    
    return(system_memory);
}

ifb_internal const ifb_cstr 
ifb_engine::core_system_memory_push_cstring(
    const ifb_cstr string) {

    //get the string length
    const ifb_size string_length = strnlen_s(string,IFB_ENGINE_CORE_MEMORY_CSTRING_MAX_SIZE);

    //push the string onto the system arena
    const ifb_cstr string_memory = (ifb_cstr)ifb_engine::core_system_memory_push(string_length);

    //if that succeeded, copy the string data
    if (string_memory) {
        memmove(
            string_memory,
            string,
            string_length);
    }

    //we're done
    return(string_memory);
}

ifb_internal const RMemoryRegionHandle
ifb_engine::core_memory_create_arena_pool(
    const ifb_cstr region_tag,
    const ifb_size arena_size,
    const ifb_size arena_count) {

    IFBEngineCore& core_ref = ifb_engine::core_ref();

    const RMemoryRegionHandle region_handle = r_mem::region_create_arena_pool(
        core_ref.memory.rhnd_reservation_ifb,
        region_tag,
        arena_size,
        arena_count);

    return(region_handle);
}