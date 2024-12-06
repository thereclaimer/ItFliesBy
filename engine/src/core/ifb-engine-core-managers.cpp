#pragma once

#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal-global.hpp"

inline ifb_void
ifb_engine::core_managers_create_all(
    IFBEngineCoreManagers& ref_core_managers) {

    //get the config
    const IFBEngineConfig& ref_config = ifb_engine::globals_get_config_reference(); 

    //memory manager
    ref_core_managers.global_handles.memory = ifb_engine::memory_manager_create(
        ref_config.memory_minimum_gb,
        ref_config.memory_commit_count_max);

    //tag manager
    ref_core_managers.global_handles.tag = ifb_engine::tag_manager_create(
        ref_config.tag_c_str_length,
        ref_config.tag_count_max);

    //arena manager
    ref_core_managers.global_handles.arena = ifb_engine::arena_manager_create(
        ref_config.arena_minimum_kb,
        ref_config.arena_count_max);
}

inline IFBEngineMemoryManager*
ifb_engine::core_managers_get_pointer_memory_manager(
    const IFBEngineCoreManagers& ref_core_managers) {

    IFBEngineMemoryManager* ptr_memory_manager = ifb_engine::memory_global_pointer(ref_core_managers.global_handles.memory);

    return(ptr_memory_manager);
}

inline IFBEngineTagManager*
ifb_engine::core_managers_get_pointer_tag_manager(
    const IFBEngineCoreManagers& ref_core_managers) {

    IFBEngineTagManager* ptr_tag_manager = ifb_engine::memory_global_pointer(ref_core_managers.global_handles.tag);

    return(ptr_tag_manager);        
}

inline IFBEngineArenaManager*
ifb_engine::core_managers_get_pointer_arena_manager(
    const IFBEngineCoreManagers& ref_core_managers) {

    IFBEngineArenaManager* ptr_arena_manager = ifb_engine::memory_global_pointer(ref_core_managers.global_handles.arena);

    return(ptr_arena_manager);
}