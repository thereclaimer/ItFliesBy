#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal-context.hpp"
#include "ifb-engine-internal-memory.hpp"

inline IFBEngineMemory*
ifb_engine::context_get_memory(
    ifb_void) {

    IFBEngineContext& context_ref = ifb_engine::context();

    return(&context_ref.memory);
}

inline IFBEngineContextManagers*
ifb_engine::context_get_managers(
    ifb_void) {

    IFBEngineContext& context_ref = ifb_engine::context();

    IFBEngineContextManagers* managers_ptr = (IFBEngineContextManagers*)ifb_engine::memory_get_pointer(
        &context_ref.memory,
        context_ref.handles.managers);

    return(managers_ptr);
}

inline IFBEngineContextCore*
ifb_engine::context_get_core(
    ifb_void) {

    IFBEngineContext& context_ref = ifb_engine::context();

    IFBEngineContextCore* core_ptr = (IFBEngineContextCore*)ifb_engine::memory_get_pointer(
        &context_ref.memory,
        context_ref.handles.core);

    return(core_ptr);
}

inline IFBEngineConfig*
ifb_engine::context_get_config(
    ifb_void) {

    IFBEngineContext& context_ref = ifb_engine::context();

    IFBEngineConfig* config_ptr = (IFBEngineConfig*)ifb_engine::memory_get_pointer(
        &context_ref.memory,
        context_ref.handles.config);

    return(config_ptr);
}

inline const ifb_ptr 
ifb_engine::context_get_pointer(
    const IFBHND& handle) {

    //get memory
    IFBEngineMemory* engine_memory_ptr = ifb_engine::context_get_memory();

    //get the pointer
    const ifb_ptr pointer = ifb_engine::memory_get_pointer(
        engine_memory_ptr,
        handle);
    
    //we're done
    return(pointer);
}

inline const ifb_ptr 
ifb_engine::context_get_pointer(
    const IFBGHND& global_handle) {

    //get memory
    IFBEngineMemory* engine_memory_ptr = ifb_engine::context_get_memory();

    //get the pointer
    const ifb_ptr pointer = ifb_engine::memory_get_pointer(
        engine_memory_ptr,
        global_handle);
    
    //we're done
    return(pointer);
}
