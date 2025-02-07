#pragma once

#include "ifb-engine-internal-context.hpp"
#include "ifb-engine-internal-config.hpp"

/**********************************************************************************/
/* CONTEXT                                                                        */
/**********************************************************************************/

struct IFBEngineContext {
    IFBEngineConfig config;
    IFBPlatformApi  platform_api;
    IFBMemory*      memory;
};

ifb_global IFBEngineContext _context;

/**********************************************************************************/
/* CREATE/DESTROY                                                                 */
/**********************************************************************************/

ifb_api const ifb_b8
ifb_engine::context_create(
    const IFBPlatformApi& platform_api_ref) {

    ifb_b8 result = true;

    //set the platform api
    _context.platform_api = platform_api_ref;

    //get the config
    ifb_engine::config_get_values(_context.config);

    //reserve the memory
    result &= ifb_engine::memory_reserve();


    return(result);
}

ifb_api const ifb_b8
ifb_engine::context_destroy(
    ifb_void) {

    return(false);
}

/**********************************************************************************/
/* STARTUP/SHUTDOWN                                                               */
/**********************************************************************************/

ifb_api const ifb_b8
ifb_engine::context_startup(
    ifb_void) {

    return(false);
}

ifb_api const ifb_b8
ifb_engine::context_shutdown(
    ifb_void) {

    return(false);
}

/**********************************************************************************/
/* RENDERING                                                                      */
/**********************************************************************************/

ifb_api const ifb_b8
ifb_engine::context_render_frame(
    ifb_void) {

    return(false);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/
