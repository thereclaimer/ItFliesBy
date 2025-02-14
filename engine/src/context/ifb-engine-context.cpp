#pragma once


#include <ifb.hpp>
#include "ifb-engine-internal-context.hpp"

/**********************************************************************************/
/* FORWARD DECLARATIONS                                                           */
/**********************************************************************************/

ifb_global IFBEngineContext* _ptr_context;

/**********************************************************************************/
/* CREATE/DESTROY                                                                 */
/**********************************************************************************/

ifb_engine_api const ifb_b8
ifb_engine::context_create(
    const IFBPlatformApi& platform_api_ref,
    const ifb_byte*       stack_memory_ptr,
    const ifb_u32         stack_memory_size) {

    //set the platform api
    ifb_platform::set_api(platform_api_ref);

    //create the core
    IFBEngineCore* ptr_core = ifb_engine::core_create(
        stack_memory_ptr,
        stack_memory_size);

    //ensure core is valid
    if (!core_ptr) return(false);

    //commit singletons
    const IFBEngineSingletonHandle singleton_context = ifb_engine_macro_core_memory_singleton_commit_type(core_ptr, IFBEngineContext);
    const IFBEngineSingletonHandle singleton_struct  = ifb_engine_macro_core_memory_singleton_commit_type(core_ptr, IFBEngineContextSingletons);
    const IFBEngineSingletonHandle singleton_config  = ifb_engine_macro_core_memory_singleton_commit_type(core_ptr, IFBEngineConfig);
    const IFBEngineSingletonHandle singleton_input   = ifb_engine_macro_core_memory_singleton_commit_type(core_ptr, IFBInput);

    //ensure singletons are committed
    ifb_b8 all_singletons_committed = true
    all_singletons_committed &= (singleton_context.value != NULL);
    all_singletons_committed &= (singleton_struct.value  != NULL);
    all_singletons_committed &= (singleton_config.value  != NULL);
    all_singletons_committed &= (singleton_input.value   != NULL);
    if (!all_singletons_committed) return(false);

    //load the context pointers
    IFBEngineContext*           ptr_context    = ifb_engine_macro_core_memory_singleton_load_type(core_ptr, singleton_context, IFBEngineContext); 
    IFBEngineContextSingletons* ptr_singletons = ifb_engine_macro_core_memory_singleton_load_type(core_ptr, singleton_struct,  IFBEngineContextSingletons); 

    //sanity check, nothing should be null at this point
    ifb_macro_assert(ptr_context);
    ifb_macro_assert(ptr_singletons);

    //initialize the singleton struct
    ptr_singletons->context    = singleton_context;
    ptr_singletons->singletons = singleton_struct;
    ptr_singletons->config     = singleton_config;
    ptr_singletons->input      = singleton_input;

    //initialize the context
    ptr_context->ptr_core       = ptr_core;
    ptr_context->ptr_singletons = ptr_singletons;

    //set the global context
    _ptr_context = ptr_context;

    //we're done
    return(true);
}

ifb_engine_api const ifb_b8
ifb_engine::context_destroy(
    ifb_void) {

    ifb_macro_assert(_ptr_context);

    ifb_b8 result = true;
    

    result &= ifb_engine::core_destroy(_ptr_context);

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
