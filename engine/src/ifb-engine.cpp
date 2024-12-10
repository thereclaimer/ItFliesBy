#pragma once

#include "ifb-engine-internal.hpp"

#include "ifb-engine-core.cpp"
#include "ifb-engine-memory.cpp"
#include "ifb-engine-algorithms.cpp"
#include "ifb-engine-asset.cpp"
#include "ifb-engine-tag.cpp"
#include "ifb-engine-allocators.cpp"
#include "ifb-engine-rendering.cpp"
#include "ifb-engine-platform.cpp"
#include "ifb-engine-tables.cpp"
#include "ifb-engine-controllers.cpp"

/**********************************************************************************/
/* API                                                                            */
/**********************************************************************************/

ifb_api const ifb_b8
ifb_engine::engine_create_context(
    IFBPlatformApi& platform_api_ref) {

    //initialize the api
    ifb_engine::platform_initialize(platform_api_ref);

    //global initialization
    ifb_engine::context_reset();
    ifb_engine::context_handles_create_all();

    //get context pointers
    IFBEngineConfig* ptr_config = ifb_engine::context_handles_get_config();
    IFBEngineMemory* ptr_memory = ifb_engine::context_handles_get_memory();

    //get config values
    ifb_engine::config_get_values(config_ptr);

    //reserve memory
    ifb_engine::memory_reserve(
        ptr_memory,
        config_ptr->memory_minimum_gb,
        config_ptr->memory_commit_count_max);

    //create the managers
    ifb_engine::context_initialize_managers();

    //we're done
    return(result);
}

ifb_api const ifb_b8
ifb_engine::engine_startup(
    ifb_void) {

    //set startup state
    _engine_context->state = IFBEngineState_Startup;

    //execute startup routine
    ifb_b8 result = ifb_engine::core_routine_startup();

    //update engine state
    _engine_context->state = (result) 
        ? IFBEngineState_Idle
        : IFBEngineState_Fatal;

    //we're done
    return(result);
}

ifb_api const ifb_b8
ifb_engine::engine_frame_execute(
    ifb_void) {

    ifb_b8 result = true;

    result &= ifb_engine::core_routine_frame_start ();
    result &= ifb_engine::core_routine_frame_render();

    return(result);
}

ifb_api const ifb_b8
ifb_engine::engine_shutdown(
    ifb_void) {

    return(true);
}

ifb_api const ifb_b8
ifb_engine::engine_destroy_context(
    ifb_void) {

    return(true);
}

ifb_api const ifb_memory
ifb_engine::engine_platform_alloc(
    const ifb_u32 size) {

    //get the platform allocator
    const IFBEngineLinearAllocatorHandle platform_allocator = ifb_engine::core_allocator_linear_platform();
    
    //get the memory
    const IFBEngineMemoryHandle memory_handle = ifb_engine::linear_allocator_reserve(platform_allocator,size);
    const ifb_memory memory = ifb_engine::memory_pointer_from_handle(memory_handle);

    //we're done
    return(memory);
}

ifb_api const ifb_memory
ifb_engine::engine_frame_alloc(
    const ifb_u32 size) {

    //get the frame allocator
    const IFBEngineLinearAllocatorHandle frame_allocator = ifb_engine::core_allocator_linear_frame();
    
    //get the memory
    const IFBEngineMemoryHandle memory_handle = ifb_engine::linear_allocator_reserve(frame_allocator,size);
    const ifb_memory memory = ifb_engine::memory_pointer_from_handle(memory_handle);

    //we're done
    return(memory);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBEngineMemory* 
ifb_engine::context_get_engine_memory(
    ifb_void) {

    IFBEngineContext* ptr_context

}

inline IFBEngineCore*   
ifb_engine::context_get_engine_core(
    ifb_void) {

}

inline IFBUserInput*    
ifb_engine::context_get_user_input(
    ifb_void) {

}