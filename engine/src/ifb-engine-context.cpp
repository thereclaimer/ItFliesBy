#pragma once

#include "ifb-engine-internal-context.hpp"

ifb_global IFBEngineContext _context;

/**********************************************************************************/
/* CREATE/DESTROY                                                                 */
/**********************************************************************************/

ifb_api const ifb_b8
ifb_engine::context_create(
    const  IFBPlatformApi* platform_api_ptr) {

    return(false);
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

inline IFBEngineMemoryManager& 
ifb_engine::context_get_memory_manager(
    ifb_void) {

    return(_context.memory_manager);
}