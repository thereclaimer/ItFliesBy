#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-memory.hpp"
#include "ifb-engine-core-arena.cpp"
#include "ifb-engine-core-memory.cpp"
#include "ifb-engine-core-tag.cpp"

inline const IFBEngineCoreHandle 
ifb_engine::core_create(
    ifb_void) {

    //allocate the core
    IFBEngineCoreHandle core_handle;
    core_handle.value = ifb_engine_memory_global_push_struct(IFBEngineCore);

    //get the pointer
    IFBEngineCore* ptr_core = ifb_engine::core_get_pointer(core_handle);

    //create the managers
    ptr_core->handles.managers = ifb_engine::managers_create();

    //we're done
    return(core_handle);
}

inline IFBEngineCore*
core_get_pointer(
    const IFBEngineCoreHandle core_handle) {

    //get the pointer
    IFBEngineCore* ptr_core = ifb_engine::memory_global_pointer(core_handle.value);
    ifb_macro_assert(ptr_core);

    return(ptr_core);
}

inline IFBEngineManagers*
core_get_pointer_managers(
    const IFBEngineCore* ptr_core) {

    IFBEngineManagers* ptr_managers = ifb_engine::managers_get_pointer(ptr_core->handles.managers);

    return(ptr_managers);
}