#pragma once

#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal-memory.hpp"

inline ifb_void
ifb_engine::core_managers_create_all(
    IFBEngineCoreManagerHandles& ref_core_managers) {

    const ifb_u32 arena_size  = IFB_ENGINE_CORE_DEFAULT_ARENA_SIZE;
    const ifb_u32 arena_count = IFB_ENGINE_CORE_DEFAULT_ARENA_COUNT;

    ref_core_managers.arena = ifb_engine::arena_manager_create(
        arena_size,
        arena_count);
}

inline IFBEngineMemoryManager*
ifb_engine::core_managers_get_pointer_memory_manager(
    const IFBEngineCoreManagerHandles& ref_core_managers) {

    IFBEngineMemoryManager* ptr_memory_manager = ifb_engine::memory_global_pointer(ref_core_managers.memory.value);

    return(ptr_memory_manager);
}

inline IFBEngineTagManager*
ifb_engine::core_managers_get_pointer_tag_manager(
    const IFBEngineCoreManagerHandles& ref_core_managers) {

    IFBEngineTagManager* ptr_tag_manager = ifb_engine::memory_global_pointer(ref_core_managers.tag.value);

    return(ptr_tag_manager);        
}

inline IFBEngineArenaManager*
ifb_engine::core_managers_get_pointer_arena_manager(
    const IFBEngineCoreManagerHandles& ref_core_managers) {

    IFBEngineArenaManager* ptr_arena_manager = ifb_engine::memory_global_pointer(ref_core_managers.arena.value);

    return(ptr_arena_manager);
}