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
    ifb_engine::globals_initialize();

    //get the context pointer
    IFBEngineContext* ptr_engine_context = ifb_engine::globals_get_context_pointer();
    ifb_macro_assert(ptr_engine_context);

    //initialize the engine core
    result &= ifb_engine::core_routine_initialize();

    //update state
    _engine_context->state = IFBEngineState_NotRunning;

    //finally, set the initialization time
    ptr_engine_context->time_initialized = ifb_engine::platform_system_time_ms();

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