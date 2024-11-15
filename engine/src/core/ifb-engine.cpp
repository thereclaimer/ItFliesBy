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
          IFBEnginePlatformApi&   platform_api,
    const ifb_memory              memory_reservation_start,
    const ifb_size                memory_page_size,
    const ifb_size                memory_page_count) {

    //validate the arguments
    ifb_b8 result = true;
    result &= memory_reservation_start != NULL;
    result &= memory_page_size >= IFB_ENGINE_MINIMUM_MEMORY_REQUIREMENT_4GB;
    result &= ifb_engine::platform_api_validate(platform_api);
    if (!result) {
        return(false);
    }

    //commit the first page for the context
    const ifb_memory context_memory = ifb_engine::platform_memory_pages_commit(memory_reservation_start,memory_page_size);
    if (context_memory != memory_reservation_start) {
        return(false);
    }

    //if that worked, cast the struct
    _engine_context = (IFBEngineContext*)context_memory;     
    
    //set the memory info
    _engine_context->memory.page_size        = memory_page_size;
    _engine_context->memory.page_count_total = memory_page_count;
    _engine_context->memory.page_count_used  = 1;

    //create the core systems
    _engine_context->core.handle_memory_manager    = ifb_engine::memory_manager_startup();
    _engine_context->core.handle_tag_table         = ifb_engine::tag_table_create();
    _engine_context->core.handle_allocator_manager = ifb_engine::allocator_manager_start_up();

    //sanity check
    result &= (
        _engine_context->core.handle_memory_manager &&  
        _engine_context->core.handle_tag_table);

    //we're done
    return(result);
}

ifb_api const ifb_b8
ifb_engine::engine_startup(
    IFBEngineContext* engine_context) {

    return(true);
}

ifb_api const ifb_b8
ifb_engine::engine_frame_start(
    IFBEngineContext* engine_context) {

    return(true);
}

ifb_api const ifb_b8
ifb_engine::engine_frame_render(
    IFBEngineContext* engine_context) {

    return(true);
}

ifb_api const ifb_b8
ifb_engine::engine_shutdown(
    IFBEngineContext* engine_context) {

    return(true);
}

ifb_api const ifb_b8
ifb_engine::engine_destroy_context(
    IFBEngineContext* engine_context) {

    return(true);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/
