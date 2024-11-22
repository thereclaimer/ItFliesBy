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
    IFBEnginePlatformInfo& platform_info_ref,
    IFBEnginePlatformApi&  platform_api_ref) {

    //validate the arguments
    ifb_b8 result = true;
    result &= platform_info_ref.reservation_start != NULL;
    result &= platform_info_ref.reservation_size  >= ifb_engine::math_size_gigabytes(4);
    result &= platform_info_ref.page_size         >= sizeof(IFBEngineContext);
    result &= ifb_engine::platform_api_validate(platform_api_ref);
    if (!result) {
        return(false);
    }

    //commit the first page for the context
    const ifb_memory context_memory = ifb_engine::platform_memory_pages_commit(platform_info_ref.reservation_start,platform_info_ref.page_size);
    if (context_memory != platform_info_ref.reservation_start) {
        return(false);
    }

    //if that worked, cast the struct
    _engine_context = (IFBEngineContext*)context_memory;     
    
    //set the memory info
    _engine_context->platform.memory_page_size        = platform_info_ref.page_size;
    _engine_context->platform.memory_page_count_total = platform_info_ref.reservation_size / platform_info_ref.page_size;
    _engine_context->platform.memory_page_count_used  = 1;

    //initialize the engine core
    result &= ifb_engine::core_routine_initialize();

    //update state
    _engine_context->state = result
        ? IFBEngineState_NotRunning
        : IFBEngineState_Fatal;          

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

    //get the frame stack
    const IFBEngineStackAllocatorId platform_stack = ifb_engine::core_stack_allocator_platform();
    
    //do the push
    const ifb_memory stack_memory = ifb_engine::stack_allocator_push_memory(platform_stack,size);
    
    //we're done
    return(stack_memory);
}

ifb_api const ifb_memory
ifb_engine::engine_frame_alloc(
    const ifb_u32 size) {

    //get the frame stack
    const IFBEngineStackAllocatorId frame_stack = ifb_engine::core_stack_allocator_frame();
    
    //do the push
    const ifb_memory stack_memory = ifb_engine::stack_allocator_push_memory(frame_stack,size);
    
    //we're done
    return(stack_memory);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/