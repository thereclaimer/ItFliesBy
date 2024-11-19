#pragma once

#include "ifb-engine-internal.hpp"

#include "ifb-engine-core-routines.cpp"
#include "ifb-engine-core-tasks.cpp"

inline IFBEngineCore*
ifb_engine::core_pointer_from_context(
    ifb_void) {

    //get the core handle
    const ifb_handle_memory_t core_handle = ifb_engine::context_core_handle();

    //get the pointer
    IFBEngineCore* core_ptr = (IFBEngineCore*)ifb_engine::memory_pointer_from_handle(core_handle);

    //we're done
    return(core_ptr);
}

inline const ifb_handle_memory_t 
ifb_engine::core_manager_handle_memory(
    ifb_void) {

    //get the core pointer
    const IFBEngineCore* core_ptr = ifb_engine::core_pointer_from_context();

    //return the handle
    return(core_ptr->managers.memory);
}

inline const ifb_handle_memory_t 
ifb_engine::core_manager_handle_tag(
    ifb_void) {

    //get the core pointer
    const IFBEngineCore* core_ptr = ifb_engine::core_pointer_from_context();

    //return the handle
    return(core_ptr->managers.tag);
}

inline const ifb_handle_memory_t 
ifb_engine::core_manager_handle_allocators(
    ifb_void) {

    //get the core pointer
    const IFBEngineCore* core_ptr = ifb_engine::core_pointer_from_context();

    //return the handle
    return(core_ptr->managers.allocators);
}

inline const ifb_handle_memory_t 
ifb_engine::core_manager_handle_assets(
    ifb_void) {

    //get the core pointer
    const IFBEngineCore* core_ptr = ifb_engine::core_pointer_from_context();

    //return the handle
    return(core_ptr->managers.assets);

}

inline const ifb_index_stack_t 
ifb_engine::core_stack_allocator_platform(
    ifb_void) {

    //get the core pointer
    const IFBEngineCore* core_ptr = ifb_engine::core_pointer_from_context();

    //return the index
    return(core_ptr->stack_allocators.platform);    
}

inline const ifb_index_stack_t 
ifb_engine::core_stack_allocator_frame(
    ifb_void) {

    //get the core pointer
    const IFBEngineCore* core_ptr = ifb_engine::core_pointer_from_context();

    //return the index
    return(core_ptr->stack_allocators.frame);    
}
