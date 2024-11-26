#pragma once

#include "ifb-engine.hpp"
#include "ifb-engine-internal.hpp"
#include "ifb-engine-core-routines.cpp"
#include "ifb-engine-core-tasks.cpp"
#include "ifb-engine-core-tables.cpp"

inline IFBEngineCore*
ifb_engine::core_pointer_from_context(
    ifb_void) {

    //get the core handle
    const IFBEngineMemoryHandle core_handle = ifb_engine::context_core_handle();

    //get the pointer
    IFBEngineCore* core_ptr = (IFBEngineCore*)ifb_engine::memory_pointer_from_handle(core_handle);

    //we're done
    return(core_ptr);
}

inline const IFBEngineMemoryHandle 
ifb_engine::core_manager_handle_assets(
    ifb_void) {

    //get the core pointer
    const IFBEngineCore* core_ptr = ifb_engine::core_pointer_from_context();

    //return the handle
    return(core_ptr->managers.assets);
}

inline const IFBEngineLinearAllocatorHandle
ifb_engine::core_allocator_linear_platform(
    ifb_void) {

    //get the core pointer
    const IFBEngineCore* core_ptr = ifb_engine::core_pointer_from_context();

    //return the index
    return(core_ptr->allocators.linear_allocators.platform);    
}

inline const IFBEngineLinearAllocatorHandle 
ifb_engine::core_allocator_linear_frame(
    ifb_void) {

    //get the core pointer
    const IFBEngineCore* core_ptr = ifb_engine::core_pointer_from_context();

    //return the index
    return(core_ptr->allocators.linear_allocators.frame);     
}
