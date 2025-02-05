#pragma once

#include "ifb-engine-internal-context.hpp"

ifb_global IFBEngineContext _context;

/**********************************************************************************/
/* CREATE/DESTROY                                                                 */
/**********************************************************************************/

ifb_api const ifb_b8
ifb_engine::context_create(
    IFBPlatformApi* platform_api_ptr) {

}

ifb_api const ifb_b8
ifb_engine::context_destroy(
    ifb_void) {

}

/**********************************************************************************/
/* STARTUP/SHUTDOWN                                                               */
/**********************************************************************************/

ifb_api const ifb_b8
ifb_engine::context_startup(
    ifb_void) {

}

ifb_api const ifb_b8
ifb_engine::context_shutdown(
    ifb_void) {

}

/**********************************************************************************/
/* RENDERING                                                                                */
/**********************************************************************************/

ifb_api const ifb_b8 ifb_engine::context_render_frame (ifb_void);

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBEngineMemoryManager& 
ifb_engine::context_get_memory_manager(
    ifb_void) {

    return(_context.memory_manager);
}