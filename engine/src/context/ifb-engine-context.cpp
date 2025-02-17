#pragma once

#include <ifb.hpp>
#include "ifb-engine-internal-context.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

ifb_global IFBEngineContext _context;

/**********************************************************************************/
/* CREATE/DESTROY                                                                 */
/**********************************************************************************/

ifb_engine_api const ifb_b8
ifb_engine::context_create(
    const IFBPlatformApi* ptr_platform_api,
    const ifb_byte*       stack_memory_ptr,
    const ifb_u32         stack_memory_size) {

    //sanity check
    ifb_macro_assert(ptr_platform_api);
    ifb_macro_assert(stack_memory_ptr);
    ifb_macro_assert(stack_memory_size);

    //create the core
    IFBEngineCore* ptr_core = ifb_engine::core_create(
        ptr_platform_api,
        stack_memory_ptr,
        stack_memory_size);
    if (!ptr_core) return(false);

    //commit singletons
    IFBEngineSingletons* ptr_singletons = ifb_engine_macro_core_memory_commit_struct(ptr_core,IFBEngineSingletons);
    ifb_engine::singletons_commit_all(ptr_singletons);

    //initialize the context
    IFBEngineContext& context_ref = ifb_engine::context_ref();
    context_ref.ptr_core         = ptr_core;
    context_ref.ptr_singletons   = ptr_singletons;

    //we're done
    return(true);
}

ifb_engine_api const ifb_b8
ifb_engine::context_destroy(
    ifb_void) {

    ifb_b8 result = true;

    IFBEngineContext& context_ref = ifb_engine::context_ref();

    result &= ifb_engine::core_destroy(context_ref.ptr_core);

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
ifb_engine::context_ref(
    ifb_void) {

    return(_context);
}

inline IFBEngineCore*
ifb_engine::context_get_ptr_core(
    ifb_void) {

    IFBEngineCore* ptr_core = _context.ptr_core;
    ifb_macro_assert(ptr_core);

    return(ptr_core);
}

inline IFBEngineSingletons* 
ifb_engine::context_get_ptr_singletons(
    ifb_void) {

    IFBEngineSingletons* ptr_singletons = _context.ptr_singletons;
    ifb_macro_assert(ptr_singletons);

    return(ptr_singletons);
}