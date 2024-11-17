#pragma once

#include "ifb-engine-internal.hpp"

#include "ifb-engine-core.cpp"
#include "ifb-engine-memory.cpp"
#include "ifb-engine-algorithms.cpp"
#include "ifb-engine-asset.cpp"
#include "ifb-engine-tag.cpp"
#include "ifb-engine-allocator-manager.cpp"


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
        _engine_context->state = IFBEngineState_Fatal;
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
    _engine_context->platform.page_size        = platform_info_ref.page_size;
    _engine_context->platform.page_count_total = platform_info_ref.reservation_size / platform_info_ref.page_size;
    _engine_context->platform.page_count_used  = 1;

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

    _engine_context->state = IFBEngineState_Startup;

    ifb_b8 result = true;

    //we're done
    return(result);
}

ifb_api const ifb_b8
ifb_engine::engine_frame_start(
    ifb_void) {

    //set state to frame start
    _engine_context->state = IFBEngineState_FrameStart;
    
    //set state to frame ready
    _engine_context->state = IFBEngineState_FrameReady;
    
    //we're done
    return(true);
}

ifb_api const ifb_b8
ifb_engine::engine_frame_render(
    ifb_void) {

    //set state to frame render
    _engine_context->state = IFBEngineState_FrameRender;


    //set state to idle
    _engine_context->state = IFBEngineState_Idle;

    //we're done
    return(true);
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

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/
