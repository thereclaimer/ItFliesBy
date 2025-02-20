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

ifb_engine_api const IFBB8
ifb_engine::context_create(
    const IFBPlatformApi* ptr_platform_api,
    const IFBByte*        stack_memory_ptr,
    const IFBU32          stack_memory_size) {

    //sanity check
    ifb_macro_assert(ptr_platform_api);
    ifb_macro_assert(stack_memory_ptr);
    ifb_macro_assert(stack_memory_size);

    //set the api
    (IFBVoid)ifb_platform::set_api(ptr_platform_api);

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

ifb_engine_api const IFBB8
ifb_engine::context_destroy(
    IFBVoid) {

    IFBB8 result = true;

    IFBEngineContext& context_ref = ifb_engine::context_ref();

    result &= ifb_engine::core_destroy(context_ref.ptr_core);

    return(result);
}

/**********************************************************************************/
/* STARTUP/SHUTDOWN                                                               */
/**********************************************************************************/

ifb_engine_api const IFBB8
ifb_engine::context_startup(
    IFBVoid) {

    return(false);
}

ifb_engine_api const IFBB8
ifb_engine::context_shutdown(
    IFBVoid) {

    return(false);
}

/**********************************************************************************/
/* RENDERING                                                                      */
/**********************************************************************************/

ifb_engine_api const IFBB8
ifb_engine::context_render_frame(
    IFBVoid) {

    return(false);
}

/**********************************************************************************/
/* INTERNAL                                                                       */
/**********************************************************************************/

inline IFBEngineContext&
ifb_engine::context_ref(
    IFBVoid) {

    return(_context);
}

inline IFBEngineCore*
ifb_engine::context_get_ptr_core(
    IFBVoid) {

    IFBEngineCore* ptr_core = _context.ptr_core;
    ifb_macro_assert(ptr_core);

    return(ptr_core);
}

inline IFBEngineSingletons* 
ifb_engine::context_get_ptr_singletons(
    IFBVoid) {

    IFBEngineSingletons* ptr_singletons = _context.ptr_singletons;
    ifb_macro_assert(ptr_singletons);

    return(ptr_singletons);
}