#pragma once

#include "ifb-engine-algorithms.cpp"
#include "ifb-engine-memory.cpp"
#include "ifb-engine-asset.cpp"
#include "ifb-engine-tag.cpp"
#include "ifb-engine-allocator-manager.cpp"

#include "ifb-engine-internal.hpp"

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
    _engine_context->memory.page_size        = platform_info_ref.page_size;
    _engine_context->memory.page_count_total = platform_info_ref.reservation_size / platform_info_ref.page_size;
    _engine_context->memory.page_count_used  = 1;

    //set the state
    _engine_context->state = IFBEngineState_Idle;

    //we're done
    return(result);
}

ifb_api const ifb_b8
ifb_engine::engine_startup(
    ifb_void) {

    ifb_b8 result = true;

    //start the core systems
    _engine_context->core.system_handles.memory_manager    = ifb_engine::memory_manager_startup();
    _engine_context->core.system_handles.tag_table         = ifb_engine::tag_table_create();
    _engine_context->core.system_handles.allocator_manager = ifb_engine::allocator_manager_start_up();

    //sanity check
    result &= ifb_engine::memory_handle_valid(_engine_context->core.system_handles.memory_manager);
    result &= ifb_engine::memory_handle_valid(_engine_context->core.system_handles.tag_table);
    result &= ifb_engine::memory_handle_valid(_engine_context->core.system_handles.allocator_manager);

    //get core stack allocators
    _engine_context->core.stack_allocators.frame    = ifb_engine::stack_allocator_create(IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_FRAME,   IFB_ENGINE_CORE_STACK_SIZE);
    _engine_context->core.stack_allocators.platform = ifb_engine::stack_allocator_create(IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_PLATFORM,IFB_ENGINE_CORE_STACK_SIZE);
    _engine_context->core.stack_allocators.window   = ifb_engine::stack_allocator_create(IFB_ENGINE_CORE_STACK_ALLOCATOR_TAG_WINDOW,  IFB_ENGINE_CORE_STACK_SIZE);

    //sanity check
    result &= ifb_engine::stack_allocator_valid(_engine_context->core.stack_allocators.frame);
    result &= ifb_engine::stack_allocator_valid(_engine_context->core.stack_allocators.platform);
    result &= ifb_engine::stack_allocator_valid(_engine_context->core.stack_allocators.window);

    return(result);
}

ifb_api const ifb_b8
ifb_engine::engine_frame_start(
    ifb_void) {

    return(true);
}

ifb_api const ifb_b8
ifb_engine::engine_frame_render(
    ifb_void) {

    //clear the frame stack
    ifb_engine::stack_allocator_reset(_engine_context->core.stack_allocators.frame);

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
