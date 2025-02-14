#pragma once

#include "ifb-engine-internal-context.hpp"

#include "ifb-engine-context-memory.cpp"
#include "ifb-engine-context-singletons.cpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

#define IFB_ENGINE_CONTEXT_MEMORY_STACK_SIZE        ifb_macro_size_kilobytes(IFB_ENGINE_CONFIG_MEMORY_STACK_SIZE_KB)
#define IFB_ENGINE_CONTEXT_MEMORY_RESERVATION_SIZE  ifb_macro_size_gigabytes(IFB_ENGINE_CONFIG_MEMORY_RESERVATION_SIZE_GB)

namespace ifb_engine {

    ifb_global ifb_byte         _context_stack_buffer[IFB_ENGINE_CONTEXT_MEMORY_STACK_SIZE];
    ifb_global IFBEngineContext _context;
};

/**********************************************************************************/
/* CREATE/DESTROY                                                                 */
/**********************************************************************************/

ifb_engine_api const ifb_b8
ifb_engine::context_create(
    const IFBPlatformApi& platform_api_ref) {

    ifb_b8 result = true;

    //set the platform api
    ifb_platform::set_api(platform_api_ref);

    //calculate memory sizes
    const ifb_u32 memory_size_stack       = IFB_ENGINE_CONTEXT_MEMORY_STACK_SIZE;
    const ifb_u64 memory_size_reservation = IFB_ENGINE_CONTEXT_MEMORY_RESERVATION_SIZE;
    ifb_byte*     memory_stack_buffer     = _context_stack_buffer;

    //reserve the memory
    result &= ifb_engine::context_memory_reserve(
        memory_stack_buffer,
        memory_size_stack,
        memory_size_reservation);

    //commit singletons
    result &= ifb_engine::context_singletons_commit_all();

    //load the config
    result &= ifb_engine::config_load();

    //we're done
    return(result);
}

ifb_engine_api const ifb_b8
ifb_engine::context_destroy(
    ifb_void) {

    ifb_b8 result = true;
    
    result &= ifb_engine::context_memory_release();

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

inline IFBEngineContext& 
ifb_engine::context(
    ifb_void) {

    return(_context);
}

inline IFBEngineContextMemory&
ifb_engine::context_get_memory(
    ifb_void) {

    return(_context.memory);
}

inline IFBEngineContextSingletons&
ifb_engine::context_get_singletons(
    ifb_void) {

    return(_context.singletons);
}