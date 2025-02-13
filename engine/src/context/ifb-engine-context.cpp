#pragma once

#include "ifb-engine-internal-context.hpp"
#include "ifb-engine-internal-config.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                                 */
/**********************************************************************************/


ifb_global IFBEngineContext _context;

/**********************************************************************************/
/* CREATE/DESTROY                                                                 */
/**********************************************************************************/

ifb_engine_api const ifb_b8
ifb_engine::context_create(
    const IFBPlatformApi& platform_api_ref) {

    ifb_b8 result = true;

    //set the platform api
    ifb_platform::set_api(platform_api_ref);

    //get the config
    ifb_engine::config_get_values(_context.config);

    //we're done
    return(result);
}

ifb_engine_api const ifb_b8
ifb_engine::context_destroy(
    ifb_void) {

    ifb_b8 result = true;
    
    result &= ifb_engine::memory_release();

    return(result);
}

/**********************************************************************************/
/* STARTUP/SHUTDOWN                                                               */
/**********************************************************************************/

ifb_engine_api const ifb_b8
ifb_engine::context_startup(
    ifb_void) {

    return(false);
}

ifb_engine_api const ifb_b8
ifb_engine::context_shutdown(
    ifb_void) {

    return(false);
}

/**********************************************************************************/
/* RENDERING                                                                      */
/**********************************************************************************/

ifb_engine_api const ifb_b8
ifb_engine::context_render_frame(
    ifb_void) {

    return(false);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline const IFBPlatformApi&
ifb_engine::context_get_platform_api(
    ifb_void) {

    return(_context.platform_api);
}

inline const IFBEngineConfig&
ifb_engine::context_get_config(
    ifb_void) {

    return(_context.config);
}

inline IFBEngineMemory&
ifb_engine::context_get_memory(
    ifb_void) {

    return(_context.memory);
} 