#pragma once

#include "ifb-engine-internal-context.hpp"


/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

namespace ifb_engine {

    ifb_global IFBEngineContext* _context_ptr;
};

/**********************************************************************************/
/* CREATE/DESTROY                                                                 */
/**********************************************************************************/

ifb_engine_api const ifb_b8
ifb_engine::context_create(
    const IFBPlatformApi& platform_api_ref,
    const ifb_byte*       stack_memory_ptr,
    const ifb_u32         stack_memory_size) {

    ifb_b8 result = true;

    //set the platform api
    ifb_platform::set_api(platform_api_ref);

    //create the core
    IFBEngineCore* core_ptr = ifb_engine::core_create(
        stack_memory_ptr,
        stack_memory_size);

    if (!core_ptr) return(false);

    //commit singletons
    IFBEngineSingletonHandle singleton_context = ifb_engine::core_memory_singleton_commit(core_ptr, sizeof(IFBEngineContext),           alignof(IFBEngineContext));
    IFBEngineSingletonHandle singleton_struct  = ifb_engine::core_memory_singleton_commit(core_ptr, sizeof(IFBEngineContextSingletons), alignof(IFBEngineContextSingletons));
    IFBEngineSingletonHandle singleton_config  = ifb_engine::core_memory_singleton_commit(core_ptr, sizeof(IFBEngineConfig),            alignof(IFBEngineConfig));



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

inline IFBEngineCore*
ifb_engine::context_get_core(
    ifb_void) {

    ifb_macro_assert(_context_ptr);

    return(_context_ptr->core_ptr);
}

inline IFBEngineContextSingletons*
ifb_engine::context_get_singletons(
    ifb_void) {

    ifb_macro_assert(_context_ptr);

    return(_context_ptr->singletons_ptr);
}
