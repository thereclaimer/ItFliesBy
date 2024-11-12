#pragma once

#include "ifb-engine-memory.cpp"
#include "ifb-engine-asset.cpp"

#include "ifb-engine-internal.hpp"

/**********************************************************************************/
/* EXTERNAL                                                                       */
/**********************************************************************************/

ifb_external IFBEngineContext*
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
        return(NULL);
    }

    //commit the first page for the context
    const ifb_memory context_memory = ifb_engine::platform_memory_pages_commit(memory_reservation_start,memory_page_size);
    if (context_memory != memory_reservation_start) {
        return(NULL);
    }

    //if that worked, cast the struct
    IFBEngineContext* context_ptr = (IFBEngineContext*)context_memory;     
    
    //set the memory info
    context_ptr->memory.page_size        = memory_page_size;
    context_ptr->memory.page_count_total = memory_page_count;
    context_ptr->memory.page_count_used  = 1;    

    //create the core systems
    result &= ifb_engine::asset_manager_create(context_ptr);

    //we're done
    return(context_ptr);
}

ifb_external const ifb_b8
ifb_engine::engine_startup(
    IFBEngineContext* engine_context) {

    return(true);
}

ifb_external const ifb_b8
ifb_engine::engine_frame_start(
    IFBEngineContext* engine_context) {

    return(true);
}

ifb_external const ifb_b8
ifb_engine::engine_frame_render(
    IFBEngineContext* engine_context) {

    return(true);
}

ifb_external const ifb_b8
ifb_engine::engine_shutdown(
    IFBEngineContext* engine_context) {

    return(true);
}

ifb_external const ifb_b8
ifb_engine::engine_destroy_context(
    IFBEngineContext* engine_context) {

    return(true);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/
