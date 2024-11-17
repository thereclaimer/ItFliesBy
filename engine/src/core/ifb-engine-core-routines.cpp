#pragma once

#include "ifb-engine-internal-core.hpp"
#include "ifb-engine-internal.hpp"

inline const ifb_b8 
ifb_engine::core_routine_initialize(
    ifb_void) {

    ifb_b8 result = true;

    //create the handle
    ifb_handle_memory_t core_memory_handle;
    result &= ifb_engine::core_task_create_core_handle(core_memory_handle);

    //get pointer
    IFBEngineCore* engine_core_ptr = (IFBEngineCore*)ifb_engine::memory_pointer_from_handle(core_memory_handle);

    //create the managers and allocators
    result &= ifb_engine::core_task_create_managers         (engine_core_ptr->managers);
    result &= ifb_engine::core_task_create_stack_allocators (engine_core_ptr->stack_allocators);

    //update the context
    _engine_context->core_handle = core_memory_handle;

    //we're done
    return(result);
}

inline const ifb_b8 
ifb_engine::core_routine_startup(
    ifb_void) {

    return(false);
}